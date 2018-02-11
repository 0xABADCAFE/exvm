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

_DEFINE_OP(BNZ_64) {
  _DECLARE_OFFSET
  if (vm->gpr[_RD(op)].s64()) {
    vm->pc.inst += offset;
    DEBUG_BRANCH_TAKEN
  }
  DEBUG_BRANCH_NOT_TAKEN
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(BEQ_64) {
  _DECLARE_OFFSET
  if (vm->gpr[_RD(op)].s64() == vm->gpr[_RS(op)].s64()) {
    vm->pc.inst += offset;
    DEBUG_BRANCH_TAKEN
  }
  DEBUG_BRANCH_NOT_TAKEN
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(BEQ_F64) {
  _DECLARE_OFFSET
  if (vm->gpr[_RD(op)].f64() == vm->gpr[_RS(op)].f64()) {
    vm->pc.inst += offset;
    DEBUG_BRANCH_TAKEN
  }
  DEBUG_BRANCH_NOT_TAKEN
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(BGREQ_64) {
  _DECLARE_OFFSET
  if (vm->gpr[_RD(op)].s64() <= vm->gpr[_RS(op)].s64()) {
    vm->pc.inst += offset;
    DEBUG_BRANCH_TAKEN
  }
  DEBUG_BRANCH_NOT_TAKEN
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(BGREQ_F64) {
  _DECLARE_OFFSET
  if (vm->gpr[_RD(op)].f64() <= vm->gpr[_RS(op)].f64()) {
    vm->pc.inst += offset;
    DEBUG_BRANCH_TAKEN
  }
  DEBUG_BRANCH_NOT_TAKEN
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(BGR_64) {
  _DECLARE_OFFSET
  if (vm->gpr[_RD(op)].s64() < vm->gpr[_RS(op)].s64()) {
    vm->pc.inst += offset;
    DEBUG_BRANCH_TAKEN
  }
  DEBUG_BRANCH_NOT_TAKEN
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(BGR_F64) {
  _DECLARE_OFFSET
  if (vm->gpr[_RD(op)].f64() < vm->gpr[_RS(op)].f64()) {
    vm->pc.inst += offset;
    DEBUG_BRANCH_TAKEN
  }
  DEBUG_BRANCH_NOT_TAKEN
}
_END_OP

