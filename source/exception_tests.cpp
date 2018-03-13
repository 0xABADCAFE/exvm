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
      std::printf("\n-------------------------------------\nInvoking illegal opcode handler for instruction %04X\n", (unsigned) *getExceptingInstruction(vm));
      setStatus(vm, VMDefs::RUNNING);
      std::puts("Kept calm and carried on.\n-------------------------------------\n");
    }

    static void zeroDivide(Interpreter* vm) {
      std::printf("\n-------------------------------------\nInvoking zero divide handler for instruction %04X\n", (unsigned) *getExceptingInstruction(vm));
      setStatus(vm, VMDefs::RUNNING);
      std::puts("Kept calm and carried on.\n-------------------------------------\n");
    }

    static void unknownCall(Interpreter* vm) {
      std::printf("\n-------------------------------------\nInvoking unknown call handler for instruction %04X\n", (unsigned) *getExceptingInstruction(vm));
      setStatus(vm, VMDefs::RUNNING);
      std::puts("Kept calm and carried on.\n-------------------------------------\n");
    }
};

int main() {
  Interpreter* interpreter = Interpreter::create(Interpreter::TYPE_DEBUGGING);
  if (interpreter) {

    interpreter->setExceptionHandler(VMDefs::ILLEGAL_OPCODE,      ExceptionHandler::illegalOpcode);
    interpreter->setExceptionHandler(VMDefs::ZERO_DIVIDE,         ExceptionHandler::zeroDivide);
    interpreter->setExceptionHandler(VMDefs::UNKNOWN_CODE_SYMBOL, ExceptionHandler::unknownCall);

    uint32 sym_id_unknown = 1234;

    uint16 code[] = {
      0xFF00,             // Illegal opcode
      _div_s32(_r0, _r1)  // Divide by zero
      _call(unknown)      // Unknown callable symbol
      VMDefs::_VEC1 << 8 | 0xFF, 0xABCD, // Bogus vector operation
      _ret
    };

    interpreter->setPC(code);
    interpreter->execute();

    interpreter->dump();

    delete interpreter;
  }

  return 0;
}
