//****************************************************************************//
//**                                                                        **//
//** File:         op_vec_vadd_saturated_impl.hpp                           **//
//** Description:  Vector on Vector Addition, Saturating                    **//
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
_DEFINE_OP(VADDS_U8) {
  // Super naive reference implementation
  uint8*  src1 = vm->gpr[VARG3].pU8();
  uint8*  src2 = vm->gpr[VARG2].pU8();
  uint8*  dst  = vm->gpr[VARG1].pU8();
  uint32  i    = vm->gpr[VARG0].u32();
  while (i--) {
    // TODO - src1idate correctness
    uint8 val = *src1++;
    uint8 res = val + *src2++;
    *dst++ = res | -(res < val);
  }
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(VADDS_U16) {
  // Super naive reference implementation
  uint16* src1 = vm->gpr[VARG3].pU16();
  uint16* src2 = vm->gpr[VARG2].pU16();
  uint16* dst  = vm->gpr[VARG1].pU16();
  uint32  i    = vm->gpr[VARG0].u32();
  while (i--) {
    // TODO - src1idate correctsness
    uint16 val = *src1++;
    uint16 res = val + *src2++;
    *dst++ = res | -(res < val);
  }
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(VADDS_U32) {
  // Super naive reference implementation
  uint32* src1 = vm->gpr[VARG3].pU32();
  uint32* src2 = vm->gpr[VARG2].pU32();
  uint32* dst  = vm->gpr[VARG1].pU32();
  uint32  i    = vm->gpr[VARG0].u32();
  while (i--) {
    // TODO - src1idate correctness
    uint32 val = *src1++;
    uint32 res = val + *src2++;
    *dst++ = res | -(res < val);
  }
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Signed
_DEFINE_OP(VADDS_S8) {
  vm->status = VMDefs::BREAKPOINT;
  vm->exceptionOffset = EXC_OFFSET_EXT;
  return;

//   // Super naive reference implementation
//   sint8*  src1 = vm->gpr[VARG3].pS8();
//   sint8*  src2 = vm->gpr[VARG2].pS8();
//   sint8*  dst = vm->gpr[VARG1].pS8();
//   uint32  i   = vm->gpr[VARG0].u32();
//   while (i--) {
//     // TODO - src1idate correctness
//
//  }
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(VADDS_S16) {
  vm->status = VMDefs::BREAKPOINT;
  vm->exceptionOffset = EXC_OFFSET_EXT;
  return;

//   // Super naive reference implementation
//   sint16* src1 = vm->gpr[VARG3].pS16();
//   sint16* src2 = vm->gpr[VARG2].pS16();
//   sint16* dst = vm->gpr[VARG1].pS16();
//   uint32  i   = vm->gpr[VARG0].u32();
//   while (i--) {
//     // TODO - src1idate correctness
//
//   }
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(VADDS_S32) {
  vm->status = VMDefs::BREAKPOINT;
  vm->exceptionOffset = EXC_OFFSET_EXT;
  return;

//   // Super naive reference implementation
//   sint32* src1 = vm->gpr[VARG3].pS32();
//   sint32* src2 = vm->gpr[VARG2].pS32();
//   sint32* dst = vm->gpr[VARG1].pS32();
//   uint32  i   = vm->gpr[VARG0].u32();
//   while (i--) {
//     // TODO - src1idate correctness
//
//   }
}
_END_OP


