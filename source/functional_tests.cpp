//****************************************************************************//
//**                                                                        **//
//** File:         functional_tests.cpp                                     **//
//** Description:  Functional Test Application                              **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2017-09-09                                               **//
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

using namespace ExVM;
using namespace std;

namespace ExVM {
  class FunctionalTest {

    public:
      static void run(Interpreter* vm) {
        printf("Interpreter %p\n", vm);
        printf("Registers   %p\n", vm->gpr);
        printf("Data Stack Base %p\n", vm->dataStackBase);
        printf("Call Stack Base %p\n", vm->callStackBase);
        printf("Regs Stack Base %p\n", vm->regStackBase);
      }

  };
}

class IllegalOpcodeTest : public FunctionalTest {
  public:
    static void run(Interpreter* vm) {

    }
};

int main() {
  Interpreter* interpreter = Interpreter::create(Interpreter::TYPE_DEBUGGING);
  if (interpreter) {
    IllegalOpcodeTest::run(interpreter);

    delete interpreter;
  }

  return 0;
}
