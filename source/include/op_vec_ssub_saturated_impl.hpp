//****************************************************************************//
//**                                                                        **//
//** File:         op_vec_ssub_saturated_impl.hpp                           **//
//** Description:  Scalar on Vector Subtraction, Saturating                 **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2017-08-15                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//


_DEFINE_OP(VSSUBS_U8) {
  // Super naive reference implementation
  uint8  val = vm->gpr[(vArgs & 0xF000) >> 12].u8();
  uint8*  src = vm->gpr[(vArgs & 0x0F00) >>  8].pU8();
  uint8*  dst = vm->gpr[(vArgs & 0x00F0) >>  4].pU8();
  uint32  i   = vm->gpr[(vArgs & 0x000F)].u32();
  while (i--) {
    // TODO - validate correctness
    uint8 val2 = *src++;
    uint8 res  = val2 - val;
    *dst++ = res & -(res <= val2);
  }
}
_END_OP

_DEFINE_OP(VSSUBS_U16) {
  // Super naive reference implementation
  uint16  val = vm->gpr[(vArgs & 0xF000) >> 12].u16();
  uint16* src = vm->gpr[(vArgs & 0x0F00) >>  8].pU16();
  uint16* dst = vm->gpr[(vArgs & 0x00F0) >>  4].pU16();
  uint32  i   = vm->gpr[(vArgs & 0x000F)].u32();
  while (i--) {
    // TODO - validate correctness
    uint16 val2 = *src++;
    uint16 res  = val2 - val;
    *dst++ = res & -(res <= val2);
  }
}
_END_OP

_DEFINE_OP(VSSUBS_U32) {
  // Super naive reference implementation
  uint32  val = vm->gpr[(vArgs & 0xF000) >> 12].u32();
  uint16* src = vm->gpr[(vArgs & 0x0F00) >>  8].pU32();
  uint16* dst = vm->gpr[(vArgs & 0x00F0) >>  4].pU32();
  uint32  i   = vm->gpr[(vArgs & 0x000F)].u32();
  while (i--) {
    // TODO - validate correctness
    // TODO - validate correctness
    uint32 val2 = *src++;
    uint32 res  = val2 - val;
    *dst++ = res & -(res <= val2);
  }
}
_END_OP

_DEFINE_OP(VSSUBS_U64) {
  // Super naive reference implementation
  uint64  val = vm->gpr[(vArgs & 0xF000) >> 12].u64();
  uint64* src = vm->gpr[(vArgs & 0x0F00) >>  8].pU64();
  uint64* dst = vm->gpr[(vArgs & 0x00F0) >>  4].pU64();
  uint32  i   = vm->gpr[(vArgs & 0x000F)].u32();
  while (i--) {
    // TODO - validate correctness
    // TODO - validate correctness
    uint64 val2 = *src++;
    uint64 res  = val2 - val;
    *dst++ = res & -(res <= val2);
  }
}
_END_OP



_DEFINE_OP(VSSUBS_S8) {
  // Super naive reference implementation
  sint8   val = vm->gpr[(vArgs & 0xF000) >> 12].s8();
  sint8*  src = vm->gpr[(vArgs & 0x0F00) >>  8].pS8();
  sint8*  dst = vm->gpr[(vArgs & 0x00F0) >>  4].pS8();
  uint32  i   = vm->gpr[(vArgs & 0x000F)].u32();
  while (i--) {
    // TODO - validate correctness

  }
}
_END_OP

_DEFINE_OP(VSSUBS_S16) {
  // Super naive reference implementation
  sint16  val = vm->gpr[(vArgs & 0xF000) >> 12].s16();
  sint16* src = vm->gpr[(vArgs & 0x0F00) >>  8].pS16();
  sint16* dst = vm->gpr[(vArgs & 0x00F0) >>  4].pS16();
  uint32  i   = vm->gpr[(vArgs & 0x000F)].u32();
  while (i--) {
    // TODO - validate correctness

  }
}
_END_OP

_DEFINE_OP(VSSUBS_S32) {
  // Super naive reference implementation
  sint32  val = vm->gpr[(vArgs & 0xF000) >> 12].s32();
  sint16* src = vm->gpr[(vArgs & 0x0F00) >>  8].pS32();
  sint16* dst = vm->gpr[(vArgs & 0x00F0) >>  4].pS32();
  uint32  i   = vm->gpr[(vArgs & 0x000F)].u32();
  while (i--) {
    // TODO - validate correctness

  }
}
_END_OP

_DEFINE_OP(VSSUBS_S64) {
  // Super naive reference implementation
  sint64  val = vm->gpr[(vArgs & 0xF000) >> 12].s64();
  sint64* src = vm->gpr[(vArgs & 0x0F00) >>  8].pS64();
  sint64* dst = vm->gpr[(vArgs & 0x00F0) >>  4].pS64();
  uint32  i   = vm->gpr[(vArgs & 0x000F)].u32();
  while (i--) {
    // TODO - validate correctness

  }
}
_END_OP
