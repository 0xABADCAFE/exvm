//****************************************************************************//
//**                                                                        **//
//** File:         op_vec_sadd_saturated_impl.hpp                           **//
//** Description:  Scalar on Vector Addition, Saturating                    **//
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
_DEFINE_OP(VSADDS_U8) {
  // Super naive reference implementation
  uint8   val = vm->gpr[VARG3].u8();
  uint8*  src = vm->gpr[VARG2].pU8();
  uint8*  dst = vm->gpr[VARG1].pU8();
  uint32  i   = vm->gpr[VARG0].u32();
  while (i--) {
    // TODO - validate correctness
    uint8 res = val + *src++;
    *dst++    = res | -(res < val);
  }
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(VSADDS_U16) {
  // Super naive reference implementation
  uint16  val = vm->gpr[VARG3].u16();
  uint16* src = vm->gpr[VARG2].pU16();
  uint16* dst = vm->gpr[VARG1].pU16();
  uint32  i   = vm->gpr[VARG0].u32();
  while (i--) {
    // TODO - validate correctness
    uint16 res = val + *src++;
    *dst++     = res | -(res < val);
  }
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(VSADDS_U32) {
  // Super naive reference implementation
  uint32  val = vm->gpr[VARG3].u32();
  uint32* src = vm->gpr[VARG2].pU32();
  uint32* dst = vm->gpr[VARG1].pU32();
  uint32  i   = vm->gpr[VARG0].u32();
  while (i--) {
    // TODO - validate correctness
    uint32 res = val + *src++;
    *dst++     = res | -(res < val);
  }
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Signed
_DEFINE_OP(VSADDS_S8) {
  vm->status = VMDefs::BREAKPOINT;
  return;

//   // Super naive reference implementation
//   sint8   val = vm->gpr[VARG3].s8();
//   sint8*  src = vm->gpr[VARG2].pS8();
//   sint8*  dst = vm->gpr[VARG1].pS8();
//   uint32  i   = vm->gpr[VARG0].u32();
//   while (i--) {
//     // TODO - validate correctness
//
//  }
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(VSADDS_S16) {
  vm->status = VMDefs::BREAKPOINT;
  return;

//   // Super naive reference implementation
//   sint16  val = vm->gpr[VARG3].s16();
//   sint16* src = vm->gpr[VARG2].pS16();
//   sint16* dst = vm->gpr[VARG1].pS16();
//   uint32  i   = vm->gpr[VARG0].u32();
//   while (i--) {
//     // TODO - validate correctness
//
//   }
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(VSADDS_S32) {
  vm->status = VMDefs::BREAKPOINT;
  return;

//   // Super naive reference implementation
//   sint32  val = vm->gpr[VARG3].s32();
//   sint32* src = vm->gpr[VARG2].pS32();
//   sint32* dst = vm->gpr[VARG1].pS32();
//   uint32  i   = vm->gpr[VARG0].u32();
//   while (i--) {
//     // TODO - validate correctness
//
//   }
}
_END_OP

