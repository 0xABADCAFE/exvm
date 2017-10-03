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
      static void dummy(Interpreter* vm) {
        printf("Data Stack Base %p\n", vm->dataStackBase);
      }

  };
}

class OpcodeTest : public FunctionalTest {

};

int main() {
  Interpreter* interpreter = new Interpreter();
  if (interpreter) {
    OpcodeTest::dummy(interpreter);

    delete interpreter;
  }

  return 0;
}
