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

#if _VM_INTERPRETER == _VM_INTERPRETER_SWITCH_CASE

_DEFINE_OP(BCALL8) {
  doBCALL8(vm, op);
  if (vm->status != VMDefs::RUNNING) {
    vm->exceptionOffset = EXC_OFFSET_STD;
    _HALT
  }
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(BCALL16) {
  doBCALL16(vm, op);
  if (vm->status != VMDefs::RUNNING) {
    vm->exceptionOffset = EXC_OFFSET_EXT;
    _HALT
  }
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(CALL) {
  doCALL(vm, op);
  if (vm->status != VMDefs::RUNNING) {
    vm->exceptionOffset = EXC_OFFSET_EXT;
    _HALT
  }
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(CALLN) {
  doCALLN(vm, op);
  if (vm->status != VMDefs::RUNNING) {
    vm->exceptionOffset = EXC_OFFSET_EXT;
    _HALT
  }
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(ICALL) {
  doICALL(vm, op);
  if (vm->status != VMDefs::RUNNING) {
    vm->exceptionOffset = EXC_OFFSET_STD;
    _HALT
  }
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(ICALLN) {
  doICALLN(vm, op);
  if (vm->status != VMDefs::RUNNING) {
    vm->exceptionOffset = EXC_OFFSET_STD;
    _HALT
  }
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(RET) {
  DEBUG_RETURN
  if (vm->callStack > vm->callStackBase) {
    vm->pc.inst = (const uint16*) *(--vm->callStack);
  } else {
    vm->status = VMDefs::COMPLETED;
    _HALT
  }
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(BRA8) {
  DEBUG_BRANCH_UNCONDITIONAL
  vm->pc.inst += _B8(op);
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(BRA16) {
  DEBUG_BRANCH_UNCONDITIONAL
  // for clarity, since _EX_S16 macro increments pc
  _DECLARE_OFFSET
  vm->pc.inst += offset;
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(CASE) {
  sint32 offset = _EX_U16;
  offset += vm->pc.extS16[vm->gpr[_RD(op)].u16()];
  vm->pc.inst += offset;
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(BNZ_8) {
  _DECLARE_OFFSET
  if (vm->gpr[_RD(op)].s8()) {
    vm->pc.inst += offset;
    DEBUG_BRANCH_TAKEN
  }
  DEBUG_BRANCH_NOT_TAKEN
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(BNZ_16) {
  _DECLARE_OFFSET
  if (vm->gpr[_RD(op)].s16()) {
    vm->pc.inst += offset;
    DEBUG_BRANCH_TAKEN
  }
  DEBUG_BRANCH_NOT_TAKEN
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(BNZ_32) {
  _DECLARE_OFFSET
  if (vm->gpr[_RD(op)].s32()) {
    vm->pc.inst += offset;
    DEBUG_BRANCH_TAKEN
  }
  DEBUG_BRANCH_NOT_TAKEN
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(BEQ_8) {
  _DECLARE_OFFSET
  if (vm->gpr[_RD(op)].s8() == vm->gpr[_RS(op)].s8()) {
    vm->pc.inst += offset;
    DEBUG_BRANCH_TAKEN
  }
  DEBUG_BRANCH_NOT_TAKEN
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(BEQ_16) {
  _DECLARE_OFFSET
  if (vm->gpr[_RD(op)].s16() == vm->gpr[_RS(op)].s16()) {
    vm->pc.inst += offset;
    DEBUG_BRANCH_TAKEN
  }
  DEBUG_BRANCH_NOT_TAKEN
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(BEQ_32) {
  _DECLARE_OFFSET
  if (vm->gpr[_RD(op)].s32() == vm->gpr[_RS(op)].s32()) {
    vm->pc.inst += offset;
    DEBUG_BRANCH_TAKEN
  }
  DEBUG_BRANCH_NOT_TAKEN
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(BGREQ_8) {
  _DECLARE_OFFSET
  if (vm->gpr[_RD(op)].s8() <= vm->gpr[_RS(op)].s8()) {
    vm->pc.inst += offset;
    DEBUG_BRANCH_TAKEN
  }
  DEBUG_BRANCH_NOT_TAKEN
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(BGREQ_16) {
  _DECLARE_OFFSET
  if (vm->gpr[_RD(op)].s16() <= vm->gpr[_RS(op)].s16()) {
    vm->pc.inst += offset;
    DEBUG_BRANCH_TAKEN
  }
  DEBUG_BRANCH_NOT_TAKEN
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(BGREQ_32) {
  _DECLARE_OFFSET
  if (vm->gpr[_RD(op)].s32() <= vm->gpr[_RS(op)].s32()) {
    vm->pc.inst += offset;
    DEBUG_BRANCH_TAKEN
  }
  DEBUG_BRANCH_NOT_TAKEN
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(BGR_8) {
  _DECLARE_OFFSET
  if (vm->gpr[_RD(op)].s8() < vm->gpr[_RS(op)].s8()) {
    vm->pc.inst += offset;
    DEBUG_BRANCH_TAKEN
  }
  DEBUG_BRANCH_NOT_TAKEN
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(BGR_16) {
  _DECLARE_OFFSET
  if (vm->gpr[_RD(op)].s16() < vm->gpr[_RS(op)].s16()) {
    vm->pc.inst += offset;
    DEBUG_BRANCH_TAKEN
  }
  DEBUG_BRANCH_NOT_TAKEN
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(BGR_32) {
  _DECLARE_OFFSET
  if (vm->gpr[_RD(op)].s32() < vm->gpr[_RS(op)].s32()) {
    vm->pc.inst += offset;
    DEBUG_BRANCH_TAKEN
  }
  DEBUG_BRANCH_NOT_TAKEN
}
_END_OP

