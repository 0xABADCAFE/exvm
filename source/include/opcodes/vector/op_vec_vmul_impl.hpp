//****************************************************************************//
//**                                                                        **//
//** File:         op_vec_vmul_impl.hpp                                     **//
//** Description:  Vector on Vector Multiplication                          **//
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
_DEFINE_OP(VMUL_U8) {
  // Super naive reference implementation
  uint8* src1 = vm->gpr[(vArgs & 0xF000) >> 12].pU8();
  uint8* src2 = vm->gpr[(vArgs & 0x0F00) >>  8].pU8();
  uint8* dst  = vm->gpr[(vArgs & 0x00F0) >>  4].pU8();
  uint32 i    = vm->gpr[(vArgs & 0x000F)].u32();
  while (i--) {
    *dst++ = *src1++ * *src2++;
  }
}
_END_OP

_DEFINE_OP(VMUL_U16) {
  // Super naive reference implementation
  uint16* src1 = vm->gpr[(vArgs & 0xF000) >> 12].pU16();
  uint16* src2 = vm->gpr[(vArgs & 0x0F00) >>  8].pU16();
  uint16* dst  = vm->gpr[(vArgs & 0x00F0) >>  4].pU16();
  uint32  i    = vm->gpr[(vArgs & 0x000F)].u32();
  while (i--) {
    *dst++ = *src1++ * *src2++;
  }
}
_END_OP

_DEFINE_OP(VMUL_U32) {
  // Super naive reference implementation
  uint32* src1 = vm->gpr[(vArgs & 0xF000) >> 12].pU32();
  uint32* src2 = vm->gpr[(vArgs & 0x0F00) >>  8].pU32();
  uint32* dst  = vm->gpr[(vArgs & 0x00F0) >>  4].pU32();
  uint32  i    = vm->gpr[(vArgs & 0x000F)].u32();
  while (i--) {
    *dst++ = *src1++ * *src2++;
  }
}
_END_OP

_DEFINE_OP(VMUL_U64) {
  // Super naive reference implementation
  uint64* src1 = vm->gpr[(vArgs & 0xF000) >> 12].pU64();
  uint64* src2 = vm->gpr[(vArgs & 0x0F00) >>  8].pU64();
  uint64* dst  = vm->gpr[(vArgs & 0x00F0) >>  4].pU64();
  uint32  i    = vm->gpr[(vArgs & 0x000F)].u32();
  while (i--) {
    *dst++ = *src1++ * *src2++;
  }
}
_END_OP


// Signed
_DEFINE_OP(VMUL_S8) {
  // Super naive reference implementation
  sint8* src1 = vm->gpr[(vArgs & 0xF000) >> 12].pS8();
  sint8* src2 = vm->gpr[(vArgs & 0x0F00) >>  8].pS8();
  sint8* dst  = vm->gpr[(vArgs & 0x00F0) >>  4].pS8();
  uint32 i    = vm->gpr[(vArgs & 0x000F)].u32();
  while (i--) {
    *dst++ = *src1++ * *src2++;
  }
}
_END_OP

_DEFINE_OP(VMUL_S16) {
  // Super naive reference implementation
  sint16* src1 = vm->gpr[(vArgs & 0xF000) >> 12].pS16();
  sint16* src2 = vm->gpr[(vArgs & 0x0F00) >>  8].pS16();
  sint16* dst  = vm->gpr[(vArgs & 0x00F0) >>  4].pS16();
  uint32  i    = vm->gpr[(vArgs & 0x000F)].u32();
  while (i--) {
    *dst++ = *src1++ * *src2++;
  }
}
_END_OP

_DEFINE_OP(VMUL_S32) {
  // Super naive reference implementation
  sint32* src1 = vm->gpr[(vArgs & 0xF000) >> 12].pS32();
  sint32* src2 = vm->gpr[(vArgs & 0x0F00) >>  8].pS32();
  sint32* dst  = vm->gpr[(vArgs & 0x00F0) >>  4].pS32();
  uint32  i    = vm->gpr[(vArgs & 0x000F)].u32();
  while (i--) {
    *dst++ = *src1++ * *src2++;
  }
}
_END_OP

_DEFINE_OP(VMUL_S64) {
  // Super naive reference implementation
  sint64* src1 = vm->gpr[(vArgs & 0xF000) >> 12].pS64();
  sint64* src2 = vm->gpr[(vArgs & 0x0F00) >>  8].pS64();
  sint64* dst  = vm->gpr[(vArgs & 0x00F0) >>  4].pS64();
  uint32  i    = vm->gpr[(vArgs & 0x000F)].u32();
  while (i--) {
    *dst++ = *src1++ * *src2++;
  }
}
_END_OP

// Float
_DEFINE_OP(VMUL_F32) {
  // Super naive reference implementation
  float32* src1 = vm->gpr[(vArgs & 0xF000) >> 12].pF32();
  float32* src2 = vm->gpr[(vArgs & 0x0F00) >>  8].pF32();
  float32* dst  = vm->gpr[(vArgs & 0x00F0) >>  4].pF32();
  uint32   i    = vm->gpr[(vArgs & 0x000F)].u32();
  while (i--) {
    *dst++ = *src1++ * *src2++;
  }
}
_END_OP

_DEFINE_OP(VMUL_F64) {
  // Super naive reference implementation
  float64* src1 = vm->gpr[(vArgs & 0xF000) >> 12].pF64();
  float64* src2 = vm->gpr[(vArgs & 0x0F00) >>  8].pF64();
  float64* dst  = vm->gpr[(vArgs & 0x00F0) >>  4].pF64();
  uint32   i    = vm->gpr[(vArgs & 0x000F)].u32();
  while (i--) {
    *dst++ = *src1++ * *src2++;
  }
}
_END_OP
