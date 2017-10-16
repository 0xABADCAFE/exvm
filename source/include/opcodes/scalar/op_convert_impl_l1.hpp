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

_DEFINE_OP(S8_2_F32) {
  vm->gpr[_RD(op)].f32() = (float32)vm->gpr[_RS(op)].s8();
}
_END_OP

_DEFINE_OP(S16_2_F32) {
  vm->gpr[_RD(op)].f32() = (float32)vm->gpr[_RS(op)].s16();
}
_END_OP

_DEFINE_OP(S32_2_F32) {
  vm->gpr[_RD(op)].f32() = (float32)vm->gpr[_RS(op)].s32();
}
_END_OP


_DEFINE_OP(U8_2_F32) {
  vm->gpr[_RD(op)].f32() = (float32)vm->gpr[_RS(op)].u8();
}
_END_OP

_DEFINE_OP(U16_2_F32) {
  vm->gpr[_RD(op)].f32() = (float32)vm->gpr[_RS(op)].u16();
}
_END_OP

_DEFINE_OP(U32_2_F32) {
  vm->gpr[_RD(op)].f32() = (float32)vm->gpr[_RS(op)].u32();
}
_END_OP


// CAST NARROWING //////////////////////////////////////////////////////////////

_DEFINE_OP(F32_2_S32) {
  vm->gpr[_RD(op)].s32() = (sint32)(vm->gpr[_RS(op)].f32());
}
_END_OP

_DEFINE_OP(F32_2_S16) {
  vm->gpr[_RD(op)].s16() = (sint16)(vm->gpr[_RS(op)].f32());
}
_END_OP

_DEFINE_OP(F32_2_S8) {
  vm->gpr[_RD(op)].s8() = (sint8)(vm->gpr[_RS(op)].f32());
}
_END_OP

