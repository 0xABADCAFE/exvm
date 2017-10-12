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


_DEFINE_OP(MADD_F64) {
/*
  vm->gpr[_RD(op)].f64() = vm->gpr[_RS(op)].f64() * vm->gpr[_EX_U8_1].f64() + vm->gpr[_EX_U8_2].f64();
  ++vm->pc.extU16;
*/
  vm->gpr[(vArgs & 0x000F)].f64() = (
    vm->gpr[(vArgs & 0x00F0) >> 4].f64() *
    vm->gpr[(vArgs & 0x0F00) >> 8].f64()
  ) + vm->gpr[(vArgs & 0xF000) >> 12].f64();
}
_END_OP
