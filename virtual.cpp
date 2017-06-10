#include <cstdio>
#include <cstdlib>
#include "vmcore.hpp"
#include "vminline.hpp"
#include "vm_codemacros.hpp"

using namespace std;

/*

Hello world Test

*/
/*
void nativePrint(VMCore* vm)
{
  printf("%s", vm->getReg(_r1).pCh());
}

static const char* helloString = "hello world\n";

_VM_CODE(hello) // a vm function
{
  _lda(helloString, _r1), // load the address of the text into r1
  _calln(nativePrint),    // call native print method
  _ret                    // return
};
*/

////////////////////////////////////////////////////////////////////////////////
//
//  some quick embedded virtual code
//
////////////////////////////////////////////////////////////////////////////////

/*
void nativePrintR1(VMCore *vm) // a quick native method
{
  printf("r1.s32 = %ld\n", vm->getReg(_r1).s32());
}

void nativePrintR1Hex(VMCore* vm)
{
  printf("r1 = 0x%08X%08X\n", (unsigned)vm->getReg(_r1).getMSW(), (unsigned)vm->getReg(_r1).getLSW());
}

_VM_CODE(testJump) // a vm function
{
  _jump(_r1, 4), 0, 2, 4, 6,

  // case r1 = 0
  _ldq(15, _r1),
  _ret,

  // case r1 = 1
  _ldq(14, _r1),
  _ret,

  // case r1 = 2
  _ldq(13, _r1),
  _ret,

  // case r1 = 3
  _ldq(12, _r1),
  _ret
};

_VM_CODE(stuff)
{
  _xor_64(_r1, _r3),
  _rol_64(_r2, _r3),
  _ret
};

_VM_CODE(main) // the main vm function
{
  _ldq(0, _r1),
  _call(testJump),
  _calln(nativePrintR1),

  _ldq(1, _r1),
  _call(testJump),
  _calln(nativePrintR1),

  _ldq(2, _r1),
  _call(testJump),
  _calln(nativePrintR1),

  _ldq(3, _r1),
  _call(testJump),
  _calln(nativePrintR1),

  _ld_16_i8(32, _r2),

  _ld_32_i32(0x11223344, _r1),
  _calln(nativePrintR1Hex),
  _lsl_64(_r2, _r1),
  _calln(nativePrintR1Hex),
  _ld_32_i32(0x55667788, _r1),
  _calln(nativePrintR1Hex),

  _iset(0),
  _ldq(1, _r1),
  _ld_32_i32(10000000, _r2),
  //_call(stuff),     // size : branch target
  _sub_32(_r1, _r2),  // 1 -17
  _sub_32(_r1, _r3),  // 1 -16
  _sub_32(_r1, _r4),  // 1 -15
  _sub_32(_r1, _r5),  // 1 -14
  _sub_32(_r1, _r6),  // 1 -13
  _sub_32(_r1, _r7),  // 1 -12
  _sub_32(_r1, _r8),  // 1 -11
  _sub_32(_r1, _r9),  // 1 -10
  _sub_32(_r1, _r10), // 1  -9
  _sub_32(_r1, _r11), // 1  -8
  _sub_32(_r1, _r12), // 1  -7
  _sub_32(_r1, _r13), // 1  -6
  _sub_32(_r1, _r14), // 1  -5
  _sub_32(_r1, _r15), // 1  -4
  _sub_32(_r1, _r16), // 1  -3
  _bnz_32(_r2, -17),  // 3  (-2, would be infinite)
  _ret                //     0
};
*/
