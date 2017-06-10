#include <cstdio>
#include <cstdlib>
#include "vmcore.hpp"
#include "vminline.hpp"
#include "vm_codemacros.hpp"

using namespace std;

/*
The following data represends VM code in a form similar to that which runtime loading, linking
and symbol resolution would leave in memory.
We use the predefined macros in vm_codemacros.hpp to provide ourselves with a way of represending
the operand codes in human readable form, as well as converting references into their respective
word codes.



// Define the range in x and y here:

const double yMin = -1.0;
const double yMax = +1.0;
const double xMin = -2.0;
const double xMax = +0.5;

// And here is the resolution:

const double dxy = 0.005;

#include <stdio.h>
#include <limits.h>

int main(void) {

    double cx, cy;
    double zx, zy, new_zx;
    unsigned char n;
    int nx, ny;

    // The Mandelbrot calculation is to iterate the equation
    // z = z*z + c, where z and c are complex numbers, z is initially
    // zero, and c is the coordinate of the point being tested. If
    // the magnitude of z remains less than 2 for ever, then the point
    // c is in the Mandelbrot set. We write out the number of iterations
    // before the magnitude of z exceeds 2, or UCHAR_MAX, whichever is
    // smaller.

    for (cy = yMin; cy < yMax; cy += dxy) {
        for (cx = xMin; cx < xMax; cx += dxy) {
            zx = 0.0;
            zy = 0.0;
            n = 0;
            while ((zx*zx + zy*zy < 4.0) && (n != UCHAR_MAX)) {
                new_zx = zx*zx - zy*zy + cx;
                zy = 2.0*zx*zy + cy;
          zx = new_zx;
          n++;
            }
            write (1, &n, sizeof(n)); // Write the result to stdout
        }
    }

    // Now calculate the image dimensions. We use exactly the same
    // for loops as above, to guard against any potential rounding errors.

    nx = 0;
    ny = 0;
    for (cx = xMin; cx < xMax; cx += dxy) {
        nx++;
    }
    for (cy = yMin; cy < yMax; cy += dxy) {
        ny++;
    }

    fprintf (stderr, "To process the image: convert -depth 8 -size %dx%d gray:output out.jpg\n",
       nx, ny);
    return 0;
}

*/

void nativeAllocBuffer(VMCore* vm)
{
  // width/height in r2/r3
  // return buffer in r1
  int w = vm->getReg(_r2).s32();
  int h = vm->getReg(_r3).s32();
  vm->getReg(_r1).pU8() = new uint8[w*h];
  printf("Allocated buffer [%d x %d]\n", w, h);
}

void nativeFreeBuffer(VMCore* vm)
{
  // expects buffer in r1
  delete[] vm->getReg(_r1).pCh();
  vm->getReg(_r1).pCh() = 0;
  printf("Freed buffer\n");
}

void nativeWriteBuffer(VMCore* vm)
{
  // writes buffer in r1 to filename in r4
  // expects width/height in r2/r3
  const char* fileName = vm->getReg(_r16).pCh();
  int w = vm->getReg(_r2).s32();
  int h = vm->getReg(_r3).s32();

  if (!fileName) {
    fileName = "untitled.pgm";
    printf("Warning - no filename passed to native function, using safe default\n");
  }

  FILE *f = fopen(fileName, "wb");
  if (f) {
    fprintf(f, "P5\n%d\n%d\n255\n", w, h);
    fwrite(vm->getReg(_r1).pCh(), 1, w*h, f);
    fclose(f);
    printf("Wrote buffer '%s'\n", fileName);
  }
}

void nativePrintCoords(VMCore* vm)
{
  printf(
    "Coords %4d, %4d (%.6f, %.6f)\n",
    (int)vm->getReg(_r7).s32(),
    (int)vm->getReg(_r5).s32(),
    vm->getReg(_r9).f32(),
    vm->getReg(_r4).f32()
  );
}

