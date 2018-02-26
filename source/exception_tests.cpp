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

class ExceptionHandler : public HostHelper {
  public:
    static void illegalOpcode(Interpreter* vm) {
      std::printf("Invoking illegal opcode handler for instruction %04X\n", (unsigned) *(getPC(vm) - 1));
      setStatus(vm, VMDefs::RUNNING);
    }

    static void zeroDivide(Interpreter* vm) {
      std::printf("Invoking illegal opcode handler for instruction %04X\n", (unsigned) *(getPC(vm) - 1));
      setStatus(vm, VMDefs::RUNNING);
    }
};

int main() {
  Interpreter* interpreter = Interpreter::create(Interpreter::TYPE_DEBUGGING);
  if (interpreter) {

    interpreter->setExceptionHandler(VMDefs::ILLEGAL_OPCODE, ExceptionHandler::illegalOpcode);
    interpreter->setExceptionHandler(VMDefs::ZERO_DIVIDE,    ExceptionHandler::zeroDivide);

    uint16 code[] = {
      0xFF00,    // Illegal
      _div_s32(_r0, _r1)
      _ret
    };

    interpreter->setPC(code);
    interpreter->execute();

    interpreter->dump();

    delete interpreter;
  }

  return 0;
}
