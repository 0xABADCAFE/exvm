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
#include "include/vm_linker.hpp"
#include "include/vm_interpreter_standard.hpp"
#include "include/vm_interpreter_debugging.hpp"
#include <cstdio>

void ExVM::StandardInterpreter::doSV(ExVM::StandardInterpreter* vm, uint16 op UNUSED) {
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
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ExVM::StandardInterpreter::doRS(ExVM::StandardInterpreter* vm, uint16 op UNUSED) {
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
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ExVM::StandardInterpreter::doPUSH_8(ExVM::StandardInterpreter* vm, uint16 op UNUSED) {
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
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ExVM::StandardInterpreter::doPUSH_16(ExVM::StandardInterpreter* vm, uint16 op UNUSED) {
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
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ExVM::StandardInterpreter::doPUSH_32(ExVM::StandardInterpreter* vm, uint16 op UNUSED) {
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
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ExVM::StandardInterpreter::doPUSH_64(ExVM::StandardInterpreter* vm, uint16 op UNUSED) {
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
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ExVM::StandardInterpreter::doPOP_8(ExVM::StandardInterpreter* vm, uint16 op UNUSED) {
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
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ExVM::StandardInterpreter::doPOP_16(ExVM::StandardInterpreter* vm, uint16 op UNUSED) {
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
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ExVM::StandardInterpreter::doPOP_32(ExVM::StandardInterpreter* vm, uint16 op UNUSED) {
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
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ExVM::StandardInterpreter::doPOP_64(ExVM::StandardInterpreter* vm, uint16 op UNUSED) {
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
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ExVM::StandardInterpreter::doSALLOC(ExVM::StandardInterpreter* vm, uint16 op) {
  uint16 size =  _EX_U16;
  if ((vm->dataStack.u8 + size) < vm->dataStackTop) {
    vm->gpr[_RD(op)].pU8() = vm->dataStack.u8;
    vm->dataStack.u8 += size;
  } else {
    vm->status = VMDefs::DATA_STACK_OVERFLOW;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ExVM::StandardInterpreter::doSFREE(ExVM::StandardInterpreter* vm, uint16 op) {
  uint8* last = vm->gpr[_RD(op)].pU8();
  if (last < vm->dataStackBase) {
    vm->status = VMDefs::DATA_STACK_UNDERFLOW;
  } else if (last >= vm->dataStackTop) {
    vm->status = VMDefs::DATA_STACK_OVERFLOW;
  } else {
    vm->dataStack.u8 = last;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ExVM::StandardInterpreter::doBCALL8(ExVM::StandardInterpreter* vm, uint16 op) {
  if (vm->callStack < vm->callStackTop) {
    *vm->callStack++ = (uint16*)vm->pc.inst;
    vm->pc.inst += _B8(op);
  } else {
    vm->status = VMDefs::CALL_STACK_OVERFLOW;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ExVM::StandardInterpreter::doBCALL16(ExVM::StandardInterpreter* vm, uint16 op UNUSED) {
  if (vm->callStack < vm->callStackTop) {
    // for clarity, since _EX_S16 macro increments pc
    _DECLARE_OFFSET
    *vm->callStack++ = (uint16*)vm->pc.inst;
    vm->pc.inst += offset;
  } else {
    vm->status = VMDefs::CALL_STACK_OVERFLOW;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ExVM::StandardInterpreter::doCALL(ExVM::StandardInterpreter* vm, uint16 op) {
  uint32 symbol = (uint32)_EX_U16 | ((uint32)op & 0x0F) << 16;
  if (symbol >= vm->codeSymbolCount) {
    vm->status = VMDefs::UNKNOWN_CODE_SYMBOL;
    return;
  }

  const uint16* newPC = vm->codeSymbol[symbol];
  //printf("call 0x%08X\n", (unsigned)newPC);
  if (vm->callStack < vm->callStackTop) {
    *vm->callStack++ = (uint16*)vm->pc.inst;
    vm->pc.inst = newPC;
  } else {
    vm->status = VMDefs::CALL_STACK_OVERFLOW;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ExVM::StandardInterpreter::doCALLN(ExVM::StandardInterpreter* vm, uint16 op) {

  uint32 symbol = (uint32)_EX_U16 | ((uint32)op & 0x0F) << 16;
  if (symbol >= vm->nativeCodeSymbolCount) {
    vm->status = VMDefs::UNKNOWN_NATIVE_CODE_SYMBOL;
    return;
  }
  NativeCall func = vm->nativeCodeSymbol[symbol];
  if (func) {
    func(vm);
  } else {
    vm->status = VMDefs::CALL_EMPTY_NATIVE;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ExVM::StandardInterpreter::doICALL(ExVM::StandardInterpreter* vm, uint16 op) {
  uint32 symbol = vm->gpr[_RS(op)].u32();

  if ( (symbol & RawSegmentData::TYPE_MASK) != RawSegmentData::TYPE_CODE) {
    vm->status = VMDefs::ILLEGAL_CALLABLE_SYMBOL;
    return;
  }

  // Mask off the type to get the actual symbol
  symbol &= ~RawSegmentData::TYPE_MASK;

  if (symbol >= vm->codeSymbolCount) {
    vm->status = VMDefs::UNKNOWN_CODE_SYMBOL;
    return;
  }

  const uint16* newPC = vm->codeSymbol[symbol];
  //printf("call 0x%08X\n", (unsigned)newPC);
  if (vm->callStack < vm->callStackTop) {
    *vm->callStack++ = (uint16*)vm->pc.inst;
    vm->pc.inst = newPC;
  } else {
    vm->status = VMDefs::CALL_STACK_OVERFLOW;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ExVM::StandardInterpreter::doICALLN(ExVM::StandardInterpreter* vm, uint16 op) {

  uint32 symbol = vm->gpr[_RS(op)].u32();

  if ( (symbol & RawSegmentData::TYPE_MASK) != RawSegmentData::TYPE_NATIVE) {
    vm->status = VMDefs::ILLEGAL_CALLABLE_SYMBOL;
    return;
  }

  // Mask off the type to get the actual symbol
  symbol &= ~RawSegmentData::TYPE_MASK;

  if (symbol >= vm->nativeCodeSymbolCount) {
    vm->status = VMDefs::UNKNOWN_NATIVE_CODE_SYMBOL;
    return;
  }
  NativeCall func = vm->nativeCodeSymbol[symbol];
  if (func) {
    func(vm);
  } else {
    vm->status = VMDefs::CALL_EMPTY_NATIVE;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// DebuggingInterpreter
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ExVM::DebuggingInterpreter::doSV(ExVM::DebuggingInterpreter* vm, uint16 op UNUSED) {
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

void ExVM::DebuggingInterpreter::doRS(ExVM::DebuggingInterpreter* vm, uint16 op UNUSED) {
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

void ExVM::DebuggingInterpreter::doPUSH_8(ExVM::DebuggingInterpreter* vm, uint16 op UNUSED) {
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

void ExVM::DebuggingInterpreter::doPUSH_16(ExVM::DebuggingInterpreter* vm, uint16 op UNUSED) {
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

void ExVM::DebuggingInterpreter::doPUSH_32(ExVM::DebuggingInterpreter* vm, uint16 op UNUSED) {
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

void ExVM::DebuggingInterpreter::doPUSH_64(ExVM::DebuggingInterpreter* vm, uint16 op UNUSED) {
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

void ExVM::DebuggingInterpreter::doPOP_8(ExVM::DebuggingInterpreter* vm, uint16 op UNUSED) {
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

void ExVM::DebuggingInterpreter::doPOP_16(ExVM::DebuggingInterpreter* vm, uint16 op UNUSED) {
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

void ExVM::DebuggingInterpreter::doPOP_32(ExVM::DebuggingInterpreter* vm, uint16 op UNUSED) {
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

void ExVM::DebuggingInterpreter::doPOP_64(ExVM::DebuggingInterpreter* vm, uint16 op UNUSED) {
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

void ExVM::DebuggingInterpreter::doSALLOC(ExVM::DebuggingInterpreter* vm, uint16 op) {
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

void ExVM::DebuggingInterpreter::doSFREE(ExVM::DebuggingInterpreter* vm, uint16 op) {
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

void ExVM::DebuggingInterpreter::doBCALL8(ExVM::DebuggingInterpreter* vm, uint16 op) {
  if (vm->callStack < vm->callStackTop) {
    *vm->callStack++ = (uint16*)vm->pc.inst;
    vm->pc.inst += _B8(op);
    if (vm->debugFlags & FLAG_LOG_CALLS) {
      debuglog(LOG_INFO, "Branch call to offset %d", (int)_B8(op));
    }
    ++vm->branchCalls;
  } else {
    vm->status = VMDefs::CALL_STACK_OVERFLOW;
    debuglog(LOG_ERROR, "Call stack overflow in BCALL8");
    dumpstate(vm);

  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ExVM::DebuggingInterpreter::doBCALL16(ExVM::DebuggingInterpreter* vm, uint16 op UNUSED) {

  if (vm->callStack < vm->callStackTop) {
    // for clarity, since _EX_S16 macro increments pc
    _DECLARE_OFFSET
    *vm->callStack++ = (uint16*)vm->pc.inst;
    vm->pc.inst += offset;
    if (vm->debugFlags & FLAG_LOG_CALLS) {
      debuglog(LOG_INFO, "Branch call to offset %d", (int)offset);
    }
    ++vm->branchCalls;
  } else {
    vm->status = VMDefs::CALL_STACK_OVERFLOW;
    debuglog(LOG_ERROR, "Call stack overflow in BCALL16");
    dumpstate(vm);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ExVM::DebuggingInterpreter::doCALL(ExVM::DebuggingInterpreter* vm, uint16 op) {
  uint32 symbol = (uint32)_EX_U16 | ((uint32)op & 0x0F) << 16;

  if (symbol >= vm->codeSymbolCount) {
    vm->status = VMDefs::UNKNOWN_CODE_SYMBOL;
    debuglog(LOG_ERROR, "Unknown code symbol %d in CALL", (int)symbol);
    dumpstate(vm);
    return;
  }

  const uint16* newPC = vm->codeSymbol[symbol];

  if (vm->callStack < vm->callStackTop) {
    *vm->callStack++ = (uint16*)vm->pc.inst;
    vm->pc.inst = newPC;
    ++vm->functionCalls;
    if (vm->debugFlags & FLAG_LOG_CALLS) {
      debuglog(LOG_INFO, "Calling %d", (int)symbol);
    }

  } else {
    vm->status = VMDefs::CALL_STACK_OVERFLOW;
    debuglog(LOG_ERROR, "Call stack overflow in CALL");
    dumpstate(vm);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ExVM::DebuggingInterpreter::doCALLN(ExVM::DebuggingInterpreter* vm, uint16 op) {

  uint32 symbol = (uint32)_EX_U16 | ((uint32)op & 0x0F) << 16;
  if (symbol >= vm->nativeCodeSymbolCount) {
    vm->status = VMDefs::UNKNOWN_NATIVE_CODE_SYMBOL;
    debuglog(LOG_ERROR, "Unknown native code symbol %d in CALLN", (int)symbol);
    dumpstate(vm);
    return;
  }

  NativeCall func = vm->nativeCodeSymbol[symbol];
  if (func) {
    if (vm->debugFlags & FLAG_LOG_NATIVE_CALLS) {
      debuglog(LOG_INFO, "Calling native %d", (int)symbol);
    }
    ++vm->nativeFunctionCalls;

    MilliClock native;
    func(vm);
    vm->nativeTime += native.elapsedFrac();

    if (vm->debugFlags & FLAG_LOG_NATIVE_CALLS) {
      debuglog(LOG_INFO, "Returned from native");
    }

  } else {
    vm->status = VMDefs::CALL_EMPTY_NATIVE;
    debuglog(LOG_ERROR, "Empty native address in CALLN");
    dumpstate(vm);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ExVM::DebuggingInterpreter::doICALL(ExVM::DebuggingInterpreter* vm, uint16 op) {
  uint32 symbol = vm->gpr[_RS(op)].u32();

  if ( (symbol & RawSegmentData::TYPE_MASK) != RawSegmentData::TYPE_CODE) {
    vm->status = VMDefs::ILLEGAL_CALLABLE_SYMBOL;
    debuglog(LOG_ERROR, "Invalid code symbol %d in CALL", (int)symbol);
    dumpstate(vm);
    return;
  }

  // Mask off the type to get the actual symbol
  symbol &= ~RawSegmentData::TYPE_MASK;

  if (symbol >= vm->codeSymbolCount) {
    vm->status = VMDefs::UNKNOWN_CODE_SYMBOL;
    debuglog(LOG_ERROR, "Unknown code symbol %d in CALL", (int)symbol);
    dumpstate(vm);
    return;
  }

  const uint16* newPC = vm->codeSymbol[symbol];
  if (vm->callStack < vm->callStackTop) {
    *vm->callStack++ = (uint16*)vm->pc.inst;
    vm->pc.inst = newPC;
    ++vm->functionCalls;
    if (vm->debugFlags & FLAG_LOG_CALLS) {
      debuglog(LOG_INFO, "Calling %d", (int)symbol);
    }
  } else {
    vm->status = VMDefs::CALL_STACK_OVERFLOW;
    debuglog(LOG_ERROR, "Call stack overflow in CALL");
    dumpstate(vm);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ExVM::DebuggingInterpreter::doICALLN(ExVM::DebuggingInterpreter* vm, uint16 op) {

  uint32 symbol = vm->gpr[_RS(op)].u32();

  if ( (symbol & RawSegmentData::TYPE_MASK) != RawSegmentData::TYPE_NATIVE) {
    vm->status = VMDefs::ILLEGAL_CALLABLE_SYMBOL;
    debuglog(LOG_ERROR, "Invalid native symbol %d in CALL", (int)symbol);
    dumpstate(vm);
    return;
  }

  // Mask off the type to get the actual symbol
  symbol &= ~RawSegmentData::TYPE_MASK;

  if (symbol >= vm->nativeCodeSymbolCount) {
    vm->status = VMDefs::UNKNOWN_NATIVE_CODE_SYMBOL;
    debuglog(LOG_ERROR, "Unknown native code symbol %d in CALLN", (int)symbol);
    dumpstate(vm);
    return;
  }


  NativeCall func = vm->nativeCodeSymbol[symbol];
  if (func) {

    if (vm->debugFlags & FLAG_LOG_NATIVE_CALLS) {
      debuglog(LOG_INFO, "Calling native %d", (int)symbol);
    }
    ++vm->nativeFunctionCalls;
    MilliClock native;
    func(vm);
    vm->nativeTime += native.elapsedFrac();

    if (vm->debugFlags & FLAG_LOG_NATIVE_CALLS) {
      debuglog(LOG_INFO, "Returned from native");
    }

  } else {
    vm->status = VMDefs::CALL_EMPTY_NATIVE;
    debuglog(LOG_ERROR, "Empty native address in CALLN");
    dumpstate(vm);
  }
}

