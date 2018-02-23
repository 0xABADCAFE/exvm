//****************************************************************************//
//**                                                                        **//
//** File:         op_vec_abs_impl.hpp                                      **//
//** Description:  Vector absolute (sign)                                   **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2017-08-19                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

// Float
_DEFINE_OP(VABS_F32) {
  // Super naive reference implementation
  uint32* src  = vm->gpr[VARG2].pU32();
  uint32* dst  = vm->gpr[VARG1].pU32();
  uint32  i    = vm->gpr[VARG0].u32();

  // Mask off the sign bit.
  uint32  mask = 0x7FFFFFFF;
  while (i--) {
    *dst++ = *src++ & mask;
  }
}
_END_OP

