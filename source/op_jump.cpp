//****************************************************************************//
//**                                                                        **//
//** File:         op_jump.cpp                                              **//
//** Description:  Jump group opcode implementation                         **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2001-08-29                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//
#include "include/vm_core.hpp"
#include "include/vm_inline.hpp"
#include "include/machine.hpp"
#include <cstdio>

#if _VM_INTERPRETER == _VM_INTERPRETER_FUNC_TABLE

  #include "include/vm_interpreter_func_table.hpp"


// Upon entry, the pc points to the 16-bit word following the current opcode.
// Normally, this would be the address of the next opcode. Handlers that use
// extension words must ensure that they increment the pc so that it points
// to the next opcode.

// Arguments:
// vm is a pointer to the VMCore instance
// op is the current opcode word

  #include "include/op_jump_impl.hpp"

#endif



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ExVM::Interpreter::doBCALL8(ExVM::Interpreter* vm, uint16 op) {
  if (vm->callStack < vm->callStackTop) {
    *vm->callStack++ = (uint16*)vm->pc.inst;
    vm->pc.inst += _B8(op);
  } else {
    vm->status = VMDefs::CALL_STACK_OVERFLOW;

    debuglog(LOG_ERROR, "Call stack overflow in BCALL8");
    dumpstate(vm);

  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ExVM::Interpreter::doBCALL16(ExVM::Interpreter* vm, uint16 op) {
  if (vm->callStack < vm->callStackTop) {
    // for clarity, since _EX_S16 macro increments pc
    _DECLARE_OFFSET
    *vm->callStack++ = (uint16*)vm->pc.inst;
    vm->pc.inst += offset;
  } else {
    vm->status = VMDefs::CALL_STACK_OVERFLOW;

    debuglog(LOG_ERROR, "Call stack overflow in BCALL16");
    dumpstate(vm);

  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ExVM::Interpreter::doCALL(ExVM::Interpreter* vm, uint16 op) {
  uint16 symbol = _EX_U16;
  if (symbol >= vm->codeSymbolCount) {
    vm->status = VMDefs::UNKNOWN_CODE_SYMBOL;

    debuglog(LOG_ERROR, "Unknown code symbold %d in CALL", (int)symbol);
    dumpstate(vm);

    return;
  }

  const uint16* newPC = vm->codeSymbol[symbol];
  //printf("call 0x%08X\n", (unsigned)newPC);
  if (vm->callStack < vm->callStackTop) {
    *vm->callStack++ = (uint16*)vm->pc.inst;
    vm->pc.inst = newPC;
  } else {
    vm->status = VMDefs::CALL_STACK_OVERFLOW;

    debuglog(LOG_ERROR, "Call stack overflow in CALL");
    dumpstate(vm);

  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ExVM::Interpreter::doCALLN(ExVM::Interpreter* vm, uint16 op) {

  uint16 symbol = _EX_U16;
  if (symbol >= vm->nativeCodeSymbolCount) {
    vm->status = VMDefs::UNKNOWN_NATIVE_CODE_SYMBOL;

    debuglog(LOG_ERROR, "Unknown native code symbold %d in CALLN", (int)symbol);
    dumpstate(vm);

    return;
  }
  NativeCall func = vm->nativeCodeSymbol[symbol];
  if (func) {
    MilliClock native;
    //printf("call native 0x%08X\n", (unsigned)func);
    func(vm);
    vm->nativeTime += native.elapsedFrac();
  } else {
    vm->status = VMDefs::CALL_EMPTY_NATIVE;

    debuglog(LOG_ERROR, "Empty native address in CALLN");
    dumpstate(vm);

  }
}

