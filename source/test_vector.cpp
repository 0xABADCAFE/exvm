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

uint8 test[256] = { 0 };

void dumpTestArray() {
  printf("Target array:");
  for (int i = 0; i < sizeof(test); i++) {
    if (!(i & 0xF)) {
      putchar('\n');
    }
    printf("0x%02X ", test[i]);
  }
  putchar('\n');
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
  // Create an Interpreter
  Interpreter* interpreter = new Interpreter();
  if (interpreter) {
    dumpTestArray();

    uint16 code[] = {
      VMDefs::_VEC<<8 | VMDefs::_VFILL_8, 0x0012,
      _ret
    };

    interpreter->getReg(_r0).u64() = 0x0123456789ABCDEFULL;
    interpreter->getReg(_r1).pU8() = test;
    interpreter->getReg(_r2).u32() = sizeof(test);

    // Test 8 bit vector fill
    interpreter->setPC(code);
    interpreter->execute();
    dumpTestArray();

    // test 16 bit vector fill
    code[0] = VMDefs::_VEC<<8 | VMDefs::_VFILL_16;
    interpreter->setPC(code);
    interpreter->execute();
    dumpTestArray();

    // test 32 bit vector fill
    code[0] = VMDefs::_VEC<<8 | VMDefs::_VFILL_32;
    interpreter->setPC(code);
    interpreter->execute();
    dumpTestArray();

    // test 32 bit vector fill
    code[0] = VMDefs::_VEC<<8 | VMDefs::_VFILL_64;
    interpreter->setPC(code);
    interpreter->execute();
    dumpTestArray();


    delete interpreter;
  }
  return 0;
}

