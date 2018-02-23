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

// Float
_DEFINE_OP(VSADD_F32) {
  // Super naive reference implementation
  float32  val = vm->gpr[VARG3].f32();
  float32* src = vm->gpr[VARG2].pF32();
  float32* dst = vm->gpr[VARG1].pF32();
  uint32   i   = vm->gpr[VARG0].u32();
  while (i--) {
    *dst++ = val + *src++;
  }
}
_END_OP

