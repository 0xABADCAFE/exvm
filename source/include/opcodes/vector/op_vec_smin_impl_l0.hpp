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
_DEFINE_OP(VSMIN_U8) {
  // Super naive reference implementation
  uint8* src = vm->gpr[VARG2].pU8();
  uint32 i   = vm->gpr[VARG0].u32();
  uint8  val = *src;

  // Bail if we find zero
  while (val && i--) {
    uint8 val2 = *src++;
    if (val2 < val) {
      val = val2;
    }
  }
  vm->gpr[VARG1].u8() = val;
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(VSMIN_U16) {
  // Super naive reference implementation
  uint16* src = vm->gpr[VARG2].pU16();
  uint32  i   = vm->gpr[VARG0].u32();
  uint16  val = *src;

  // Bail if we find zero
  while (val && i--) {
    uint16 val2 = *src++;
    if (val2 < val) {
      val = val2;
    }
  }
  vm->gpr[VARG1].u16() = val;
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(VSMIN_U32) {
  // Super naive reference implementation
  uint32* src = vm->gpr[VARG2].pU32();
  uint32  i   = vm->gpr[VARG0].u32();
  uint32  val = *src;

  // Bail if we find zero
  while (val && i--) {
    uint32 val2 = *src++;
    if (val2 < val) {
      val = val2;
    }
  }
  vm->gpr[VARG1].u32() = val;
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Signed integer
_DEFINE_OP(VSMIN_S8) {
  // Super naive reference implementation
  sint8* src = vm->gpr[VARG2].pS8();
  uint32 i   = vm->gpr[VARG0].u32();
  sint8  min = 0x80;
  sint8  val = *src;

  // Bail if we find min
  while (val > min && i--) {
    sint8 val2 = *src++;
    if (val2 < val) {
      val = val2;
    }
  }
  vm->gpr[VARG1].s8() = val;
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(VSMIN_S16) {
  // Super naive reference implementation
  sint16* src = vm->gpr[VARG2].pS16();
  uint32  i   = vm->gpr[VARG0].u32();
  sint16  min = 0x8000;
  sint16  val = *src;

  // Bail if we find min
  while (val > min && i--) {
    sint16 val2 = *src++;
    if (val2 < val) {
      val = val2;
    }
  }
  vm->gpr[VARG1].s16() = val;
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(VSMIN_S32) {
  // Super naive reference implementation
  sint32* src = vm->gpr[VARG2].pS32();
  uint32  i   = vm->gpr[VARG0].u32();
  sint32  min = 0x80000000;
  sint32  val = *src;

  // Bail if we find min
  while (val > min && i--) {
    sint32 val2 = *src++;
    if (val2 < val) {
      val = val2;
    }
  }
  vm->gpr[VARG1].s32() = val;
}
_END_OP

