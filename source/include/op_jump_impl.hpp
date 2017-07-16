//****************************************************************************//
//**                                                                        **//
//** File:         op_jump_code.hpp                                         **//
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

#if X_PTRSIZE == XA_PTRSIZE64
  #define _DECLARE_OFFSET sint64 offset = _EX_S16;
#else
  #define _DECLARE_OFFSET sint16 offset = _EX_S16;
#endif

////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(BCALL8) {
  if (vm->callStack < vm->callStackTop) {
    *vm->callStack++ = (uint16*)vm->pc.inst;
    vm->pc.inst += _B8(op);
  } else {
    vm->status = VMDefs::CALL_STACK_OVERFLOW;

#ifdef VM_FULL_DEBUG
    printf("Runtime error: call stack overflow\n");
    vm->dump();
#endif

    _THROW(-1)
  }
}
_END_OP

////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(BCALL16) {
  if (vm->callStack < vm->callStackTop) {
    // for clarity, since _EX_S16 macro increments pc
    _DECLARE_OFFSET
    *vm->callStack++ = (uint16*)vm->pc.inst;
    vm->pc.inst += offset;
  } else {
    vm->status = VMDefs::CALL_STACK_OVERFLOW;

#ifdef VM_FULL_DEBUG
    printf("Runtime error: call stack overflow\n");
    vm->dump();
#endif

    _THROW(-1)
  }

}
_END_OP

////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(CALL) {
  uint16 symbol = _EX_U16;
  if (symbol >= vm->codeSymbolCount) {
    vm->status = VMDefs::UNKNOWN_CODE_SYMBOL;

#ifdef VM_FULL_DEBUG
    printf("Runtime error: Unknown code symbold : %d\n", (int)symbol);
    vm->dump();
#endif

    _THROW(-1)
  }
  const uint16* newPC = vm->codeSymbol[symbol];
  //printf("call 0x%08X\n", (unsigned)newPC);
  if (vm->callStack < vm->callStackTop) {
    *vm->callStack++ = (uint16*)vm->pc.inst;
    vm->pc.inst = newPC;
  } else {
    vm->status = VMDefs::CALL_STACK_OVERFLOW;

#ifdef VM_FULL_DEBUG
    printf("Runtime error: call stack overflow\n");
    vm->dump();
#endif

    _THROW(-1)
  }
}
_END_OP

////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(CALLN) {
  uint16 symbol = _EX_U16;
  if (symbol >= vm->nativeCodeSymbolCount) {
    vm->status = VMDefs::UNKNOWN_NATIVE_CODE_SYMBOL;

#ifdef VM_FULL_DEBUG
    printf("Runtime error: Unknown native code symbold : %d\n", (int)symbol);
    vm->dump();
#endif

    _THROW(-1)
  }
  Native func = vm->nativeCodeSymbol[symbol];
  if (func) {
    MilliClock native;
    //printf("call native 0x%08X\n", (unsigned)func);
    func(vm);
    vm->nativeTime += native.elapsedFrac();
  } else {
    vm->status = VMDefs::CALL_EMPTY_NATIVE;

#ifdef VM_FULL_DEBUG
    printf("Runtime error: call native with null address\n");
    vm->dump();
#endif

    _THROW(-1)
  }
}
_END_OP

////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(RET) {
  if (vm->callStack > vm->callStackBase) {
    vm->pc.inst = (const uint16*) *(--vm->callStack);
  } else {
    vm->status = VMDefs::COMPLETED;
    _THROW(-1)
  }
}
_END_OP

_DEFINE_OP(BRA8) {
  vm->pc.inst += _B8(op);
}
_END_OP

_DEFINE_OP(BRA16) {
  //for clarity, since _EX_S16 macro increments pc
  _DECLARE_OFFSET
  vm->pc.inst += offset;
}
_END_OP

_DEFINE_OP(CASE) {
  sint32 offset = _EX_U16;
  offset += vm->pc.extS16[vm->gpr[_RD(op)].u16()];
  vm->pc.inst += offset;
}
_END_OP

_DEFINE_OP(BNZ_8) {
  _DECLARE_OFFSET
  if (vm->gpr[_RD(op)].s8()) {
    vm->pc.inst += offset;
  }
}
_END_OP

_DEFINE_OP(BNZ_16) {
  _DECLARE_OFFSET
  if (vm->gpr[_RD(op)].s16()) {
    vm->pc.inst += offset;
  }
}
_END_OP

_DEFINE_OP(BNZ_32) {
  _DECLARE_OFFSET
  if (vm->gpr[_RD(op)].s32()) {
    vm->pc.inst += offset;
  }
}
_END_OP

