//****************************************************************************//
//**                                                                        **//
//** File:         op_vec_sasl_impl.hpp                                     **//
//** Description:  Scalar on Vector arithmetic shift right                  **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2017-08-19                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

_DEFINE_OP(VSASR_64) {
  // Super naive reference implementation
  sint64  val = vm->gpr[VARG3].s64();
  sint64* src = vm->gpr[VARG2].pS64();
  sint64* dst = vm->gpr[VARG1].pS64();
  uint32  i   = vm->gpr[VARG0].u32();
  while (i--) {
    *dst++ = *src++ >> val;
  }
}
_END_OP

