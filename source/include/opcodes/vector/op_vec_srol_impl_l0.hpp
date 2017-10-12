//****************************************************************************//
//**                                                                        **//
//** File:         op_vec_srol_impl.hpp                                     **//
//** Description:  Scalar on Vector rotate left                             **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2017-08-19                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//


_DEFINE_OP(VSROL_8) {
  // Super naive reference implementation
  uint32 shf = vm->gpr[(vArgs & 0xF000) >> 12].u8() & 0x7;
  uint8* src = vm->gpr[(vArgs & 0x0F00) >> 8].pU8();
  uint8* dst = vm->gpr[(vArgs & 0x00F0) >> 4].pU8();
  uint32 i   = vm->gpr[(vArgs & 0x000F)].u32();
  while (i--) {
    uint32 val = *src++;
    *dst++ = (val << shf) | val >> (8 - shf);
  }
}
_END_OP

_DEFINE_OP(VSROL_16) {
  // Super naive reference implementation
  uint32  shf = vm->gpr[(vArgs & 0xF000) >> 12].u8() & 0xF;
  uint16* src = vm->gpr[(vArgs & 0x0F00) >> 8].pU16();
  uint16* dst = vm->gpr[(vArgs & 0x00F0) >> 4].pU16();
  uint32  i   = vm->gpr[(vArgs & 0x000F)].u32();
  while (i--) {
    uint32 val = *src++;
    *dst++ = (val << shf) | val >> (16 - shf);
  }
}
_END_OP

_DEFINE_OP(VSROL_32) {
  // Super naive reference implementation
  uint32  shf = vm->gpr[(vArgs & 0xF000) >> 12].u8() & 0x1F;
  uint32* src = vm->gpr[(vArgs & 0x0F00) >> 8].pU32();
  uint32* dst = vm->gpr[(vArgs & 0x00F0) >> 4].pU32();
  uint32  i   = vm->gpr[(vArgs & 0x000F)].u32();
  while (i--) {
    uint32 val = *src++;
    *dst++ = (val << shf) | val >> (32 - shf);
  }
}
_END_OP

