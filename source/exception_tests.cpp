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

  private:
    static void illegalOpcode(Interpreter* vm) {
      keepCalmAndCarryOn(vm, "Illegal Opcode");
    }

    static void zeroDivide(Interpreter* vm) {
      keepCalmAndCarryOn(vm, "Divide by Zero");
    }

    static void unknownCall(Interpreter* vm) {
      keepCalmAndCarryOn(vm, "Unknown Code Symbol");
    }

    static void unknownData(Interpreter* vm) {
      keepCalmAndCarryOn(vm, "Unknown Data Symbol");
    }

    static void unknownNative(Interpreter* vm) {
      keepCalmAndCarryOn(vm, "Unknown Native Symbol");
    }

    static void dataStackUnderflow(Interpreter* vm) {
      keepCalmAndCarryOn(vm, "Data Stack Underflow");
    }

    static void keepCalmAndCarryOn(Interpreter* vm, const char* note) {
      std::printf("Invoked %s handler for instruction %04X\n", note, (unsigned) *getExceptingInstruction(vm));
      setStatus(vm, VMDefs::RUNNING);
    }

  public:
    static void setHandlers(Interpreter* vm) {
      vm->setExceptionHandler(VMDefs::ILLEGAL_OPCODE,             illegalOpcode);
      vm->setExceptionHandler(VMDefs::ZERO_DIVIDE,                zeroDivide);
      vm->setExceptionHandler(VMDefs::UNKNOWN_CODE_SYMBOL,        unknownCall);
      vm->setExceptionHandler(VMDefs::UNKNOWN_DATA_SYMBOL,        unknownData);
      vm->setExceptionHandler(VMDefs::UNKNOWN_NATIVE_CODE_SYMBOL, unknownNative);
      vm->setExceptionHandler(VMDefs::DATA_STACK_UNDERFLOW,       dataStackUnderflow);
    }
};

int main() {
  Interpreter* interpreter = Interpreter::create(Interpreter::TYPE_DEBUGGING);
  if (interpreter) {

    ExceptionHandler::setHandlers(interpreter);

    uint32 sym_id_unknown = 1234;

    uint16 code[] = {
      0xFF00,                            // Bogus Scalar operation
      VMDefs::_ADV << 8  | 0xFF, 0xABCD, // Bogus advanced operation
      VMDefs::_VEC1 << 8 | 0xFF, 0xABCD, // Bogus vector operation
      _div_s32(_r0, _r1)                 // Divide by zero
      _call(unknown)                     // Unknown callable symbol
      _calln(unknown)                    // Unknown native code symbol
      _ld_32(unknown, _r2)               // Unknown data symbol
      _pop_16(0xFFFF)                    // data stack underflow
      _ret
    };

    interpreter->setPC(code);
    interpreter->execute();

    if (interpreter->getStatus() != VMDefs::COMPLETED) {
      std::printf("Execution terminated with an unhandled exception case.\n");
      interpreter->dump();
    } else {
      std::printf("Execution completed with no unhandled exception cases.\n");
    }

    delete interpreter;
  }

  return 0;
}
