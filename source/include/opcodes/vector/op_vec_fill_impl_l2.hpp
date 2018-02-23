//****************************************************************************//
//**                                                                        **//
//** File:         op_vec_fill.hpp                                          **//
//** Description:  Vector filling (splat)                                   **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2017-08-15                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

_DEFINE_OP(VFILL_64) {
  // Super naive reference implementation
  uint64  val = vm->gpr[VARG2].u64();
  uint64* dst = vm->gpr[VARG1].pU64();
  uint32  i   = vm->gpr[VARG0].u32();
  while (i--) {
    *dst++ = val;
  }
}
_END_OP

