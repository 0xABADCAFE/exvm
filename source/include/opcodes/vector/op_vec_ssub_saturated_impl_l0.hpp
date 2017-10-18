//****************************************************************************//
//**                                                                        **//
//** File:         op_vec_ssub_saturated_impl.hpp                           **//
//** Description:  Scalar on Vector Subtraction, Saturating                 **//
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
_DEFINE_OP(VSSUBS_U8) {
  // Super naive reference implementation
  uint8  val = vm->gpr[(vArgs & 0xF000) >> 12].u8();
  uint8*  src = vm->gpr[(vArgs & 0x0F00) >>  8].pU8();
  uint8*  dst = vm->gpr[(vArgs & 0x00F0) >>  4].pU8();
  uint32  i   = vm->gpr[(vArgs & 0x000F)].u32();
  while (i--) {
    // TODO - validate correctness
    uint8 val2 = *src++;
    uint8 res  = val2 - val;
    *dst++ = res & -(res <= val2);
  }
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(VSSUBS_U16) {
  // Super naive reference implementation
  uint16  val = vm->gpr[(vArgs & 0xF000) >> 12].u16();
  uint16* src = vm->gpr[(vArgs & 0x0F00) >>  8].pU16();
  uint16* dst = vm->gpr[(vArgs & 0x00F0) >>  4].pU16();
  uint32  i   = vm->gpr[(vArgs & 0x000F)].u32();
  while (i--) {
    // TODO - validate correctness
    uint16 val2 = *src++;
    uint16 res  = val2 - val;
    *dst++ = res & -(res <= val2);
  }
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(VSSUBS_U32) {
  // Super naive reference implementation
  uint32  val = vm->gpr[(vArgs & 0xF000) >> 12].u32();
  uint32* src = vm->gpr[(vArgs & 0x0F00) >>  8].pU32();
  uint32* dst = vm->gpr[(vArgs & 0x00F0) >>  4].pU32();
  uint32  i   = vm->gpr[(vArgs & 0x000F)].u32();
  while (i--) {
    // TODO - validate correctness
    // TODO - validate correctness
    uint32 val2 = *src++;
    uint32 res  = val2 - val;
    *dst++ = res & -(res <= val2);
  }
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Signed
_DEFINE_OP(VSSUBS_S8) {
  vm->status = VMDefs::BREAKPOINT;
  return;

//   // Super naive reference implementation
//   sint8   val = vm->gpr[(vArgs & 0xF000) >> 12].s8();
//   sint8*  src = vm->gpr[(vArgs & 0x0F00) >>  8].pS8();
//   sint8*  dst = vm->gpr[(vArgs & 0x00F0) >>  4].pS8();
//   uint32  i   = vm->gpr[(vArgs & 0x000F)].u32();
//   while (i--) {
//     // TODO - validate correctness
//
//   }
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(VSSUBS_S16) {
  vm->status = VMDefs::BREAKPOINT;
  return;

//   // Super naive reference implementation
//   sint16  val = vm->gpr[(vArgs & 0xF000) >> 12].s16();
//   sint16* src = vm->gpr[(vArgs & 0x0F00) >>  8].pS16();
//   sint16* dst = vm->gpr[(vArgs & 0x00F0) >>  4].pS16();
//   uint32  i   = vm->gpr[(vArgs & 0x000F)].u32();
//   while (i--) {
//     // TODO - validate correctness
//
//   }
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(VSSUBS_S32) {
  vm->status = VMDefs::BREAKPOINT;
  return;

//   // Super naive reference implementation
//   sint32  val = vm->gpr[(vArgs & 0xF000) >> 12].s32();
//   sint32* src = vm->gpr[(vArgs & 0x0F00) >>  8].pS32();
//   sint32* dst = vm->gpr[(vArgs & 0x00F0) >>  4].pS32();
//   uint32  i   = vm->gpr[(vArgs & 0x000F)].u32();
//   while (i--) {
//     // TODO - validate correctness
//
//   }
}
_END_OP

