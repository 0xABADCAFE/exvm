//****************************************************************************//
//**                                                                        **//
//** File:         op_vec_inv_impl.hpp                                      **//
//** Description:  Vector bitwise inverse                                   **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2017-08-19                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

_DEFINE_OP(VINV_8) {
  // Super naive reference implementation
  sint8* src = vm->gpr[VARG2].pS8();
  sint8* dst = vm->gpr[VARG1].pS8();
  uint32 i   = vm->gpr[VARG0].u32();
  while (i--) {
    *dst++ = ~(*src++);
  }
}
_END_OP

