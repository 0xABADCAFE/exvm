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
_DEFINE_OP(VDIVS_S64) {
  vm->status = VMDefs::BREAKPOINT;
  return;
  // Super naive reference implementation
//  sint64* src1 = vm->gpr[(vArgs & 0xF000) >> 12].pS64();
//  sint64* src2 = vm->gpr[(vArgs & 0x0F00) >>  8].pS64();
//  sint64* dst  = vm->gpr[(vArgs & 0x00F0) >>  4].pS64();
//  uint32  i    = vm->gpr[(vArgs & 0x000F)].u32();
//  while (i--) {
//    *dst++ = *src1++ / *src2++;
//  }
}
_END_OP



