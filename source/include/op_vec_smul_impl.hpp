//****************************************************************************//
//**                                                                        **//
//** File:         op_vec_smul_impl.hpp                                     **//
//** Description:  Scalar on Vector Multiplication                          **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2017-08-15                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

// Unsigned
_DEFINE_OP(VSMUL_U8) {
  // Super naive reference implementation
  uint8  val = vm->gpr[(vArgs & 0xF000) >> 12].u8();
  uint8* src = vm->gpr[(vArgs & 0x0F00) >>  8].pU8();
  uint8* dst = vm->gpr[(vArgs & 0x00F0) >>  4].pU8();
  uint32 i   = vm->gpr[(vArgs & 0x000F)].u32();
  while (i--) {
    *dst++ = val * *src++;
  }
}
_END_OP

_DEFINE_OP(VSMUL_U16) {
  // Super naive reference implementation
  uint16  val = vm->gpr[(vArgs & 0xF000) >> 12].u16();
  uint16* src = vm->gpr[(vArgs & 0x0F00) >>  8].pU16();
  uint16* dst = vm->gpr[(vArgs & 0x00F0) >>  4].pU16();
  uint32  i   = vm->gpr[(vArgs & 0x000F)].u32();
  while (i--) {
    *dst++ = val * *src++;
  }
}
_END_OP

_DEFINE_OP(VSMUL_U32) {
  // Super naive reference implementation
  uint32  val = vm->gpr[(vArgs & 0xF000) >> 12].u32();
  uint32* src = vm->gpr[(vArgs & 0x0F00) >>  8].pU32();
  uint32* dst = vm->gpr[(vArgs & 0x00F0) >>  4].pU32();
  uint32  i   = vm->gpr[(vArgs & 0x000F)].u32();
  while (i--) {
    *dst++ = val * *src++;
  }
}
_END_OP

_DEFINE_OP(VSMUL_U64) {
  // Super naive reference implementation
  uint64  val = vm->gpr[(vArgs & 0xF000) >> 12].u64();
  uint64* src = vm->gpr[(vArgs & 0x0F00) >>  8].pU64();
  uint64* dst = vm->gpr[(vArgs & 0x00F0) >>  4].pU64();
  uint32  i   = vm->gpr[(vArgs & 0x000F)].u32();
  while (i--) {
    *dst++ = val * *src++;
  }
}
_END_OP


// Signed
_DEFINE_OP(VSMUL_S8) {
  // Super naive reference implementation
  sint8  val = vm->gpr[(vArgs & 0xF000) >> 12].s8();
  sint8* src = vm->gpr[(vArgs & 0x0F00) >>  8].pS8();
  sint8* dst = vm->gpr[(vArgs & 0x00F0) >>  4].pS8();
  uint32 i   = vm->gpr[(vArgs & 0x000F)].u32();
  while (i--) {
    *dst++ = val * *src++;
  }
}
_END_OP

_DEFINE_OP(VSMUL_S16) {
  // Super naive reference implementation
  sint16  val = vm->gpr[(vArgs & 0xF000) >> 12].s16();
  sint16* src = vm->gpr[(vArgs & 0x0F00) >>  8].pS16();
  sint16* dst = vm->gpr[(vArgs & 0x00F0) >>  4].pS16();
  uint32 i    = vm->gpr[(vArgs & 0x000F)].u32();
  while (i--) {
    *dst++ = val * *src++;
  }
}
_END_OP

_DEFINE_OP(VSMUL_S32) {
  // Super naive reference implementation
  sint32  val = vm->gpr[(vArgs & 0xF000) >> 12].s32();
  sint32* src = vm->gpr[(vArgs & 0x0F00) >>  8].pS32();
  sint32* dst = vm->gpr[(vArgs & 0x00F0) >>  4].pS32();
  uint32  i   = vm->gpr[(vArgs & 0x000F)].u32();
  while (i--) {
    *dst++ = val * *src++;
  }
}
_END_OP

_DEFINE_OP(VSMUL_S64) {
  // Super naive reference implementation
  sint64  val = vm->gpr[(vArgs & 0xF000) >> 12].s64();
  sint64* src = vm->gpr[(vArgs & 0x0F00) >>  8].pS64();
  sint64* dst = vm->gpr[(vArgs & 0x00F0) >>  4].pS64();
  uint32  i   = vm->gpr[(vArgs & 0x000F)].u32();
  while (i--) {
    *dst++ = val * *src++;
  }
}
_END_OP

// Float
_DEFINE_OP(VSMUL_F32) {
  // Super naive reference implementation
  float32  val = vm->gpr[(vArgs & 0xF000) >> 12].f32();
  float32* src = vm->gpr[(vArgs & 0x0F00) >>  8].pF32();
  float32* dst = vm->gpr[(vArgs & 0x00F0) >>  4].pF32();
  uint32   i   = vm->gpr[(vArgs & 0x000F)].u32();
  while (i--) {
    *dst++ = val * *src++;
  }
}
_END_OP

_DEFINE_OP(VSMUL_F64) {
  // Super naive reference implementation
  float64  val = vm->gpr[(vArgs & 0xF000) >> 12].f64();
  float64* src = vm->gpr[(vArgs & 0x0F00) >>  8].pF64();
  float64* dst = vm->gpr[(vArgs & 0x00F0) >>  4].pF64();
  uint32   i   = vm->gpr[(vArgs & 0x000F)].u32();
  while (i--) {
    *dst++ = val * *src++;
  }
}
_END_OP
