//****************************************************************************//
//**                                                                        **//
//** File:         op_vec_smin.hpp                                          **//
//** Description:  Find minimum scalar in vector                            **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2017-08-15                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

// Unsigned integer
_DEFINE_OP(VSSUM_U8) {
  // Super naive reference implementation
  uint8* src = vm->gpr[VARG2].pU8();
  uint32 i   = vm->gpr[VARG0].u32();
  uint64 val = 0;
  while (i--) {
    val += *src++;
  }
  vm->gpr[VARG1].u64() = val;
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(VSSUM_U16) {
  // Super naive reference implementation
  uint16* src = vm->gpr[VARG2].pU16();
  uint32  i   = vm->gpr[VARG0].u32();
  uint64  val = 0;
  while (i--) {
    val += *src++;
  }
  vm->gpr[VARG1].u64() = val;
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(VSSUM_U32) {
  // Super naive reference implementation
  uint32* src = vm->gpr[VARG2].pU32();
  uint32  i   = vm->gpr[VARG0].u32();
  uint64  val = 0;
  while (i--) {
    val += *src++;
  }
  vm->gpr[VARG1].u64() = val;
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Signed integer
_DEFINE_OP(VSSUM_S8) {
  // Super naive reference implementation
  sint8* src = vm->gpr[VARG2].pS8();
  uint32 i   = vm->gpr[VARG0].u32();
  sint64 val = 0;
  while (i--) {
    val += *src++;
  }
  vm->gpr[VARG1].s64() = val;
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(VSSUM_S16) {
  // Super naive reference implementation
  sint16* src = vm->gpr[VARG2].pS16();
  uint32  i   = vm->gpr[VARG0].u32();
  sint64  val = 0;
  while (i--) {
    val += *src++;
  }
  vm->gpr[VARG1].s64() = val;
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(VSSUM_S32) {
  // Super naive reference implementation
  sint32* src = vm->gpr[VARG2].pS32();
  uint32  i   = vm->gpr[VARG0].u32();
  sint64  val = 0;
  while (i--) {
    val += *src++;
  }
  vm->gpr[VARG1].s64() = val;
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

