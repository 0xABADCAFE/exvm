//****************************************************************************//
//**                                                                        **//
//** File:         op_vec_smul_saturated_impl.hpp                           **//
//** Description:  Scalar on Vector Multiplication                          **//
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

_DEFINE_OP(VSMULS_U64) {
  vm->status = VMDefs::BREAKPOINT;
  return;
//   // Super naive reference implementation
//   uint64  val = vm->gpr[(vArgs & 0xF000) >> 12].u64();
//   uint64* src = vm->gpr[(vArgs & 0x0F00) >>  8].pU64();
//   uint64* dst = vm->gpr[(vArgs & 0x00F0) >>  4].pU64();
//   uint32  i   = vm->gpr[(vArgs & 0x000F)].u32();
//   while (i--) {
//     *dst++ = val * *src++;
//   }
}
_END_OP

// Signed
_DEFINE_OP(VSMULS_S64) {
  vm->status = VMDefs::BREAKPOINT;
  return;
//  // Super naive reference implementation
//   sint64  val = vm->gpr[(vArgs & 0xF000) >> 12].s64();
//   sint64* src = vm->gpr[(vArgs & 0x0F00) >>  8].pS64();
//   sint64* dst = vm->gpr[(vArgs & 0x00F0) >>  4].pS64();
//   uint32  i   = vm->gpr[(vArgs & 0x000F)].u32();
//   while (i--) {
//     *dst++ = val * *src++;
//   }
}
_END_OP

