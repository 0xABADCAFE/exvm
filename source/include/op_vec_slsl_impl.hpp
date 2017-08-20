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


_DEFINE_OP(VSLSL_8) {
  // Super naive reference implementation
  uint8  val = vm->gpr[(vArgs & 0xF000) >> 12].u8();
  uint8* src = vm->gpr[(vArgs & 0x0F00) >> 8].pU8();
  uint8* dst = vm->gpr[(vArgs & 0x00F0) >> 4].pU8();
  uint32 i   = vm->gpr[(vArgs & 0x000F)].u32();
  while (i--) {
    *dst++ = *src++ << val;
  }
}
_END_OP

_DEFINE_OP(VSLSL_16) {
  // Super naive reference implementation
  uint16  val = vm->gpr[(vArgs & 0xF000) >> 12].u16();
  uint16* src = vm->gpr[(vArgs & 0x0F00) >> 8].pU16();
  uint16* dst = vm->gpr[(vArgs & 0x00F0) >> 4].pU16();
  uint32  i   = vm->gpr[(vArgs & 0x000F)].u32();
  while (i--) {
    *dst++ = *src++ << val;
  }
}
_END_OP

_DEFINE_OP(VSLSL_32) {
  // Super naive reference implementation
  uint32  val = vm->gpr[(vArgs & 0xF000) >> 12].u32();
  uint32* src = vm->gpr[(vArgs & 0x0F00) >> 8].pU32();
  uint32* dst = vm->gpr[(vArgs & 0x00F0) >> 4].pU32();
  uint32  i   = vm->gpr[(vArgs & 0x000F)].u32();
  while (i--) {
    *dst++ = *src++ << val;
  }
}
_END_OP

_DEFINE_OP(VSLSL_64) {
  // Super naive reference implementation
  uint64  val = vm->gpr[(vArgs & 0xF000) >> 12].u64();
  uint64* src = vm->gpr[(vArgs & 0x0F00) >> 8].pU64();
  uint64* dst = vm->gpr[(vArgs & 0x00F0) >> 4].pU64();
  uint32  i   = vm->gpr[(vArgs & 0x000F)].u32();
  while (i--) {
    *dst++ = *src++ << val;
  }
}
_END_OP
