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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

