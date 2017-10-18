//****************************************************************************//
//**                                                                        **//
//** File:         op_vec_smax.hpp                                          **//
//** Description:  Find maximum scalar in vector                            **//
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

_DEFINE_OP(VSMAX_U64) {
  // Super naive reference implementation
  uint64* src = vm->gpr[(vArgs & 0x00F0) >> 4].pU64();
  uint32  i   = vm->gpr[(vArgs & 0x000F)].u32();
  uint64  max = (uint64)(-1LL);
  uint64  val = *src;

  // Bail if we find max
  while (val != max && i--) {
    uint64 val2 = *src++;
    if (val2 > val) {
      val = val2;
    }
  }
  vm->gpr[(vArgs & 0x0F00) >> 8].u64() = val;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Signed integer

_DEFINE_OP(VSMAX_S64) {
  // Super naive reference implementation
  sint64* src = vm->gpr[(vArgs & 0x00F0) >> 4].pS64();
  uint32  i   = vm->gpr[(vArgs & 0x000F)].u32();
  sint64  max = 9223372036854775807LL;
  sint64  val = *src;

  // Bail if we find max
  while (val != max && i--) {
    sint64 val2 = *src++;
    if (val2 > val) {
      val = val2;
    }
  }
  vm->gpr[(vArgs & 0x0F00) >> 8].s64() = val;
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Floatng point
_DEFINE_OP(VSMAX_F64) {
  // Super naive reference implementation
  float64* src = vm->gpr[(vArgs & 0x00F0) >> 4].pF64();
  uint32   i   = vm->gpr[(vArgs & 0x000F)].u32();
  float64  val = *src;

  // Bail if we find max
  while (i--) {
    float32 val2 = *src++;
    if (val2 > val) {
      val = val2;
    }
  }
  vm->gpr[(vArgs & 0x0F00) >> 8].f64() = val;
}
_END_OP

