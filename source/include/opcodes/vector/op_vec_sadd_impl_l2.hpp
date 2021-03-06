//****************************************************************************//
//**                                                                        **//
//** File:         op_vec_sadd_impl.hpp                                     **//
//** Description:  Scalar on Vector Addition                                **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2017-08-15                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

// Integer
_DEFINE_OP(VSADD_I64) {
  // Super naive reference implementation
  sint64  val = vm->gpr[VARG3].s64();
  sint64* src = vm->gpr[VARG2].pS64();
  sint64* dst = vm->gpr[VARG1].pS64();
  uint32  i   = vm->gpr[VARG0].u32();
  while (i--) {
    *dst++ = val + *src++;
  }
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Float
_DEFINE_OP(VSADD_F64) {
  // Super naive reference implementation
  float64  val = vm->gpr[VARG3].f64();
  float64* src = vm->gpr[VARG2].pF64();
  float64* dst = vm->gpr[VARG1].pF64();
  uint32   i   = vm->gpr[VARG0].u32();
  while (i--) {
    *dst++ = val + *src++;
  }
}
_END_OP

