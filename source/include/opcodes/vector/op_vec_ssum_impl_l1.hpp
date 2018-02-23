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

// Floatng point
_DEFINE_OP(VSSUM_F32) {
  // Super naive reference implementation
  float32* src = vm->gpr[VARG2].pF32();
  uint32   i   = vm->gpr[VARG0].u32();
  float64  val = 0;
  while (i--) {
    val += *src++;
  }
  vm->gpr[VARG1].f64() = val;
}
_END_OP

