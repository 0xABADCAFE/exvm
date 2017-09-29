//****************************************************************************//
//**                                                                        **//
//** File:         op_scalar.cpp                                            **//
//** Description:  Simple scalar opcode implementation                      **//
//** Comment(s):   Internal developer version only,                           **//
//** Library:                                                               **//
//** Created:      2017-09-29                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

#include "include/machine.hpp"
#include "include/vm_core.hpp"
#include "include/vm_inline.hpp"
#include <cstdio>

#if _VM_INTERPRETER == _VM_INTERPRETER_FUNC_TABLE

  #include "include/vm_interpreter_func_table.hpp"
  #include <cmath>

// Upon entry, the pc points to the 16-bit word following the current opcode.
// Normally, this would be the address of the next opcode. Handlers that use
// extension words must ensure that they increment the pc so that it points
// to the next opcode.

// Arguments:
// vm is a pointer to the VMCore instance
// op is the current opcode word

  #include "include/opcodes/scalar/op_control_impl.hpp"
  #include "include/opcodes/scalar/op_load_impl.hpp"
  #include "include/opcodes/scalar/op_store_impl.hpp"
  #include "include/opcodes/scalar/op_move_impl.hpp"
  #include "include/opcodes/scalar/op_jump_impl.hpp"
  #include "include/opcodes/scalar/op_convert_impl.hpp"
  #include "include/opcodes/scalar/op_arithmetic_impl.hpp"
  #include "include/opcodes/scalar/op_logic_impl.hpp"
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ExVM::Interpreter::doSV(ExVM::Interpreter* vm, uint16 op UNUSED) {
  uint16  mask  = _EX_U16;
  GPR*    r     = vm->gpr;

  while (mask && (vm->regStack < vm->regStackTop)) {
    if (mask & 0x0001) {
      *vm->regStack++ = r->u64();
    }
    ++r;
    mask >>= 1;
  }
  if (mask) {
    // not all the registers were saved, signifying an overflow
    vm->status = VMDefs::REG_STACK_OVERFLOW;
    debuglog(LOG_ERROR, "Register stack overflow");
    dumpstate(vm);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ExVM::Interpreter::doRS(ExVM::Interpreter* vm, uint16 op UNUSED) {
  uint16  mask  = _EX_U16;
  GPR*    r     = vm->gpr + GPR_LAST;
  while (mask && (vm->regStack > vm->regStackBase)) {
    if (mask & 0x8000) {
      r->u64() = *(--vm->regStack);
    }
    --r;
    mask<<=1;
  }
  if (mask) {
    // not all the registers were restored, signifying an underflow
    vm->status = VMDefs::REG_STACK_UNDERFLOW;
    debuglog(LOG_ERROR, "Register stack underflow");
    dumpstate(vm);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ExVM::Interpreter::doPUSH_8(ExVM::Interpreter* vm, uint16 op UNUSED) {
  uint16 mask =  _EX_U16;
  GPR*  r = vm->gpr;
  while (mask && (vm->dataStack.u8 < vm->dataStackTop)) {
    if (mask & 1) {
      *vm->dataStack.u16++ = r->u8();
    }
    r++;
    mask >>= 1;
  }
  if (mask) {
    // not all the data were pushed, signifying an overflow
    vm->status = VMDefs::DATA_STACK_OVERFLOW;
    debuglog(LOG_ERROR, "Data stack overflow in PUSH_8");
    dumpstate(vm);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ExVM::Interpreter::doPUSH_16(ExVM::Interpreter* vm, uint16 op UNUSED) {
  uint16 mask =  _EX_U16;
  GPR*  r = vm->gpr;
  while (mask && (vm->dataStack.u8 < vm->dataStackTop)) {
    if (mask & 1) {
      *vm->dataStack.u16++ = r->u16();
    }
    ++r;
    mask >>= 1;
  }
  if (mask) {
    // not all the data were pushed, signifying an overflow
    vm->status = VMDefs::DATA_STACK_OVERFLOW;
    debuglog(LOG_ERROR, "Data stack overflow in PUSH_16");
    dumpstate(vm);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ExVM::Interpreter::doPUSH_32(ExVM::Interpreter* vm, uint16 op UNUSED) {
  uint16 mask =  _EX_U16;
  GPR*  r = vm->gpr;
  while (mask && (vm->dataStack.u8 < vm->dataStackTop)) {
    if (mask & 1) {
      *vm->dataStack.u32++ = r->u32();
    }
    ++r;
    mask >>= 1;
  }
  if (mask) {
    // not all the data were pushed, signifying an overflow
    vm->status = VMDefs::DATA_STACK_OVERFLOW;
    debuglog(LOG_ERROR, "Data stack overflow in PUSH_32");
    dumpstate(vm);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ExVM::Interpreter::doPUSH_64(ExVM::Interpreter* vm, uint16 op UNUSED) {
  uint16 mask =  _EX_U16;
  GPR*  r = vm->gpr;
  while (mask && (vm->dataStack.u8 < vm->dataStackTop)) {
    if (mask & 1) {
      *vm->dataStack.u64++ = r->u64();
    }
    ++r;
    mask >>= 1;
  }
  if (mask) {
    // not all the data were pushed, signifying an overflow
    vm->status = VMDefs::DATA_STACK_OVERFLOW;
    debuglog(LOG_ERROR, "Data stack overflow in PUSH_64");
    dumpstate(vm);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ExVM::Interpreter::doPOP_8(ExVM::Interpreter* vm, uint16 op UNUSED) {
  uint16 mask =  _EX_U16;
  GPR*  r = vm->gpr + GPR_LAST;
  while (mask && (vm->dataStack.u8 > vm->dataStackBase)) {
    if (mask & 0x8000) {
      r->u8() = *(--vm->dataStack.u16);
    }
    --r;
    mask <<= 1;
  }
  if (mask) {
    // not all the data were popped, signifying an underflow
    vm->status = VMDefs::DATA_STACK_UNDERFLOW;
    debuglog(LOG_ERROR, "Data stack underflow in POP_8");
    dumpstate(vm);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ExVM::Interpreter::doPOP_16(ExVM::Interpreter* vm, uint16 op UNUSED) {
  uint16 mask =  _EX_U16;
  GPR*  r = vm->gpr + GPR_LAST;
  while (mask && (vm->dataStack.u8 > vm->dataStackBase)) {
    if (mask & 0x8000) {
      r->u16() = *(--vm->dataStack.u16);
    }
    --r;
    mask <<= 1;
  }
  if (mask) {
    // not all the data were popped, signifying an underflow
    vm->status = VMDefs::DATA_STACK_UNDERFLOW;
    debuglog(LOG_ERROR, "Data stack underflow in POP_16");
    dumpstate(vm);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ExVM::Interpreter::doPOP_32(ExVM::Interpreter* vm, uint16 op UNUSED) {
  uint16 mask =  _EX_U16;
  GPR*  r = vm->gpr + GPR_LAST;
  while (mask && (vm->dataStack.u8 > vm->dataStackBase)) {
    if (mask & 0x8000) {
      r->u32() = *(--vm->dataStack.u32);
    }
    --r;
    mask <<= 1;
  }
  if (mask) {
    // not all the data were popped, signifying an underflow
    vm->status = VMDefs::DATA_STACK_UNDERFLOW;
    debuglog(LOG_ERROR, "Data stack underflow in POP_32");
    dumpstate(vm);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ExVM::Interpreter::doPOP_64(ExVM::Interpreter* vm, uint16 op UNUSED) {
  uint16 mask =  _EX_U16;
  GPR*  r = vm->gpr + GPR_LAST;
  while (mask && (vm->dataStack.u8 > vm->dataStackBase)) {
    if (mask & 0x8000) {
      r->u64() = *(--vm->dataStack.u64);
    }
    --r;
    mask <<= 1;
  }
  if (mask) {
    // not all the data were popped, signifying an underflow
    vm->status = VMDefs::DATA_STACK_UNDERFLOW;
    debuglog(LOG_ERROR, "Data stack underflow in POP_64");
    dumpstate(vm);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ExVM::Interpreter::doSALLOC(ExVM::Interpreter* vm, uint16 op) {
  uint16 size =  _EX_U16;
  if ((vm->dataStack.u8 + size) < vm->dataStackTop) {
    vm->gpr[_RD(op)].pU8() = vm->dataStack.u8;
    vm->dataStack.u8 += size;
  } else {
    vm->status = VMDefs::DATA_STACK_OVERFLOW;
    debuglog(LOG_ERROR, "Data stack overflow in SALLOC");
    dumpstate(vm);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ExVM::Interpreter::doSFREE(ExVM::Interpreter* vm, uint16 op) {
  uint8* last = vm->gpr[_RD(op)].pU8();
  if (last < vm->dataStackBase) {
    vm->status = VMDefs::DATA_STACK_UNDERFLOW;
    debuglog(LOG_ERROR, "Data stack underflow in SFREE");
    dumpstate(vm);
  } else if (last >= vm->dataStackTop) {
    vm->status = VMDefs::DATA_STACK_OVERFLOW;
    debuglog(LOG_ERROR, "Data stack overflow in SFREE");
    dumpstate(vm);
  } else {
    vm->dataStack.u8 = last;
  }
}

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

void ExVM::Interpreter::doBCALL16(ExVM::Interpreter* vm, uint16 op UNUSED) {
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
  uint32 symbol = (uint32)_EX_U16 | ((uint32)op & 0xFF) << 16;
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

  uint32 symbol = (uint32)_EX_U16 | ((uint32)op & 0xFF) << 16;
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

