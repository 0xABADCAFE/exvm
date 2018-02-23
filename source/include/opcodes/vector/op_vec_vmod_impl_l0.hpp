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

// Unsigned
_DEFINE_OP(VMOD_U8) {
  // Super naive reference implementation
  uint8* src1 = vm->gpr[VARG3].pU8();
  uint8* src2 = vm->gpr[VARG2].pU8();
  uint8* dst  = vm->gpr[VARG1].pU8();
  uint32 i    = vm->gpr[VARG0].u32();
  while (i--) {
    *dst++ = *src1++ % *src2++;
  }
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(VMOD_U16) {
  // Super naive reference implementation
  uint16* src1 = vm->gpr[VARG3].pU16();
  uint16* src2 = vm->gpr[VARG2].pU16();
  uint16* dst  = vm->gpr[VARG1].pU16();
  uint32  i    = vm->gpr[VARG0].u32();
  while (i--) {
    *dst++ = *src1++ % *src2++;
  }
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(VMOD_U32) {
  // Super naive reference implementation
  uint32* src1 = vm->gpr[VARG3].pU32();
  uint32* src2 = vm->gpr[VARG2].pU32();
  uint32* dst  = vm->gpr[VARG1].pU32();
  uint32  i    = vm->gpr[VARG0].u32();
  while (i--) {
    *dst++ = *src1++ % *src2++;
  }
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(VMOD_S8) {
  // Super naive reference implementation
  sint8* src1 = vm->gpr[VARG3].pS8();
  sint8* src2 = vm->gpr[VARG2].pS8();
  sint8* dst  = vm->gpr[VARG1].pS8();
  uint32 i    = vm->gpr[VARG0].u32();
  while (i--) {
    *dst++ = *src1++ % *src2++;
  }
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(VMOD_S16) {
  // Super naive reference implementation
  sint16* src1 = vm->gpr[VARG3].pS16();
  sint16* src2 = vm->gpr[VARG2].pS16();
  sint16* dst  = vm->gpr[VARG1].pS16();
  uint32  i    = vm->gpr[VARG0].u32();
  while (i--) {
    *dst++ = *src1++ % *src2++;
  }
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(VMOD_S32) {
  // Super naive reference implementation
  sint32* src1 = vm->gpr[VARG3].pS32();
  sint32* src2 = vm->gpr[VARG2].pS32();
  sint32* dst  = vm->gpr[VARG1].pS32();
  uint32  i    = vm->gpr[VARG0].u32();
  while (i--) {
    *dst++ = *src1++ % *src2++;
  }
}
_END_OP



