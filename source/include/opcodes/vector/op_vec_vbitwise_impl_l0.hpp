//****************************************************************************//
//**                                                                        **//
//** File:         op_vec_vbitwise_impl.hpp                                 **//
//** Description:  Vector on Vector Bitwise Operations                      **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2017-08-15                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

_DEFINE_OP(VAND_8) {
  // Super naive reference implementation
  uint8* src1 = vm->gpr[VARG3].pU8();
  uint8* src2 = vm->gpr[VARG2].pU8();
  uint8* dst  = vm->gpr[VARG1].pU8();
  uint32 i    = vm->gpr[VARG0].u32();
  while (i--) {
    *dst++ = *src1++ & *src2++;
  }
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(VOR_8) {
  // Super naive reference implementation
  uint8* src1 = vm->gpr[VARG3].pU8();
  uint8* src2 = vm->gpr[VARG2].pU8();
  uint8* dst  = vm->gpr[VARG1].pU8();
  uint32 i    = vm->gpr[VARG0].u32();
  while (i--) {
    *dst++ = *src1++ | *src2++;
  }
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(VXOR_8) {
  // Super naive reference implementation
  uint8* src1 = vm->gpr[VARG3].pU8();
  uint8* src2 = vm->gpr[VARG2].pU8();
  uint8* dst  = vm->gpr[VARG1].pU8();
  uint32 i    = vm->gpr[VARG0].u32();
  while (i--) {
    *dst++ = *src1++ ^ *src2++;
  }
}
_END_OP

