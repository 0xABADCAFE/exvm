//****************************************************************************//
//**                                                                        **//
//** File:         op_vec_slsr_impl.hpp                                     **//
//** Description:  Scalar on Vector logical shift right                     **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2017-08-19                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

_DEFINE_OP(VSLSR_8) {
  // Super naive reference implementation
  uint32 val = vm->gpr[VARG3].u8() & 0x7;
  uint8* src = vm->gpr[VARG2].pU8();
  uint8* dst = vm->gpr[VARG1].pU8();
  uint32 i   = vm->gpr[VARG0].u32();
  while (i--) {
    *dst++ = *src++ >> val;
  }
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(VSLSR_16) {
  // Super naive reference implementation
  uint32  val = vm->gpr[VARG3].u8() & 0xF;
  uint16* src = vm->gpr[VARG2].pU16();
  uint16* dst = vm->gpr[VARG1].pU16();
  uint32  i   = vm->gpr[VARG0].u32();
  while (i--) {
    *dst++ = *src++ >> val;
  }
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(VSLSR_32) {
  // Super naive reference implementation
  uint32  val = vm->gpr[VARG3].u8() & 0x1F;
  uint32* src = vm->gpr[VARG2].pU32();
  uint32* dst = vm->gpr[VARG1].pU32();
  uint32  i   = vm->gpr[VARG0].u32();
  while (i--) {
    *dst++ = *src++ >> val;
  }
}
_END_OP

