//****************************************************************************//
//**                                                                        **//
//** File:         op_vec_VMULS_impl.hpp                                     **//
//** Description:  Vector on Vector Multiplication                          **//
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
_DEFINE_OP(VMULS_U64) {
  vm->status = VMDefs::BREAKPOINT;
  vm->exceptionOffset = EXC_OFFSET_EXT;
  return;
  // Super naive reference implementation
//  uint64* src1 = vm->gpr[VARG3].pU64();
//  uint64* src2 = vm->gpr[VARG2].pU64();
//  uint64* dst  = vm->gpr[VARG1].pU64();
//  uint32  i    = vm->gpr[VARG0].u32();
//  while (i--) {
//    *dst++ = *src1++ * *src2++;
//  }
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Signed
_DEFINE_OP(VMULS_S64) {
  vm->status = VMDefs::BREAKPOINT;
  vm->exceptionOffset = EXC_OFFSET_EXT;
  return;
  // Super naive reference implementation
//  sint64* src1 = vm->gpr[VARG3].pS64();
//  sint64* src2 = vm->gpr[VARG2].pS64();
//  sint64* dst  = vm->gpr[VARG1].pS64();
//  uint32  i    = vm->gpr[VARG0].u32();
//  while (i--) {
//    *dst++ = *src1++ * *src2++;
//  }
}
_END_OP



