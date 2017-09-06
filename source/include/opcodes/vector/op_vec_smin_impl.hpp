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
_DEFINE_OP(VSMIN_U8) {
  // Super naive reference implementation
  uint8* src = vm->gpr[(vArgs & 0x00F0) >> 4].pU8();
  uint32 i   = vm->gpr[(vArgs & 0x000F)].u32();
  uint8  val = *src;

  // Bail if we find zero
  while (val && i--) {
    uint8 val2 = *src++;
    if (val2 < val) {
      val = val2;
    }
  }
  vm->gpr[(vArgs & 0x0F00) >> 8].u8() = val;
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(VSMIN_U16) {
  // Super naive reference implementation
  uint16* src = vm->gpr[(vArgs & 0x00F0) >> 4].pU16();
  uint32  i   = vm->gpr[(vArgs & 0x000F)].u32();
  uint16  val = *src;

  // Bail if we find zero
  while (val && i--) {
    uint16 val2 = *src++;
    if (val2 < val) {
      val = val2;
    }
  }
  vm->gpr[(vArgs & 0x0F00) >> 8].u16() = val;
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(VSMIN_U32) {
  // Super naive reference implementation
  uint32* src = vm->gpr[(vArgs & 0x00F0) >> 4].pU32();
  uint32  i   = vm->gpr[(vArgs & 0x000F)].u32();
  uint32  val = *src;

  // Bail if we find zero
  while (val && i--) {
    uint32 val2 = *src++;
    if (val2 < val) {
      val = val2;
    }
  }
  vm->gpr[(vArgs & 0x0F00) >> 8].u32() = val;
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(VSMIN_U64) {
  // Super naive reference implementation
  uint64* src = vm->gpr[(vArgs & 0x00F0) >> 4].pU64();
  uint32  i   = vm->gpr[(vArgs & 0x000F)].u32();
  uint64  val = *src;

  // Bail if we find zero
  while (val && i--) {
    uint64 val2 = *src++;
    if (val2 < val) {
      val = val2;
    }
  }
  vm->gpr[(vArgs & 0x0F00) >> 8].u64() = val;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Signed integer
_DEFINE_OP(VSMIN_S8) {
  // Super naive reference implementation
  sint8* src = vm->gpr[(vArgs & 0x00F0) >> 4].pS8();
  uint32 i   = vm->gpr[(vArgs & 0x000F)].u32();
  sint8  min = -128;
  sint8  val = *src;

  // Bail if we find min
  while (val > min && i--) {
    sint8 val2 = *src++;
    if (val2 < val) {
      val = val2;
    }
  }
  vm->gpr[(vArgs & 0x0F00) >> 8].s8() = val;
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(VSMIN_S16) {
  // Super naive reference implementation
  sint16* src = vm->gpr[(vArgs & 0x00F0) >> 4].pS16();
  uint32  i   = vm->gpr[(vArgs & 0x000F)].u32();
  sint16  min = -32768;
  sint16  val = *src;

  // Bail if we find min
  while (val > min && i--) {
    sint16 val2 = *src++;
    if (val2 < val) {
      val = val2;
    }
  }
  vm->gpr[(vArgs & 0x0F00) >> 8].s16() = val;
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(VSMIN_S32) {
  // Super naive reference implementation
  sint32* src = vm->gpr[(vArgs & 0x00F0) >> 4].pS32();
  uint32  i   = vm->gpr[(vArgs & 0x000F)].u32();
  sint32  min = -2147483648L;
  sint32  val = *src;

  // Bail if we find min
  while (val > min && i--) {
    sint32 val2 = *src++;
    if (val2 < val) {
      val = val2;
    }
  }
  vm->gpr[(vArgs & 0x0F00) >> 8].s32() = val;
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(VSMIN_S64) {
  // Super naive reference implementation
  sint64* src = vm->gpr[(vArgs & 0x00F0) >> 4].pS64();
  uint32  i   = vm->gpr[(vArgs & 0x000F)].u32();
  sint64  min = -9223372036854775807LL;
  sint64  val = *src;

  // Bail if we find min
  while (val > min && i--) {
    sint64 val2 = *src++;
    if (val2 < val) {
      val = val2;
    }
  }
  vm->gpr[(vArgs & 0x0F00) >> 8].s64() = val;
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Floatng point
_DEFINE_OP(VSMIN_F32) {
  // Super naive reference implementation
  float32* src = vm->gpr[(vArgs & 0x00F0) >> 4].pF32();
  uint32   i   = vm->gpr[(vArgs & 0x000F)].u32();
  float32  val = *src;

  // Bail if we find min
  while (i--) {
    float32 val2 = *src++;
    if (val2 < val) {
      val = val2;
    }
  }
  vm->gpr[(vArgs & 0x0F00) >> 8].f32() = val;
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(VSMIN_F64) {
  // Super naive reference implementation
  float64* src = vm->gpr[(vArgs & 0x00F0) >> 4].pF64();
  uint32   i   = vm->gpr[(vArgs & 0x000F)].u32();
  float64  val = *src;

  // Bail if we find min
  while (i--) {
    float32 val2 = *src++;
    if (val2 < val) {
      val = val2;
    }
  }
  vm->gpr[(vArgs & 0x0F00) >> 8].f64() = val;
}
_END_OP

