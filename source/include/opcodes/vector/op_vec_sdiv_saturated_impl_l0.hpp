//****************************************************************************//
//**                                                                        **//
//** File:         op_vec_sdiv_saturated_impl.hpp                           **//
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

// Unsigned - no different to non-saturating version

// Signed
_DEFINE_OP(VSDIVS_S8) {
  vm->status = VMDefs::BREAKPOINT;
  return;
//   // Super naive reference implementation
//   sint8  val = vm->gpr[(vArgs & 0xF000) >> 12].s8();
//   if (!val) {
//     vm->status = VMDefs::ZERO_DIVIDE;
//     return;
//   }
//   sint8* src = vm->gpr[(vArgs & 0x0F00) >>  8].pS8();
//   sint8* dst = vm->gpr[(vArgs & 0x00F0) >>  4].pS8();
//   uint32 i   = vm->gpr[(vArgs & 0x000F)].u32();
//   while (i--) {
//     *dst++ = *src++ / val;
//   }
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(VSDIVS_S16) {
  vm->status = VMDefs::BREAKPOINT;
  return;
//   // Super naive reference implementation
//   sint16  val = vm->gpr[(vArgs & 0xF000) >> 12].s16();
//   if (!val) {
//     vm->status = VMDefs::ZERO_DIVIDE;
//     return;
//   }
//   sint16* src = vm->gpr[(vArgs & 0x0F00) >>  8].pS16();
//   sint16* dst = vm->gpr[(vArgs & 0x00F0) >>  4].pS16();
//   uint32 i    = vm->gpr[(vArgs & 0x000F)].u32();
//   while (i--) {
//     *dst++ = *src++ / val;
//   }
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(VSDIVS_S32) {
  vm->status = VMDefs::BREAKPOINT;
  return;
//   // Super naive reference implementation
//   sint32  val = vm->gpr[(vArgs & 0xF000) >> 12].s32();
//   if (!val) {
//     vm->status = VMDefs::ZERO_DIVIDE;
//     return;
//   }
//   sint32* src = vm->gpr[(vArgs & 0x0F00) >>  8].pS32();
//   sint32* dst = vm->gpr[(vArgs & 0x00F0) >>  4].pS32();
//   uint32  i   = vm->gpr[(vArgs & 0x000F)].u32();
//   while (i--) {
//     *dst++ = *src++ / val;
//   }
}
_END_OP

