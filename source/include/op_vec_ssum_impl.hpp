//****************************************************************************//
//**                                                                        **//
//** File:         op_vec_smin.hpp                                          **//
//** Description:  Find minimum scalar in vector                            **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2017-08-15                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

// Unsigned integer
_DEFINE_OP(VSSUM_U8) {
  // Super naive reference implementation
  uint8* src = vm->gpr[(vArgs & 0x00F0) >> 4].pU8();
  uint32 i   = vm->gpr[(vArgs & 0x000F)].u32();
  uint64 val = 0;
  while (i--) {
    val += *src++;
  }
  vm->gpr[(vArgs & 0x0F00) >> 8].u64() = val;
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(VSSUM_U16) {
  // Super naive reference implementation
  uint16* src = vm->gpr[(vArgs & 0x00F0) >> 4].pU16();
  uint32  i   = vm->gpr[(vArgs & 0x000F)].u32();
  uint64  val = 0;
  while (i--) {
    val += *src++;
  }
  vm->gpr[(vArgs & 0x0F00) >> 8].u64() = val;
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(VSSUM_U32) {
  // Super naive reference implementation
  uint32* src = vm->gpr[(vArgs & 0x00F0) >> 4].pU32();
  uint32  i   = vm->gpr[(vArgs & 0x000F)].u32();
  uint64  val = 0;
  while (i--) {
    val += *src++;
  }
  vm->gpr[(vArgs & 0x0F00) >> 8].u64() = val;
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(VSSUM_U64) {
  // Super naive reference implementation
  uint64* src = vm->gpr[(vArgs & 0x00F0) >> 4].pU64();
  uint32  i   = vm->gpr[(vArgs & 0x000F)].u32();
  uint64  val = 0;
  while (i--) {
    val += *src++;
  }
  vm->gpr[(vArgs & 0x0F00) >> 8].u64() = val;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Signed integer
_DEFINE_OP(VSSUM_S8) {
  // Super naive reference implementation
  sint8* src = vm->gpr[(vArgs & 0x00F0) >> 4].pS8();
  uint32 i   = vm->gpr[(vArgs & 0x000F)].u32();
  sint64 val = 0;
  while (i--) {
    val += *src++;
  }
  vm->gpr[(vArgs & 0x0F00) >> 8].s64() = val;
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(VSSUM_S16) {
  // Super naive reference implementation
  sint16* src = vm->gpr[(vArgs & 0x00F0) >> 4].pS16();
  uint32  i   = vm->gpr[(vArgs & 0x000F)].u32();
  sint64  val = 0;
  while (i--) {
    val += *src++;
  }
  vm->gpr[(vArgs & 0x0F00) >> 8].s64() = val;
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(VSSUM_S32) {
  // Super naive reference implementation
  sint32* src = vm->gpr[(vArgs & 0x00F0) >> 4].pS32();
  uint32  i   = vm->gpr[(vArgs & 0x000F)].u32();
  sint64  val = 0;
  while (i--) {
    val += *src++;
  }
  vm->gpr[(vArgs & 0x0F00) >> 8].s64() = val;
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(VSSUM_S64) {
  // Super naive reference implementation
  sint64* src = vm->gpr[(vArgs & 0x00F0) >> 4].pS64();
  uint32  i   = vm->gpr[(vArgs & 0x000F)].u32();
  sint64  val = 0;
  while (i--) {
    val += *src++;
  }
  vm->gpr[(vArgs & 0x0F00) >> 8].s64() = val;
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Floatng point
_DEFINE_OP(VSSUM_F32) {
  // Super naive reference implementation
  float32* src = vm->gpr[(vArgs & 0x00F0) >> 4].pF32();
  uint32   i   = vm->gpr[(vArgs & 0x000F)].u32();
  float64  val = 0;
  while (i--) {
    val += *src++;
  }
  vm->gpr[(vArgs & 0x0F00) >> 8].f64() = val;
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(VSSUM_F64) {
  // Super naive reference implementation
  float64* src = vm->gpr[(vArgs & 0x00F0) >> 4].pF64();
  uint32   i   = vm->gpr[(vArgs & 0x000F)].u32();
  float64  val = 0;
  while (i--) {
    val += *src++;
  }
  vm->gpr[(vArgs & 0x0F00) >> 8].f64() = val;
}
_END_OP

