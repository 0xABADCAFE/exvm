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
#include <cmath>
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

void printVec3f(Interpreter* vm) {
  // Vec3 in r0
  const float32 *v = vm->getReg(_r0).pF32();
  std::printf(
    "vec3f { %0.5f, %0.5f, %0.5f } : %0.5f\n",
    (float64)v[0], (float64)v[1], (float64)v[2],
    sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2])
  );
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  mockCodeSegment
//
//  This represents the expected layout of a freshly loaded, unlinked code segment.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

uint16 mockCodeSegment[] = {
  _salloc(10*3*sizeof(float32), _r15) // 0
  _move_64(_r15, _r0)                 // 2
  _ld_32_f32(1.75, _r1)               // 3
  _spl_v3f32(_r1, _r0)                // 6
  _calln_unresolved(@printVec3f)      // 8
  _norm_v3f32(_r0, _r0)               // 10
  _calln_unresolved(@printVec3f)      // 12
  _sfree(_r15)                        // 14
  _ret                                // 15
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  mockDataSegment
//
//  This represents the expected layout of a freshly loaded, unlinked data segment.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char mockDataSegment[] = "Dummy\0";

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  mockDataSegment
//
//  This represents the expected layout of a freshly loaded, unlinked data segment.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char mockNameSegment[] =
  // Name         Offset
  "main\0"        // 0
  "printVec3f\0"  // 5
;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  mockExports
//
//  This represents the expected layout of a freshly loaded, unlinked export table.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RawSegmentData::SymbolRef mockExports[] = {
  {
    // @main
    0 | RawSegmentData::TYPE_CODE,   // Offset of the symbol name "main" in the name segment OR'd with CODE
    0                                 // Offset of the entry point into the code segment (in words)
  }
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
    // @printVec3f
    5 | RawSegmentData::TYPE_NATIVE,  // Offset of the symbol name "printVec3f" in the name segment OR'd with NATIVE
    9                                 // Offset into the code segment where the symbol ID will be injected
  },  {
    // @printVec3f
    5 | RawSegmentData::TYPE_NATIVE,  // Offset of the symbol name "printVec3f" in the name segment OR'd with NATIVE
    13                                 // Offset into the code segment where the symbol ID will be injected
  },


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
    "\tsizeof(mockCodeSegment) : %" FU32 "\n"
    "\tsizeof(Linker)          : %" FU32 "\n"
    "\tsizeof(Interpreter)     : %" FU32 "\n"
    "\tsizeof(Executable)      : %" FU32 "\n",
    (uint32) sizeof(mockCodeSegment),
    (uint32) sizeof(Linker),
    (uint32) sizeof(Interpreter),
    (uint32) sizeof(Executable)
  );

  std::puts("Code Segment before linking...");
  for (int i = 0; i<sizeof(mockCodeSegment)/sizeof(uint16); i++) {
    printf("%3d  0x%04X\n", i, mockCodeSegment[i]);
  }

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
  linker->defineNativeCode("printVec3f", printVec3f);

  // Add the RawSegment
  linker->addRawSegment(&mockLoadSegment);

  // Link it
  linker->link();


  std::puts("Code Segment after linking...");
  for (int i = 0; i<sizeof(mockCodeSegment)/sizeof(uint16); i++) {
    printf("%3d  0x%04X\n", i, mockCodeSegment[i]);
  }

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
/*
    std::puts("Data Symbol Table");
    for (uint32 i = 0; i < executable->dataCount; i++) {
      std::printf("\tSymbol ID : %" FU32 " -> %p\n", i, executable->dataAddresses[i]);
    }
*/
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

////////////////////////////////////////////////////////////////////////////////

int main() {
  runTestExample();
  return 0;
}