_DEFINE_OP(BNZ_64) {
  _DECLARE_OFFSET
  if (vm->gpr[_RD(op)].s64()) {
    vm->pc.inst += offset;
  }
}
_END_OP

_DEFINE_OP(BEQ_8) {
  _DECLARE_OFFSET
  if (vm->gpr[_RD(op)].s8() == vm->gpr[_RS(op)].s8()) {
    vm->pc.inst += offset;
  }
}
_END_OP

_DEFINE_OP(BEQ_16) {
  _DECLARE_OFFSET
  if (vm->gpr[_RD(op)].s16() == vm->gpr[_RS(op)].s16()) {
    vm->pc.inst += offset;
  }
}
_END_OP

_DEFINE_OP(BEQ_32) {
  _DECLARE_OFFSET
  if (vm->gpr[_RD(op)].s32() == vm->gpr[_RS(op)].s32()) {
    vm->pc.inst += offset;
  }
}
_END_OP

_DEFINE_OP(BEQ_64) {
  _DECLARE_OFFSET
  if (vm->gpr[_RD(op)].s64() == vm->gpr[_RS(op)].s64()) {
    vm->pc.inst += offset;
  }
}
_END_OP

_DEFINE_OP(BEQ_F32) {
  _DECLARE_OFFSET
  if (vm->gpr[_RD(op)].f32() == vm->gpr[_RS(op)].f32()) {
    vm->pc.inst += offset;
  }
}
_END_OP

_DEFINE_OP(BEQ_F64) {
  _DECLARE_OFFSET
  if (vm->gpr[_RD(op)].f64() == vm->gpr[_RS(op)].f64()) {
    vm->pc.inst += offset;
  }
}
_END_OP

_DEFINE_OP(BGREQ_8) {
  _DECLARE_OFFSET
  if (vm->gpr[_RD(op)].s8() <= vm->gpr[_RS(op)].s8()) {
    vm->pc.inst += offset;
  }
}
_END_OP

_DEFINE_OP(BGREQ_16) {
  _DECLARE_OFFSET
  if (vm->gpr[_RD(op)].s16() <= vm->gpr[_RS(op)].s16()) {
    vm->pc.inst += offset;
  }
}
_END_OP

_DEFINE_OP(BGREQ_32) {
  _DECLARE_OFFSET
  if (vm->gpr[_RD(op)].s32() <= vm->gpr[_RS(op)].s32()) {
    vm->pc.inst += offset;
  }
}
_END_OP

_DEFINE_OP(BGREQ_64) {
  _DECLARE_OFFSET
  if (vm->gpr[_RD(op)].s64() <= vm->gpr[_RS(op)].s64()) {
    vm->pc.inst += offset;
  }
}
_END_OP

_DEFINE_OP(BGREQ_F32) {
  _DECLARE_OFFSET
  if (vm->gpr[_RD(op)].f32() <= vm->gpr[_RS(op)].f32()) {
    vm->pc.inst += offset;
  }
}
_END_OP

_DEFINE_OP(BGREQ_F64) {
  _DECLARE_OFFSET
  if (vm->gpr[_RD(op)].f64() <= vm->gpr[_RS(op)].f64()) {
    vm->pc.inst += offset;
  }
}
_END_OP

_DEFINE_OP(BGR_8) {
  _DECLARE_OFFSET
  if (vm->gpr[_RD(op)].s8() < vm->gpr[_RS(op)].s8()) {
    vm->pc.inst += offset;
  }
}
_END_OP

_DEFINE_OP(BGR_16) {
  _DECLARE_OFFSET
  if (vm->gpr[_RD(op)].s16() < vm->gpr[_RS(op)].s16()) {
    vm->pc.inst += offset;
  }
}
_END_OP

_DEFINE_OP(BGR_32) {
  _DECLARE_OFFSET
  if (vm->gpr[_RD(op)].s32() < vm->gpr[_RS(op)].s32()) {
    vm->pc.inst += offset;
  }
}
_END_OP

_DEFINE_OP(BGR_64) {
  _DECLARE_OFFSET
  if (vm->gpr[_RD(op)].s64() < vm->gpr[_RS(op)].s64()) {
    vm->pc.inst += offset;
  }
}
_END_OP

_DEFINE_OP(BGR_F32) {
  _DECLARE_OFFSET
  if (vm->gpr[_RD(op)].f32() < vm->gpr[_RS(op)].f32()) {
    vm->pc.inst += offset;
  }
}
_END_OP

_DEFINE_OP(BGR_F64) {
  _DECLARE_OFFSET
  if (vm->gpr[_RD(op)].f64() < vm->gpr[_RS(op)].f64()) {
    vm->pc.inst += offset;
  }
}
_END_OP
