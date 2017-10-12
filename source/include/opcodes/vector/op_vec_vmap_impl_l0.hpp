//****************************************************************************//
//**                                                                        **//
//** File:         op_vec_sadd_impl.hpp                                     **//
//** Description:  Vector on Vector Addition                                **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2017-08-15                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

_DEFINE_OP(VMAP_8_16) {
  // Super naive reference implementation
  uint8*  src = vm->gpr[(vArgs & 0xF000) >> 12].pU8();
  uint16* map = vm->gpr[(vArgs & 0x0F00) >>  8].pU16();
  uint16* dst = vm->gpr[(vArgs & 0x00F0) >>  4].pU16();
  uint32  i   = vm->gpr[(vArgs & 0x000F)].u32();
  while (i--) {
    *dst++ = map[*src++];
  }
}
_END_OP

_DEFINE_OP(VMAP_8_32) {
  // Super naive reference implementation
  uint8*  src = vm->gpr[(vArgs & 0xF000) >> 12].pU8();
  uint32* map = vm->gpr[(vArgs & 0x0F00) >>  8].pU32();
  uint32* dst = vm->gpr[(vArgs & 0x00F0) >>  4].pU32();
  uint32  i   = vm->gpr[(vArgs & 0x000F)].u32();
  while (i--) {
    *dst++ = map[*src++];
  }
}
_END_OP

_DEFINE_OP(VMAP_16_32) {
  // Super naive reference implementation
  uint16* src = vm->gpr[(vArgs & 0xF000) >> 12].pU16();
  uint32* map = vm->gpr[(vArgs & 0x0F00) >>  8].pU32();
  uint32* dst = vm->gpr[(vArgs & 0x00F0) >>  4].pU32();
  uint32  i   = vm->gpr[(vArgs & 0x000F)].u32();
  while (i--) {
    *dst++ = map[*src++];
  }
}
_END_OP

