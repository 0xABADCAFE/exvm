//****************************************************************************//
//**                                                                        **//
//** File:         op_vec_vdiv_impl.hpp                                     **//
//** Description:  Vector on Vector Division                                **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2017-08-15                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

// TODO - division by zero
_DEFINE_OP(VDIV_U64) {
  // Super naive reference implementation
  uint64* src1 = vm->gpr[(vArgs & 0xF000) >> 12].pU64();
  uint64* src2 = vm->gpr[(vArgs & 0x0F00) >>  8].pU64();
  uint64* dst  = vm->gpr[(vArgs & 0x00F0) >>  4].pU64();
  uint32  i    = vm->gpr[(vArgs & 0x000F)].u32();
  while (i--) {
    *dst++ = *src1++ / *src2++;
  }
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Signed
_DEFINE_OP(VDIV_S64) {
  // Super naive reference implementation
  sint64* src1 = vm->gpr[(vArgs & 0xF000) >> 12].pS64();
  sint64* src2 = vm->gpr[(vArgs & 0x0F00) >>  8].pS64();
  sint64* dst  = vm->gpr[(vArgs & 0x00F0) >>  4].pS64();
  uint32  i    = vm->gpr[(vArgs & 0x000F)].u32();
  while (i--) {
    *dst++ = *src1++ / *src2++;
  }
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Float
_DEFINE_OP(VDIV_F64) {
  // Super naive reference implementation
  float64* src1 = vm->gpr[(vArgs & 0xF000) >> 12].pF64();
  float64* src2 = vm->gpr[(vArgs & 0x0F00) >>  8].pF64();
  float64* dst  = vm->gpr[(vArgs & 0x00F0) >>  4].pF64();
  uint32   i    = vm->gpr[(vArgs & 0x000F)].u32();
  while (i--) {
    *dst++ = *src1++ / *src2++;
  }
}
_END_OP

