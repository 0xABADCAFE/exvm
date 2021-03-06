//****************************************************************************//
//**                                                                        **//
//** File:         op_vec_vmul_impl.hpp                                     **//
//** Description:  Vector on Vector Multiplication                          **//
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
_DEFINE_OP(VMUL_F32) {
  // Super naive reference implementation
  float32* src1 = vm->gpr[VARG3].pF32();
  float32* src2 = vm->gpr[VARG2].pF32();
  float32* dst  = vm->gpr[VARG1].pF32();
  uint32   i    = vm->gpr[VARG0].u32();
  while (i--) {
    *dst++ = *src1++ * *src2++;
  }
}
_END_OP

