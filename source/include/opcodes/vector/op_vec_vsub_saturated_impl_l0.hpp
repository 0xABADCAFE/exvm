//****************************************************************************//
//**                                                                        **//
//** File:         op_vec_vsub_saturated_impl.hpp                           **//
//** Description:  Vector on Vector Subtraction, Saturating                 **//
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
_DEFINE_OP(VSUBS_U8) {
  // Super naive reference implementation
  uint8*  src1 = vm->gpr[(vArgs & 0xF000) >> 12].pU8();
  uint8*  src2 = vm->gpr[(vArgs & 0x0F00) >>  8].pU8();
  uint8*  dst  = vm->gpr[(vArgs & 0x00F0) >>  4].pU8();
  uint32  i    = vm->gpr[(vArgs & 0x000F)].u32();
  while (i--) {
    // TODO - validate correctness
    uint8 val = *src1++;
    uint8 res = val - *src2++;
    *dst++    = res & -(res <= val);
  }
}
_END_OP

_DEFINE_OP(VSUBS_U16) {
  // Super naive reference implementation
  uint16* src1 = vm->gpr[(vArgs & 0xF000) >> 12].pU16();
  uint16* src2 = vm->gpr[(vArgs & 0x0F00) >>  8].pU16();
  uint16* dst  = vm->gpr[(vArgs & 0x00F0) >>  4].pU16();
  uint32  i    = vm->gpr[(vArgs & 0x000F)].u32();
  while (i--) {
    // TODO - validate correctness
    uint16 val = *src1++;
    uint16 res = val - *src2++;
    *dst++     = res & -(res <= val);
  }
}
_END_OP

_DEFINE_OP(VSUBS_U32) {
  // Super naive reference implementation
  uint32* src1 = vm->gpr[(vArgs & 0xF000) >> 12].pU32();
  uint32* src2 = vm->gpr[(vArgs & 0x0F00) >>  8].pU32();
  uint32* dst  = vm->gpr[(vArgs & 0x00F0) >>  4].pU32();
  uint32  i    = vm->gpr[(vArgs & 0x000F)].u32();
  while (i--) {
    // TODO - validate correctness
    uint32 val = *src1++;
    uint32 res = val - *src2++;
    *dst++     = res & -(res <= val);
  }
}
_END_OP

// Signed
_DEFINE_OP(VSUBS_S8) {
  vm->status = VMDefs::BREAKPOINT;
  return;

//   // Super naive reference implementation
//   sint8*  src1 = vm->gpr[(vArgs & 0xF000) >> 12].pS8();
//   sint8*  src2 = vm->gpr[(vArgs & 0x0F00) >>  8].pS8();
//   sint8*  dst  = vm->gpr[(vArgs & 0x00F0) >>  4].pS8();
//   uint32  i    = vm->gpr[(vArgs & 0x000F)].u32();
//   while (i--) {
//     // TODO - validate correctness
//
//   }
}
_END_OP

_DEFINE_OP(VSUBS_S16) {
  vm->status = VMDefs::BREAKPOINT;
  return;

//   // Super naive reference implementation
//   sint16* src1 = vm->gpr[(vArgs & 0xF000) >> 12].pS16();
//   sint16* src2 = vm->gpr[(vArgs & 0x0F00) >>  8].pS16();
//   sint16* dst  = vm->gpr[(vArgs & 0x00F0) >>  4].pS16();
//   uint32  i    = vm->gpr[(vArgs & 0x000F)].u32();
//   while (i--) {
//     // TODO - validate correctness
//
//   }
}
_END_OP

_DEFINE_OP(VSUBS_S32) {
  vm->status = VMDefs::BREAKPOINT;
  return;

//   // Super naive reference implementation
//   sint32* src1 = vm->gpr[(vArgs & 0xF000) >> 12].pS32();
//   sint32* src2 = vm->gpr[(vArgs & 0x0F00) >>  8].pS32();
//   sint32* dst  = vm->gpr[(vArgs & 0x00F0) >>  4].pS32();
//   uint32  i    = vm->gpr[(vArgs & 0x000F)].u32();
//   while (i--) {
//     // TODO - validate correctness
//
//   }
}
_END_OP

