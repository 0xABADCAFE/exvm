//****************************************************************************//
//**                                                                        **//
//** File:         op_vec_vmac_impl.hpp                                     **//
//** Description:  Vector multiply accumulate                               **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2017-09-05                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

// Float
_DEFINE_OP(VMAC_F32) {
  // Super naive reference implementation
  float32* src1 = vm->gpr[VARG3].pF32();
  float32* src2 = vm->gpr[VARG2].pF32();
  float32  acc  = 0;
  uint32   i    = vm->gpr[VARG0].u32();

  if (src1 != src2) {
    while (i--) {
      acc += *src1++ * *src2++;
    }
  } else {
    // Special case - sum of squares
    while (i--) {
      float32 tmp = *src1++;
      acc += tmp * tmp;
    }
  }
  vm->gpr[VARG1].f32() = acc;
}
_END_OP

