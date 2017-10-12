//****************************************************************************//
//**                                                                        **//
//** File:         op_vec_slsl_impl.hpp                                     **//
//** Description:  Scalar on Vector logical shift left                      **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2017-08-19                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

_DEFINE_OP(VSLSL_64) {
  // Super naive reference implementation
  uint32  val = vm->gpr[(vArgs & 0xF000) >> 12].u8() & 0x3F;
  uint64* src = vm->gpr[(vArgs & 0x0F00) >> 8].pU64();
  uint64* dst = vm->gpr[(vArgs & 0x00F0) >> 4].pU64();
  uint32  i   = vm->gpr[(vArgs & 0x000F)].u32();
  while (i--) {
    *dst++ = *src++ << val;
  }
}
_END_OP
