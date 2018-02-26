//****************************************************************************//
//**                                                                        **//
//** File:         op_vec_sdiv_impl.hpp                                     **//
//** Description:  Scalar on Vector Division                                **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2017-08-15                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

// Unsigned
_DEFINE_OP(VSDIV_U8) {
  // Super naive reference implementation
  uint8  val = vm->gpr[VARG3].u8();
  if (!val) {
    vm->status = VMDefs::ZERO_DIVIDE;
    vm->exceptionOffset = EXC_OFFSET_EXT;
    return;
  }
  uint8* src = vm->gpr[VARG2].pU8();
  uint8* dst = vm->gpr[VARG1].pU8();
  uint32 i   = vm->gpr[VARG0].u32();
  while (i--) {
    *dst++ = *src++ / val;
  }
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(VSDIV_U16) {
  // Super naive reference implementation
  uint16  val = vm->gpr[VARG3].u16();
  if (!val) {
    vm->status = VMDefs::ZERO_DIVIDE;
    vm->exceptionOffset = EXC_OFFSET_EXT;
    return;
  }
  uint16* src = vm->gpr[VARG2].pU16();
  uint16* dst = vm->gpr[VARG1].pU16();
  uint32  i   = vm->gpr[VARG0].u32();
  while (i--) {
    *dst++ = *src++ / val;
  }
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(VSDIV_U32) {
  // Super naive reference implementation
  uint32  val = vm->gpr[VARG3].u32();
  if (!val) {
    vm->status = VMDefs::ZERO_DIVIDE;
    vm->exceptionOffset = EXC_OFFSET_EXT;
    return;
  }
  uint32* src = vm->gpr[VARG2].pU32();
  uint32* dst = vm->gpr[VARG1].pU32();
  uint32  i   = vm->gpr[VARG0].u32();
  while (i--) {
    *dst++ = *src++ / val;
  }
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Signed
_DEFINE_OP(VSDIV_S8) {
  // Super naive reference implementation
  sint8  val = vm->gpr[VARG3].s8();
  if (!val) {
    vm->status = VMDefs::ZERO_DIVIDE;
    vm->exceptionOffset = EXC_OFFSET_EXT;
    return;
  }
  sint8* src = vm->gpr[VARG2].pS8();
  sint8* dst = vm->gpr[VARG1].pS8();
  uint32 i   = vm->gpr[VARG0].u32();
  while (i--) {
    *dst++ = *src++ / val;
  }
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(VSDIV_S16) {
  // Super naive reference implementation
  sint16  val = vm->gpr[VARG3].s16();
  if (!val) {
    vm->status = VMDefs::ZERO_DIVIDE;
    vm->exceptionOffset = EXC_OFFSET_EXT;
    return;
  }
  sint16* src = vm->gpr[VARG2].pS16();
  sint16* dst = vm->gpr[VARG1].pS16();
  uint32  i   = vm->gpr[VARG0].u32();
  while (i--) {
    *dst++ = *src++ / val;
  }
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(VSDIV_S32) {
  // Super naive reference implementation
  sint32  val = vm->gpr[VARG3].s32();
  if (!val) {
    vm->status = VMDefs::ZERO_DIVIDE;
    vm->exceptionOffset = EXC_OFFSET_EXT;
    return;
  }
  sint32* src = vm->gpr[VARG2].pS32();
  sint32* dst = vm->gpr[VARG1].pS32();
  uint32  i   = vm->gpr[VARG0].u32();
  while (i--) {
    *dst++ = *src++ / val;
  }
}
_END_OP

