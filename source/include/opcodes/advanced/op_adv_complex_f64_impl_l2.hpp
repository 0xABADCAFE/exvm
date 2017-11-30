//****************************************************************************//
//**                                                                        **//
//** File:         op_adv_vec2_f64_impl.hpp                                 **//
//** Description:  Operations for vec2d                                     **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2017-08-19                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

// Complex Multiply of vec2d (real,imaginary)
_DEFINE_OP(MUL_C2F64) {
  const float64* src1 = vm->gpr[(vArgs & 0x0F00) >> 8].pF64();
  const float64* src2 = vm->gpr[(vArgs & 0x00F0) >> 4].pF64();
  float64*       dst  = vm->gpr[(vArgs & 0x000F)].pF64();

  // (a + bi)(c + di) = (ac - bd) + (bc + ad)i

  //              a * c        -        b * d
  dst[0] = (src1[0] * src2[0]) - (src1[1] * src2[1]);

  //              b * c        +        a * d
  dst[1] = (src1[1] * src2[0]) + (src1[0] * src2[1]);
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Complex Division of vec2d (real, imaginary)
_DEFINE_OP(DIV_C2F64) {
  const float64* src1 = vm->gpr[(vArgs & 0x0F00) >> 8].pF64();
  const float64* src2 = vm->gpr[(vArgs & 0x00F0) >> 4].pF64();
  float64*       dst  = vm->gpr[(vArgs & 0x000F)].pF64();

  float64 denominator = ((src2[0] * src2[0]) + (src2[1] * src2[1]));

  //               a * c        +        b * c         / (c^2 + d^2)
  dst[0] = ((src1[0] * src2[0]) + (src1[1] * src2[1])) / denominator;

  //               b * c        -        a * d         / (c^2 + d^2)
  dst[1] = ((src1[1] * src2[0]) - (src1[0] * src2[1])) / denominator;
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

