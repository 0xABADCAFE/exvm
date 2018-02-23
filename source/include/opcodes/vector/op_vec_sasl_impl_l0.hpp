//****************************************************************************//
//**                                                                        **//
//** File:         op_vec_sasl_impl.hpp                                     **//
//** Description:  Scalar on Vector arithmetic shift left                   **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2017-08-19                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

_DEFINE_OP(VSASL_8) {
  // Super naive reference implementation
  sint8  val = vm->gpr[VARG3].s8();
  sint8* src = vm->gpr[VARG2].pS8();
  sint8* dst = vm->gpr[VARG1].pS8();
  uint32 i   = vm->gpr[VARG0].u32();
  while (i--) {
    *dst++ = *src++ << val;
  }
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(VSASL_16) {
  // Super naive reference implementation
  sint16  val = vm->gpr[VARG3].s16();
  sint16* src = vm->gpr[VARG2].pS16();
  sint16* dst = vm->gpr[VARG1].pS16();
  uint32  i   = vm->gpr[VARG0].u32();
  while (i--) {
    *dst++ = *src++ << val;
  }
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(VSASL_32) {
  // Super naive reference implementation
  sint32  val = vm->gpr[VARG3].s32();
  sint32* src = vm->gpr[VARG2].pS32();
  sint32* dst = vm->gpr[VARG1].pS32();
  uint32  i   = vm->gpr[VARG0].u32();
  while (i--) {
    *dst++ = *src++ << val;
  }
}
_END_OP

