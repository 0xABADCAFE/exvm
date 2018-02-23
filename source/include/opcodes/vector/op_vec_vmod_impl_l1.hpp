//****************************************************************************//
//**                                                                        **//
//** File:         op_vec_vmod_impl.hpp                                     **//
//** Description:  Vector on Vector Modulus                                 **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2017-08-15                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

// TODO - division by zero

// Float
_DEFINE_OP(VMOD_F32) {
  // Super naive reference implementation
  float32* src1 = vm->gpr[VARG3].pF32();
  float32* src2 = vm->gpr[VARG2].pF32();
  float32* dst  = vm->gpr[VARG1].pF32();
  uint32   i    = vm->gpr[VARG0].u32();
  while (i--) {
    *dst++ = (float32)std::fmod((float64)*src1++, (float64)*src2++);
  }
}
_END_OP

