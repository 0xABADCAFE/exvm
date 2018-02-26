//****************************************************************************//
//**                                                                        **//
//** File:         op_vec_sdiv_impl.hpp                                     **//
//** Description:  Scalar on Vector Modulus                                 **//
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
_DEFINE_OP(VSMOD_U64) {
  // Super naive reference implementation
  uint64  val = vm->gpr[VARG3].u64();
  if (!val) {
    vm->status = VMDefs::ZERO_DIVIDE;
    vm->exceptionOffset = EXC_OFFSET_EXT;
    return;
  }
  uint64* src = vm->gpr[VARG2].pU64();
  uint64* dst = vm->gpr[VARG1].pU64();
  uint32  i   = vm->gpr[VARG0].u32();
  while (i--) {
    *dst++ = *src++ % val;
  }
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Signed
_DEFINE_OP(VSMOD_S64) {
  // Super naive reference implementation
  sint64  val = vm->gpr[VARG3].s64();
  if (!val) {
    vm->status = VMDefs::ZERO_DIVIDE;
    vm->exceptionOffset = EXC_OFFSET_EXT;
    return;
  }
  sint64* src = vm->gpr[VARG2].pS64();
  sint64* dst = vm->gpr[VARG1].pS64();
  uint32  i   = vm->gpr[VARG0].u32();
  while (i--) {
    *dst++ = *src++ % val;
  }
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Float
_DEFINE_OP(VSMOD_F64) {
  // Super naive reference implementation
  float64  val = vm->gpr[VARG3].f64();
  float64* src = vm->gpr[VARG2].pF64();
  float64* dst = vm->gpr[VARG1].pF64();
  uint32  i    = vm->gpr[VARG0].u32();
  while (i--) {
    *dst++ = std::fmod(*src++, val);
  }
}
_END_OP

