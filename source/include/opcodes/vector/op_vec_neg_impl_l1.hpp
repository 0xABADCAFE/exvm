//****************************************************************************//
//**                                                                        **//
//** File:         op_vec_neg_impl.hpp                                      **//
//** Description:  Vector sign negation                                     **//
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
_DEFINE_OP(VNEG_F32) {
  // Super naive reference implementation
  float32* src = vm->gpr[VARG2].pF32();
  float32* dst = vm->gpr[VARG1].pF32();
  uint32   i   = vm->gpr[VARG0].u32();
  while (i--) {
    *dst++ = -(*src++);
  }
}
_END_OP

