//****************************************************************************//
//**                                                                        **//
//** File:         op_convert_code.hpp                                      **//
//** Description:  Conversion group opcode implementation                   **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2001-09-10                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

// CAST WIDENING ///////////////////////////////////////////////////////////////

_DEFINE_OP(S8_2_S16) {
  vm->gpr[_RD(op)].s16() = (sint16)vm->gpr[_RS(op)].s8();
}
_END_OP

_DEFINE_OP(S8_2_S32) {
  vm->gpr[_RD(op)].s32() = (sint32)vm->gpr[_RS(op)].s8();
}
_END_OP


_DEFINE_OP(S16_2_S32) {
  vm->gpr[_RD(op)].s32() = (sint32)vm->gpr[_RS(op)].s16();
}
_END_OP


