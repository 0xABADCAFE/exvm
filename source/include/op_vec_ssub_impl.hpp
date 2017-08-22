//****************************************************************************//
//**                                                                        **//
//** File:         op_vec_ssub_impl.hpp                                     **//
//** Description:  Scalar on Vector Subtraction                             **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2017-08-15                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

// Integer
_DEFINE_OP(VSSUB_I8) {
  // Super naive reference implementation
  sint8  val = vm->gpr[(vArgs & 0xF000) >> 12].s8();
  sint8* src = vm->gpr[(vArgs & 0x0F00) >>  8].pS8();
  sint8* dst = vm->gpr[(vArgs & 0x00F0) >>  4].pS8();
  uint32 i   = vm->gpr[(vArgs & 0x000F)].u32();
  while (i--) {
    *dst++ = *src++ - val;
  }
}
_END_OP

_DEFINE_OP(VSSUB_I16) {
  // Super naive reference implementation
  sint16  val = vm->gpr[(vArgs & 0xF000) >> 12].s16();
  sint16* src = vm->gpr[(vArgs & 0x0F00) >>  8].pS16();
  sint16* dst = vm->gpr[(vArgs & 0x00F0) >>  4].pS16();
  uint32  i   = vm->gpr[(vArgs & 0x000F)].u32();
  while (i--) {
    *dst++ = *src++ - val;
  }
}
_END_OP

_DEFINE_OP(VSSUB_I32) {
  // Super naive reference implementation
  sint32  val = vm->gpr[(vArgs & 0xF000) >> 12].s32();
  sint32* src = vm->gpr[(vArgs & 0x0F00) >>  8].pS32();
  sint32* dst = vm->gpr[(vArgs & 0x00F0) >>  4].pS32();
  uint32  i   = vm->gpr[(vArgs & 0x000F)].u32();
  while (i--) {
    *dst++ = *src++ - val;
  }
}
_END_OP

_DEFINE_OP(VSSUB_I64) {
  // Super naive reference implementation
  sint64  val = vm->gpr[(vArgs & 0xF000) >> 12].s64();
  sint64* src = vm->gpr[(vArgs & 0x0F00) >>  8].pS64();
  sint64* dst = vm->gpr[(vArgs & 0x00F0) >>  4].pS64();
  uint32  i   = vm->gpr[(vArgs & 0x000F)].u32();
  while (i--) {
    *dst++ = *src++ - val;
  }
}
_END_OP

// Float
_DEFINE_OP(VSSUB_F32) {
  // Super naive reference implementation
  float32  val = vm->gpr[(vArgs & 0xF000) >> 12].f32();
  float32* src = vm->gpr[(vArgs & 0x0F00) >>  8].pF32();
  float32* dst = vm->gpr[(vArgs & 0x00F0) >>  4].pF32();
  uint32   i   = vm->gpr[(vArgs & 0x000F)].u32();
  while (i--) {
    *dst++ = *src++ - val;
  }
}
_END_OP

_DEFINE_OP(VSSUB_F64) {
  // Super naive reference implementation
  float64  val = vm->gpr[(vArgs & 0xF000) >> 12].f64();
  float64* src = vm->gpr[(vArgs & 0x0F00) >>  8].pF64();
  float64* dst = vm->gpr[(vArgs & 0x00F0) >>  4].pF64();
  uint32  i    = vm->gpr[(vArgs & 0x000F)].u32();
  while (i--) {
    *dst++ = *src++ - val;
  }
}
_END_OP
