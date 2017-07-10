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
#include "include/vmcore.hpp"
#include "include/vminline.hpp"
#include "include/vm_codemacros.hpp"
#include <new>
using namespace std;

////////////////////////////////////////////////////////////////////////////////

void nativeAllocBuffer(VMCore* vm) {
  // width/height in r1/r2
  // return buffer in r0
  int w = vm->getReg(_r1).s32();
  int h = vm->getReg(_r2).s32();
  vm->getReg(_r0).pU8() = new(nothrow) uint8[w*h];
  printf("Allocated buffer [%d x %d]\n", w, h);
}

void nativeFreeBuffer(VMCore* vm) {
  // expects buffer in r0
  delete[] vm->getReg(_r0).pCh();
  vm->getReg(_r0).pCh() = 0;
  printf("Freed buffer\n");
}

void nativeWriteBuffer(VMCore* vm) {
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
    fwrite(vm->getReg(_r0).pCh(), 1, w*h, f);
    fclose(f);
    printf("Wrote buffer '%s'\n", fileName);
  }
}

void nativePrintCoords(VMCore* vm) {
  printf(
    "Coords %4d, %4d (%.6f, %.6f)\n",
    (int)vm->getReg(_r6).s32(),
    (int)vm->getReg(_r4).s32(),
    vm->getReg(_r8).f32(),
    vm->getReg(_r3).f32()
  );
}

////////////////////////////////////////////////////////////////////////////////

_VM_CODE(makeFractal) {
  // r0 = pixel data address
  // r1 = width in pixels
  // r2 = height in pixels
  // r3 = cY (float pos, starting at yMin)
  // r4 = 4.0 (bailout)
  // r5 = xMin (float)
  // r6 = cX (float pos, starting at xMin)
  // r7 = fStep
  // r8 = x (int) pixel
  // r9 = iStep (1)

  _save       (_mr0|_mr2)                // 2 : save pixel base address
  _ld_32_f32  (4.0f, _r4)                // 3 : bailout = 4.0
  _ld_16_i32  (255,  _r9)                // 2 : max iters

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
  _ret
};

_VM_CODE(calculateRanges) {
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

  _ret
};

_VM_CODE(virtualProgram) {
  _ld_16_i16  (512, _r1)
  _ld_16_i16  (512, _r2)
  _calln      (nativeAllocBuffer)
  _ld_32_f32  (-1.25f, _r3)       // yMin
  _ld_32_f32  (1.25f, _r4)        // yMax
  _call       (calculateRanges)
  _call       (makeFractal)
  _lda        ("framebuffer.pgm", _r15)
  _calln      (nativeWriteBuffer)
  _calln      (nativeFreeBuffer)
  _ret
};

