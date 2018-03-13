//****************************************************************************//
//**                                                                        **//
//** File:         op_vec_vdiv_saturated_impl.hpp                           **//
//** Description:  Vector on Vector Division, Saturated                     **//
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

// Signed
_DEFINE_OP(VDIVS_S8) {
  vm->status = VMDefs::BREAKPOINT;
  vm->exceptionOffset = EXC_OFFSET_EXT;
  return;
  // Super naive reference implementation
//  sint8* src1 = vm->gpr[VARG3].pS8();
//  sint8* src2 = vm->gpr[VARG2].pS8();
//  sint8* dst  = vm->gpr[VARG1].pS8();
//  uint32 i    = vm->gpr[VARG0].u32();
//  while (i--) {
//    *dst++ = *src1++ / *src2++;
//  }
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(VDIVS_S16) {
  vm->status = VMDefs::BREAKPOINT;
  vm->exceptionOffset = EXC_OFFSET_EXT;
  return;
  // Super naive reference implementation
//  sint16* src1 = vm->gpr[VARG3].pS16();
//  sint16* src2 = vm->gpr[VARG2].pS16();
//  sint16* dst  = vm->gpr[VARG1].pS16();
//  uint32  i    = vm->gpr[VARG0].u32();
//  while (i--) {
//    *dst++ = *src1++ / *src2++;
//  }
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(VDIVS_S32) {
  vm->status = VMDefs::BREAKPOINT;
  vm->exceptionOffset = EXC_OFFSET_EXT;
  return;
  // Super naive reference implementation
//  sint32* src1 = vm->gpr[VARG3].pS32();
//  sint32* src2 = vm->gpr[VARG2].pS32();
//  sint32* dst  = vm->gpr[VARG1].pS32();
//  uint32  i    = vm->gpr[VARG0].u32();
//  while (i--) {
//    *dst++ = *src1++ / *src2++;
//  }
}
_END_OP

