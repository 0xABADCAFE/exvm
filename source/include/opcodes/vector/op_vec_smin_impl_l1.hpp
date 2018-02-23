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
_DEFINE_OP(VSMIN_F32) {
  // Super naive reference implementation
  float32* src = vm->gpr[VARG2].pF32();
  uint32   i   = vm->gpr[VARG0].u32();
  float32  val = *src;

  // Bail if we find min
  while (i--) {
    float32 val2 = *src++;
    if (val2 < val) {
      val = val2;
    }
  }
  vm->gpr[VARG1].f32() = val;
}
_END_OP

