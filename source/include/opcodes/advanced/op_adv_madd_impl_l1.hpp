//****************************************************************************//
//**                                                                        **//
//** File:         op_adv_madd_impl.hpp                                     **//
//** Description:  Multiply-Add                                             **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2017-08-19                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

_DEFINE_OP(MADD_F32) {
/*
  vm->gpr[_RD(op)].f32() = vm->gpr[_RS(op)].f32() * vm->gpr[_EX_U8_1].f32() + vm->gpr[_EX_U8_2].f32();
  ++vm->pc.extU16;
*/
  vm->gpr[VARG0].f32() = (
    vm->gpr[VARG1].f32() *
    vm->gpr[VARG2].f32()
  ) + vm->gpr[VARG3].f32();
}
_END_OP

