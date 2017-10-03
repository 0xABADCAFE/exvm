//****************************************************************************//
//**                                                                        **//
//** File:         vmprogram.cpp                                            **//
//** Description:  Virtual Machine test example                             **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2001-08-14                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

#include <cstdio>
#include <cstdlib>
#include "include/vm_core.hpp"
#include "include/vm_inline.hpp"
#include "include/vm_codemacros.hpp"
#include "include/vm_linker.hpp"
#include <new>

using namespace std;
using namespace ExVM;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Native functions
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void nativeAllocBuffer(Interpreter* vm) {
  // width/height in r1/r2
  // return buffer in r0
  int w = vm->getReg(_r1).s32();
  int h = vm->getReg(_r2).s32();
  uint8* buffer = (uint8*)std::calloc(w * h, 1);
  vm->getReg(_r0).pU8() = buffer;
  if (buffer) {
    printf("Allocated buffer [%d x %d]\n", w, h);
  }
}

void nativeFreeBuffer(Interpreter* vm) {
  // expects buffer in r0
  uint8* buffer = vm->getReg(_r0).pU8();
  if (buffer) {
    std::free(buffer);
    printf("Freed buffer\n");
  }
  vm->getReg(_r0).pCh() = 0;
}

void nativeWriteBuffer(Interpreter* vm) {
  // writes buffer in r0 to filename in r15
  // expects width/height in r1/r2
  const char* fileName = vm->getReg(_r15).pCh();
  int w = vm->getReg(_r1).s32();
  int h = vm->getReg(_r2).s32();

  if (!fileName) {
    fileName = "untitled.pgm";
    printf("Warning - no filename passed to native function, using safe default\n");
  }

  FILE *f = fopen(fileName, "wb");
  if (f) {
    fprintf(f, "P5\n%d\n%d\n255\n", w, h);
    fwrite(vm->getReg(_r0).pCh(), 1, w * h, f);
    fclose(f);
    printf("Wrote buffer '%s'\n", fileName);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  mockCodeSegment
//
//  This represents the expected layout of a freshly loaded, unlinked code segment.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

uint16 mockCodeSegment[] = {

  // Offset 0 : @render

  // r0 = pixel data address
  // r1 = width in pixels
  // r2 = height in pixels
  // r3 = cY (float pos, starting at yMin)
  // r4 = 16.0 (bailout)
  // r5 = xMin (float)
  // r6 = cX (float pos, starting at xMin)
  // r7 = fStep
  // r8 = x (int) pixel
  // r9 = iStep (1)

  _save       (_mr0|_mr2)                // 2 : save pixel base address
  _ld_32_f32  (16.0f, _r4)               // 3 : bailout = 16.0
  _ld_16_i32  (256,  _r9)                // 2 : max iters

  // y loop
  _ldq        (0,    _r8)                // 1 : x = 0
  _move_32    (_r5,  _r6)                // 1 : cX = xMin

  // x loop
  _move_32    (_r6,  _r10)               // 1 : zx = cX
  _move_32    (_r3,  _r11)               // 1 : zy = cY
  _ldq        (0,    _r12)               // 1 : n = 0

  // iteration loop
  _move_32    (_r10, _r13)               // 1
  _mul_f32    (_r10, _r13)               // 1 : zx2 = zx*zx
  _move_32    (_r11, _r14)               // 1
  _mul_f32    (_r11, _r14)               // 1 : zy2   = zy*zy

  _move_32    (_r6,  _r15)               // 1 : new_zx = cX
  _add_f32    (_r13, _r15)               // 1 : new_zx += zx2
  _sub_f32    (_r14, _r15)               // 1 : new_zx -= zy2

  _add_f32    (_r14, _r13)               // 1 : r14 = zx*zx + zy*zy (for loop test)

  _move_32    (_r10, _r14)               // 1 : tmp = zx
  _mul_f32    (_r11, _r14)               // 1 : tmp *= zy
  _add_f32    (_r14, _r14)               // 1 : tmp += tmp2
  _add_f32    (_r3,  _r14)               // 1 : tmp += cY (tmp = 2*zx*zy+cY)

  _move_32    (_r14, _r11)               // 1 : zy = tmp
  _move_32    (_r15, _r10)               // 1 : zx = new_zx
  _addi_16    (1,    _r12)               // 2 : n++

  _bgr_f32    (_r13, _r4, 2)             // 2 : bailout
  _bls_32     (_r12, _r9, -20)           // 2 : iteration loop

  // bailout
  _mul_u16    (_r12, _r12)               // 1 : out *= out - improve gradient
  _st_ripi_8  (_r12, _r0)                // 1 : out = n
  _add_f32    (_r7,  _r6)                // 1 : cX += fStep
  _addi_16    (1,    _r8)                // 2 : x += iStep

  _bls_32     (_r8, _r1, -(6+20+3+1))    // 2 : x loop

  _add_f32    (_r7, _r3)                 // 1 : cY += fStep
  _subi_16    (1,   _r2)                 // 2 : y += iStep
  _bnz_32     (_r2, -(5+5+6+20+1))       // 2 : y loop

  _restore    (_mr0|_mr2)                // 1
  _ret,

  // Offset 47 : @ranges

  // calculates xMin in r5, xMax in r6, step in r7
  _move_32    (_r4, _r5)
  _sub_f32    (_r3, _r5)         // r5 = r4 - r3 (total y range)
  _s32to_f32  (_r1, _r6)         // r6 = (float) r1
  _move_32    (_r6, _r8)
  _mul_f32    (_r5, _r6)         // r6 *= r5
  _s32to_f32  (_r2, _r5)         // r5 = (float) r2
  _div_f32    (_r5, _r6)         // r6 /= r4
  _move_32    (_r6, _r7)
  _div_f32    (_r8, _r7)
  _ld_32_f32  (0.75f, _r5)
  _sub_f32    (_r6, _r5)
  _add_f32    (_r5, _r6)

  _ret,

  // Offset 62 : @main
  _ld_16_i16         (1024, _r1)      // 62
  _ld_16_i16         (1024, _r2)      // 64
  _calln_unresolved  (@allocBuff)    // 66 : insert @allocBuff -> 67
  _ld_32_f32         (-1.25f, _r3)   // 68
  _ld_32_f32         (1.25f, _r4)    // 71
  _call_unresolved   (@ranges)       // 74 : insert @ranges -> 75
  _call_unresolved   (@render)       // 76 : insert @render -> 77
  _lda_unresolved    (@file, _r15)   // 78 : insert @file   -> 79
  _calln_unresolved  (@writeBuff)    // 80 : insert @writeBuff -> 81
  _calln_unresolved  (@freeBuff)     // 82 : insert @freeBuff  -> 83
  _ret                               // 84
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  mockDataSegment
//
//  This represents the expected layout of a freshly loaded, unlinked data segment.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char mockDataSegment[] = "framebuffer.pgm\0";

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  mockDataSegment
//
//  This represents the expected layout of a freshly loaded, unlinked data segment.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char mockNameSegment[] =
  // Name         Offset
  "allocBuff\0"   // 0
  "freeBuff\0"    // 10
  "writeBuff\0"   // 19
  "render\0"      // 29
  "ranges\0"      // 36
  "main\0"        // 43
  "file\0";       // 48

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  mockExports
//
//  This represents the expected layout of a freshly loaded, unlinked export table.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RawSegmentData::SymbolRef mockExports[] = {
  {
    // @render
    29 | RawSegmentData::TYPE_CODE,   // Offset of the symbol name "render" in the name segment OR'd with CODE
    0                                 // Offset of the entry point into the code segment (in words)
  }, {
    // @ranges
    36 | RawSegmentData::TYPE_CODE,   // Offset of the symbol name "ranges" in the name segment OR'd with CODE
    47                                // Offset of the entry point into the code segment (in words)
  }, {
    // @main
    43 | RawSegmentData::TYPE_CODE,   // Offset of the symbol name "main" in the name segment OR'd with CODE
    62,                               // Offset of the entry point into the code segnent (in words)
  }, {
    // @file
    48 | RawSegmentData::TYPE_DATA,   // Offset of the symbol name "file" in the name segment OR'd with DATA
    0,                                // Offset of the element into the data segment (in bytes)
  },
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  mockImports
//
//  This represents the expected layout of a freshly loaded, unlinked import table.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RawSegmentData::SymbolRef mockImports[] = {
  {
    // @allocBuff
    0 | RawSegmentData::TYPE_NATIVE,  // Offset of the symbol name "allocBuff" in the name segment OR'd with NATIVE
    67                                // Offset into the code segment where the symbol ID will be injected
  }, {
    // @ranges
    36 | RawSegmentData::TYPE_CODE,   // Offset of the symbol name "ranges" in the name segment OR'd with CODE
    75                                // Offset into the code segment where the symbol ID will be injected
  }, {
    // @render
    29 | RawSegmentData::TYPE_CODE,   // Offset of the symbol name "render" in the name segment OR'd with CODE
    77                                // Offset into the code segment where the symbol ID will be injected
  }, {
    // @file
    48 | RawSegmentData::TYPE_DATA,   // Offset of the symbol name "file" in the name segment OR'd with DATA
    79                                // Offset into the code segment where the symbol ID will be injected
  }, {
    // @writeBuff
    19 | RawSegmentData::TYPE_NATIVE, // Offset of the symbol name "writeBuff" in the name segment OR'd with NATIVE
    81                                // Offset into the code segment where the symbol ID will be injected
  }, {
    // @freeBuff
    10 | RawSegmentData::TYPE_NATIVE, // Offset of the symbol name "freeBuff" in the name segment OR'd with NATIVE
    83                                // Offset into the code segment where the symbol ID will be injected
  }

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  mockLoadSegment
//
//  This represents the expected layout of a freshly loaded, unlinked RawSegment instance that incorporates all of the
//  above elements.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RawSegmentData mockLoadSegment = {
  mockCodeSegment,                                         // .codeSegment
  mockDataSegment,                                         // .dataSegment
  mockNameSegment,                                         // .nameSegment
  mockExports,                                             // .exportTable
  mockImports,                                             // .importTable
  RawSegmentData::MAGIC,                                   // .magic
  sizeof(mockExports) / sizeof(RawSegmentData::SymbolRef), // .exportTableLength
  sizeof(mockImports) / sizeof(RawSegmentData::SymbolRef), // .importTableLength
  sizeof(mockCodeSegment) / sizeof(uint16),                // .codeSegmentLength
  sizeof(mockDataSegment),                                 // .dataSegmentLength
  sizeof(mockNameSegment)                                  // .nameSegmentLength
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  runTestExample()
//
//  Takes the mockLoadSegment and runs it through the Linker. This
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void runTestExample() {

  std::printf(
    "Structure Sizes\n"
    "\tsizeof(Linker)      : %" FU32 "\n"
    "\tsizeof(Interpreter) : %" FU32 "\n"
    "\tsizeof(Executable)  : %" FU32 "\n",
    (uint32)sizeof(Linker),
    (uint32)sizeof(Interpreter),
    (uint32)sizeof(Executable)
  );

  std::puts(
    "\nLinking Virtual Program\n"
    "-----------------------\n"
  );

  Linker* linker = new(nothrow) Linker();

  if (!linker) {
    std::puts("Could not instantiate linker.");
    return;
  }

  // Add host defined native function symbols first.
  linker->defineNativeCode("allocBuff", nativeAllocBuffer);
  linker->defineNativeCode("freeBuff",  nativeFreeBuffer);
  linker->defineNativeCode("writeBuff", nativeWriteBuffer);

  // Add the RawSegment
  linker->addRawSegment(&mockLoadSegment);

  // Link it
  linker->link();

  // Grab the executable layout
  Executable* executable = linker->getExecutable();

  // Dispose of the linker
  delete linker;

  // Dump the Executable
  if (executable) {
    printf(
      "Linked Executable at %p {\n"
      "\tnativeCodeAddresses : %p\n"
      "\tcodeAddresses       : %p\n"
      "\tdataAddresses       : %p\n"
      "\tnativeCodeCount     : %" FU32 "\n"
      "\tcodeCount           : %" FU32 "\n"
      "\tdataCount           : %" FU32 "\n"
      "}\n",
      executable,
      executable->nativeCodeAddresses,
      executable->codeAddresses,
      executable->dataAddresses,
      (uint32)executable->nativeCodeCount,
      (uint32)executable->codeCount,
      (uint32)executable->dataCount
    );
    std::puts("NativeCall Symbol Table");
    for (uint32 i = 0; i < executable->nativeCodeCount; i++) {
      std::printf("\tSymbol ID : %" FU32 " -> %p\n", i, executable->nativeCodeAddresses[i]);
    }
    std::puts("Code Symbol Table");
    for (uint32 i = 0; i < executable->codeCount; i++) {
      std::printf("\tSymbol ID : %" FU32 " -> %p\n", i, executable->codeAddresses[i]);
    }
    std::puts("Data Symbol Table");
    for (uint32 i = 0; i < executable->dataCount; i++) {
      std::printf("\tSymbol ID : %" FU32 " -> %p\n", i, executable->dataAddresses[i]);
    }

    std::puts(
      "\nBeginning Virtual Program\n"
      "-----------------------\n"
    );

    // Create an Interpreter
    Interpreter* interpreter = new Interpreter();
    if (interpreter) {
      // Execute it
      interpreter->setExecutable(executable);
      interpreter->execute();
      interpreter->dump();

      // Victory
      std::puts(
        "\n-----------------------\n"
      );

      // Release the Executable
      Executable::release(executable);

      delete interpreter;
    }
  } else {
    std::puts("\nDid not link an Executable.\n");
  }

}

