//****************************************************************************//
//**                                                                        **//
//** File:         op_vec_fill.hpp                                          **//
//** Description:  Vector filling (splat)                                   **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2001-09-02                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//


_DEFINE_OP(VNEG_S8) {
  // Super naive reference implementation
  sint8* src = vm->gpr[(vArgs & 0x0F00) >> 8].pS8();
  sint8* dst = vm->gpr[(vArgs & 0x00F0) >> 4].pS8();
  uint32 i   = vm->gpr[(vArgs & 0x000F)].u32();
  while (i--) {
    *dst++ = -(*src++);
  }
}
_END_OP

_DEFINE_OP(VNEG_S16) {
  // Super naive reference implementation
  sint16* src = vm->gpr[(vArgs & 0x0F00) >> 8].pS16();
  sint16* dst = vm->gpr[(vArgs & 0x00F0) >> 4].pS16();
  uint32 i    = vm->gpr[(vArgs & 0x000F)].u32();
  while (i--) {
    *dst++ = -(*src++);
  }
}
_END_OP

_DEFINE_OP(VNEG_S32) {
  // Super naive reference implementation
  sint32* src = vm->gpr[(vArgs & 0x0F00) >> 8].pS32();
  sint32* dst = vm->gpr[(vArgs & 0x00F0) >> 4].pS32();
  uint32  i   = vm->gpr[(vArgs & 0x000F)].u32();
  while (i--) {
    *dst++ = -(*src++);
  }
}
_END_OP

_DEFINE_OP(VNEG_S64) {
  // Super naive reference implementation
  sint64* src = vm->gpr[(vArgs & 0x0F00) >> 8].pS64();
  sint64* dst = vm->gpr[(vArgs & 0x00F0) >> 4].pS64();
  uint32 i    = vm->gpr[(vArgs & 0x000F)].u32();
  while (i--) {
    *dst++ = -(*src++);
  }
}
_END_OP

_DEFINE_OP(VNEG_F32) {
  // Super naive reference implementation
  float* src = vm->gpr[(vArgs & 0x0F00) >> 8].pF32();
  float* dst = vm->gpr[(vArgs & 0x00F0) >> 4].pF32();
  uint32  i  = vm->gpr[(vArgs & 0x000F)].u32();
  while (i--) {
    *dst++ = -(*src++);
  }
}
_END_OP

_DEFINE_OP(VNEG_F64) {
  // Super naive reference implementation
  float64* src = vm->gpr[(vArgs & 0x0F00) >> 8].pF64();
  float64* dst = vm->gpr[(vArgs & 0x00F0) >> 4].pF64();
  uint32 i     = vm->gpr[(vArgs & 0x000F)].u32();
  while (i--) {
    *dst++ = -(*src++);
  }
}
_END_OP
