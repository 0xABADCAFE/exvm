//****************************************************************************//
//**                                                                        **//
//** File:         op_vec_sand_impl.hpp                                     **//
//** Description:  Scalar on Vector bitwise OR                              **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2017-08-19                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

_DEFINE_OP(VSOR_64) {
  // Super naive reference implementation
  uint64  val = vm->gpr[VARG3].u64();
  uint64* src = vm->gpr[VARG2].pU64();
  uint64* dst = vm->gpr[VARG1].pU64();
  uint32  i   = vm->gpr[VARG0].u32();
  while (i--) {
    *dst++ = val | *src++;
  }
}
_END_OP
