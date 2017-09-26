//****************************************************************************//
//**                                                                        **//
//** File:         main.cpp                                                 **//
//** Description:  Test Application                                         **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2001-08-29                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//


#include <new>
#include <cstdio>
#include <cstdlib>
#include "include/vm_core.hpp"
#include "include/vm_inline.hpp"
#include "include/vm_codemacros.hpp"

using namespace std;
using namespace ExVM;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const int testSize = 128;

void dumpTestArray(Interpreter *interpreter) {

  uint8* test = interpreter->getReg(_r1).pU8();

  printf("Target array:");
  for (int i = 0; i < testSize; i++) {

    if (!(i & 0x1F)) {
      putchar('\n');
    }
    else if (!(i & 0x7)) {
      printf(": ");
    }
    printf("0x%02X ", test[i]);
  }
  printf("\n\n");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {

  // Create an Interpreter
  Interpreter* interpreter = new Interpreter();
  if (interpreter) {

    uint16 code[] = {
      _salloc(testSize, _r1) // 0

      // This is where we will inject our vector test
      _nop                   // 2
      0x0012,

      _sfree(_r1)            // 4
      _ret                   // 5
    };

    interpreter->getReg(_r0).u64() = 0x0123456789ABCDEFULL;
    interpreter->getReg(_r2).u32() = testSize;

    // Test 8 bit vector fill
    printf("Testing 8-bit vector fill...\n");
    code[2] = VMDefs::_VEC1<<8 | VMDefs::_VFILL_8;
    interpreter->setPC(code);
    interpreter->execute();
    dumpTestArray(interpreter);

    // test 16 bit vector fill
    printf("Testing 16-bit vector fill...\n");
    code[2] = VMDefs::_VEC1<<8 | VMDefs::_VFILL_16;
    interpreter->getReg(_r2).u32() = testSize/sizeof(uint16);
    interpreter->setPC(code);
    interpreter->execute();
    dumpTestArray(interpreter);

    // test 32 bit vector fill
    printf("Testing 32-bit vector fill...\n");
    code[2] = VMDefs::_VEC1<<8 | VMDefs::_VFILL_32;
    interpreter->getReg(_r2).u32() = testSize/sizeof(uint32);
    interpreter->setPC(code);
    interpreter->execute();
    dumpTestArray(interpreter);

    // test 64 bit vector fill
    printf("Testing 64-bit vector fill...\n");
    code[2] = VMDefs::_VEC1<<8 | VMDefs::_VFILL_64;
    interpreter->getReg(_r2).u32() = testSize/sizeof(uint64);
    interpreter->setPC(code);
    interpreter->execute();
    dumpTestArray(interpreter);

    // Test 8 bit vector negate
    interpreter->getReg(_r2).u32() = testSize;
    interpreter->getReg(_r0).pU8() = interpreter->getReg(_r1).pU8();
    printf("Testing 8-bit vector negate (overwriting self) #1...\n");
    code[2] = VMDefs::_VEC1<<8 | VMDefs::_VNEG_S8;
    interpreter->setPC(code);
    interpreter->execute();
    dumpTestArray(interpreter);

    // Test 8 bit vector negate
    interpreter->getReg(_r2).u32() = testSize;
    interpreter->getReg(_r0).pU8() = interpreter->getReg(_r1).pU8();
    printf("Testing 8-bit vector negate (overwriting self) #2...\n");
    code[2] = VMDefs::_VEC1<<8 | VMDefs::_VNEG_S8;
    interpreter->setPC(code);
    interpreter->execute();
    dumpTestArray(interpreter);

    // Test 16 bit vector negate
    interpreter->getReg(_r2).u32() = testSize/sizeof(uint16);
    interpreter->getReg(_r0).pU8() = interpreter->getReg(_r1).pU8();
    printf("Testing 16-bit vector negate (overwriting self) #1...\n");
    code[2] = VMDefs::_VEC1<<8 | VMDefs::_VNEG_S16;
    interpreter->setPC(code);
    interpreter->execute();
    dumpTestArray(interpreter);

    // Test 16 bit vector negate
    interpreter->getReg(_r2).u32() = testSize/sizeof(uint16);
    interpreter->getReg(_r0).pU8() = interpreter->getReg(_r1).pU8();
    printf("Testing 16-bit vector negate (overwriting self) #2...\n");
    code[2] = VMDefs::_VEC1<<8 | VMDefs::_VNEG_S16;
    interpreter->setPC(code);
    interpreter->execute();
    dumpTestArray(interpreter);

    // Test 32 bit vector negate
    interpreter->getReg(_r2).u32() = testSize/sizeof(uint32);
    interpreter->getReg(_r0).pU8() = interpreter->getReg(_r1).pU8();
    printf("Testing 32-bit vector negate (overwriting self) #1...\n");
    code[2] = VMDefs::_VEC1<<8 | VMDefs::_VNEG_S32;
    interpreter->setPC(code);
    interpreter->execute();
    dumpTestArray(interpreter);

    // Test 32 bit vector negate
    interpreter->getReg(_r2).u32() = testSize/sizeof(uint32);
    interpreter->getReg(_r0).pU8() = interpreter->getReg(_r1).pU8();
    printf("Testing 32-bit vector negate (overwriting self) #2...\n");
    code[2] = VMDefs::_VEC1<<8 | VMDefs::_VNEG_S32;
    interpreter->setPC(code);
    interpreter->execute();
    dumpTestArray(interpreter);

    // Test 64 bit vector negate
    interpreter->getReg(_r2).u32() = testSize/sizeof(uint64);
    interpreter->getReg(_r0).pU8() = interpreter->getReg(_r1).pU8();
    printf("Testing 64-bit vector negate (overwriting self) #1...\n");
    code[2] = VMDefs::_VEC1<<8 | VMDefs::_VNEG_S64;
    interpreter->setPC(code);
    interpreter->execute();
    dumpTestArray(interpreter);

    // Test 64 bit vector negate
    interpreter->getReg(_r2).u32() = testSize/sizeof(uint64);
    interpreter->getReg(_r0).pU8() = interpreter->getReg(_r1).pU8();
    printf("Testing 64-bit vector negate (overwriting self) #2...\n");
    code[2] = VMDefs::_VEC1<<8 | VMDefs::_VNEG_S64;
    interpreter->setPC(code);
    interpreter->execute();
    dumpTestArray(interpreter);

    delete interpreter;
  }
  return 0;
}

