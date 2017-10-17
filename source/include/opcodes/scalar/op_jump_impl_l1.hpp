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

_DEFINE_OP(BEQ_F32) {
  _DECLARE_OFFSET
  if (vm->gpr[_RD(op)].f32() == vm->gpr[_RS(op)].f32()) {
    vm->pc.inst += offset;
  }
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(BGREQ_F32) {
  _DECLARE_OFFSET
  if (vm->gpr[_RD(op)].f32() <= vm->gpr[_RS(op)].f32()) {
    vm->pc.inst += offset;
  }
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(BGR_F32) {
  _DECLARE_OFFSET
  if (vm->gpr[_RD(op)].f32() < vm->gpr[_RS(op)].f32()) {
    vm->pc.inst += offset;
  }
}
_END_OP

