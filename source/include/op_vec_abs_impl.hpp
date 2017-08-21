//****************************************************************************//
//**                                                                        **//
//** File:         op_vec_abs_impl.hpp                                      **//
//** Description:  Vector absolute (sign)                                   **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2017-08-19                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

// Integer
_DEFINE_OP(VABS_S8) {
  // Super naive reference implementation
  sint8* src = vm->gpr[(vArgs & 0x0F00) >> 8].pS8();
  sint8* dst = vm->gpr[(vArgs & 0x00F0) >> 4].pS8();
  uint32 i   = vm->gpr[(vArgs & 0x000F)].u32();
  while (i--) {
    sint8 val  = *src++;
    sint8 sign = val >> 7;
    *dst++     = (val ^ sign) - sign;
  }
}
_END_OP

_DEFINE_OP(VABS_S16) {
  // Super naive reference implementation
  sint16* src = vm->gpr[(vArgs & 0x0F00) >> 8].pS16();
  sint16* dst = vm->gpr[(vArgs & 0x00F0) >> 4].pS16();
  uint32  i   = vm->gpr[(vArgs & 0x000F)].u32();
  while (i--) {
    sint8 val  = *src++;
    sint8 sign = val >> 15;
    *dst++     = (val ^ sign) - sign;
  }
}
_END_OP

_DEFINE_OP(VABS_S32) {
  // Super naive reference implementation
  sint32* src = vm->gpr[(vArgs & 0x0F00) >> 8].pS32();
  sint32* dst = vm->gpr[(vArgs & 0x00F0) >> 4].pS32();
  uint32  i   = vm->gpr[(vArgs & 0x000F)].u32();
  while (i--) {
    sint32 val  = *src++;
    sint32 sign = val >> 31;
    *dst++     = (val ^ sign) - sign;
  }
}
_END_OP

_DEFINE_OP(VABS_S64) {
  // Super naive reference implementation
  sint64* src = vm->gpr[(vArgs & 0x0F00) >> 8].pS64();
  sint64* dst = vm->gpr[(vArgs & 0x00F0) >> 4].pS64();
  uint32  i   = vm->gpr[(vArgs & 0x000F)].u32();
  while (i--) {
    sint64 val  = *src++;
    sint64 sign = val >> 63;
    *dst++      = (val ^ sign) - sign;
  }
}
_END_OP

// Float
_DEFINE_OP(VABS_F32) {
  // Super naive reference implementation
  uint32* src  = vm->gpr[(vArgs & 0x0F00) >> 8].pU32();
  uint32* dst  = vm->gpr[(vArgs & 0x00F0) >> 4].pU32();
  uint32  i    = vm->gpr[(vArgs & 0x000F)].u32();

  // Mask off the sign bit.
  uint32  mask = 0x7FFFFFFF;
  while (i--) {
    *dst++ = *src++ & mask;
  }
}
_END_OP

_DEFINE_OP(VABS_F64) {
  // Super naive reference implementation
  uint64* src  = vm->gpr[(vArgs & 0x0F00) >> 8].pU64();
  uint64* dst  = vm->gpr[(vArgs & 0x00F0) >> 4].pU64();
  uint32  i    = vm->gpr[(vArgs & 0x000F)].u32();

  // Mask off the sign bit.
  uint64   mask = 0x7FFFFFFFFFFFFFFFULL;
  while (i--) {
    *dst++ = *src++ & mask;
  }
}
_END_OP

