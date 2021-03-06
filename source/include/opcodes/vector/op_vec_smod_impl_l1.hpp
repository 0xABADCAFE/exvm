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

// Float
_DEFINE_OP(VSMOD_F32) {
  // Super naive reference implementation
  float64  val = (float64)vm->gpr[VARG3].f32();
  float32* src = vm->gpr[VARG2].pF32();
  float32* dst = vm->gpr[VARG1].pF32();
  uint32   i   = vm->gpr[VARG0].u32();
  while (i--) {
    *dst++ = (float32) std::fmod((float64)*src++, val);
  }
}
_END_OP