_VM_CODE(makeFractal)
{
  // r1 = pixel data address
  // r2 = width in pixels
  // r3 = height in pixels
  // r4 = cY (float pos, starting at yMin)
  // r5 = y (int) pixel
  // r6 = xMin (float)
  // r7 = cX (float pos, starting at xMin)
  // r8 = fStep
  // r9 = x (int) pixel
  // r10 = iStep (1)

  _save       (_mr1)           // 2 : save r1
  _ldq        (0, _r5)         // 1 : y (r5) = 0
  _ld_16_i32  (255, _r10)      // 2 : max iters

  // y-loop
  _ldq        (0, _r9)         // 1 : x = 0
  _move_32    (_r6, _r7)       // 1 : cX = xMin

  // x-loop                        do {

  _move_32    (_r7, _r11)            // 1 : zx = cX
  _move_32    (_r4, _r12)            // 1 : zy = cY
  _ldq        (0, _r13)              // 1 :  n = 0

                                      // do {

  _move_32    (_r11, _r14)           // 1
  _mul_f32    (_r11, _r14)           // 1 : zx2 = zx*zx
  _move_32    (_r12, _r15)           // 1
  _mul_f32    (_r12, _r15)           // 1 : zy2   = zy*zy

  _move_32    (_r7,  _r16)           // 1 : new_zx = cX
  _add_f32    (_r14, _r16)           // 1 : new_zx += zx2
  _sub_f32    (_r15, _r16)           // 1 : new_zx -= zy2

  _add_f32    (_r15, _r14)           // 1 : r14 = zx*zx + zy*zy (for loop test)

  _move_32    (_r11, _r15)           // 1 : tmp = zx
  _mul_f32    (_r12, _r15)           // 1 : tmp *= zy
  _add_f32    (_r15, _r15)           // 1 : tmp += tmp2
  _add_f32    (_r4,  _r15)           // 1 : tmp += cY (tmp = 2*zx*zy+cY)

  _move_32    (_r15, _r12)           // 1 : zy = tmp
  _move_32    (_r16, _r11)           // 1 : zx = new_zx
  _addi_16    (1, _r13)              // 2 : n++

  _ld_32_f32  (4.0f, _r16)             // 3
  _bgr_f32    (_r14, _r16, 2)          // 2
  _bls_32     (_r13, _r10, -23)        // 2

  _mul_u16    (_r13, _r13)             // 1
  _st_ripi_8  (_r13, _r1)              // 1 : out = n
  _add_f32    (_r8, _r7)               // 1 : cX += fStep
  _addi_16    (1, _r9)                 // 2 : x += iStep

  _bls_32     (_r9, _r2, -(6+23+3+1))    // 2 : } while (x < width)

  _add_f32    (_r8, _r4)                 // 1 : cY += fStep
  _addi_16    (1, _r5)                   // 2 : y += iStep
  _bls_32     (_r5, _r3, -(5+5+6+23+1))  // 2 : } while (y < height)

  _restore    (_mr1)                     // 1
  _ret
};

_VM_CODE(calculateRanges)
{
  // calculates xMin in r6, xMax in r7, step in r8
  _move_32    (_r5, _r6)
  _sub_f32    (_r4, _r6)         // r6 = r5-r4 (total y range)
  _s32to_f32  (_r2, _r7)         // r7 = (float) r2
  _move_32    (_r7, _r9)
  _mul_f32    (_r6, _r7)         // r7 *= r6
  _s32to_f32  (_r3, _r6)         // r6 = (float) r3
  _div_f32    (_r6, _r7)         // r7 /= r6
  _move_32    (_r7, _r8)
  _div_f32    (_r9, _r8)
  _ld_32_f32  (0.75f, _r6)
  _sub_f32    (_r7, _r6)
  _add_f32    (_r6, _r7)

  _ret
};


_VM_CODE(virtualProgram)          // a vm function
{
  _ld_16_i16  (512, _r2)
  _ld_16_i16  (512, _r3)
  _calln      (nativeAllocBuffer)
  _ld_32_f32  (-1.25f, _r4)       // yMin
  _ld_32_f32  (1.25f, _r5)        // yMax
  _call       (calculateRanges)
  _call       (makeFractal)
  _lda        ("framebuffer.pgm", _r16)
  _calln      (nativeWriteBuffer)
  _calln      (nativeFreeBuffer)
  _ret
};



