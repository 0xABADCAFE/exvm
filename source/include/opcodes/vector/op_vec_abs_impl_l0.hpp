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

// Integer
_DEFINE_OP(VABS_S8) {
  // Super naive reference implementation
  sint8* src = vm->gpr[VARG2].pS8();
  sint8* dst = vm->gpr[VARG1].pS8();
  uint32 i   = vm->gpr[VARG0].u32();
  while (i--) {
    sint8 val  = *src++;
    sint8 sign = val >> 7;
    *dst++     = (val ^ sign) - sign;
  }
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(VABS_S16) {
  // Super naive reference implementation
  sint16* src = vm->gpr[VARG2].pS16();
  sint16* dst = vm->gpr[VARG1].pS16();
  uint32  i   = vm->gpr[VARG0].u32();
  while (i--) {
    sint16 val  = *src++;
    sint16 sign = val >> 15;
    *dst++     = (val ^ sign) - sign;
  }
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(VABS_S32) {
  // Super naive reference implementation
  sint32* src = vm->gpr[VARG2].pS32();
  sint32* dst = vm->gpr[VARG1].pS32();
  uint32  i   = vm->gpr[VARG0].u32();
  while (i--) {
    sint32 val  = *src++;
    sint32 sign = val >> 31;
    *dst++     = (val ^ sign) - sign;
  }
}
_END_OP

