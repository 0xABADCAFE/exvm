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
_DEFINE_OP(VSSUM_U64) {
  // Super naive reference implementation
  uint64* src = vm->gpr[VARG2].pU64();
  uint32  i   = vm->gpr[VARG0].u32();
  uint64  val = 0;
  while (i--) {
    val += *src++;
  }
  vm->gpr[VARG1].u64() = val;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Signed integer
_DEFINE_OP(VSSUM_S64) {
  // Super naive reference implementation
  sint64* src = vm->gpr[VARG2].pS64();
  uint32  i   = vm->gpr[VARG0].u32();
  sint64  val = 0;
  while (i--) {
    val += *src++;
  }
  vm->gpr[VARG1].s64() = val;
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Floating point
_DEFINE_OP(VSSUM_F64) {
  // Super naive reference implementation
  float64* src = vm->gpr[VARG2].pF64();
  uint32   i   = vm->gpr[VARG0].u32();
  float64  val = 0;
  while (i--) {
    val += *src++;
  }
  vm->gpr[VARG1].f64() = val;
}
_END_OP

