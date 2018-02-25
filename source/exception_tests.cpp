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

namespace ExVM {
class FunctionalTest {

  protected:
    static void info(Interpreter* vm) {
      std::printf("Interpreter %p\n", vm);
      std::printf("Registers   %p\n", vm->gpr);
      std::printf("Data Stack Base %p\n", vm->dataStackBase);
      std::printf("Call Stack Base %p\n", vm->callStackBase);
      std::printf("Regs Stack Base %p\n", vm->regStackBase);
    }

    static void setStatus(Interpreter* vm, VMDefs::VMStatus status) {
      vm->status = status;
    }
};
}

class ExceptionHandler : public FunctionalTest {
  public:
    static void illegalOpcode(Interpreter* vm) {
      info(vm);
      setStatus(vm, VMDefs::RUNNING);
    }
};

int main() {
  Interpreter* interpreter = Interpreter::create(Interpreter::TYPE_DEBUGGING);
  if (interpreter) {

    interpreter->setExceptionHandler(VMDefs::ILLEGAL_OPCODE, ExceptionHandler::illegalOpcode);

    uint16 code[] = {
      0xFF00,    // Illegal
      _ret
    };

    interpreter->setPC(code);
    interpreter->execute();

    interpreter->dump();

    delete interpreter;
  }

  return 0;
}
