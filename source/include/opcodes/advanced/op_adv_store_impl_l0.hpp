//****************************************************************************//
//**                                                                        **//
//** File:         op_adv_store_code.hpp                                    **//
//** Description:  Store group opcode implementation                        **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2001-08-29                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

_DEFINE_OP(ST_RII_8) {
  // st.8 rS, (rD,rI,#s)
  *(
      // Base address
      vm->gpr[(vArgs & 0x00F0) >> 4].pU8() + (
        // Index
        vm->gpr[(vArgs & 0x0F00) >> 8].s32()
        // Scale
        << ((vArgs & 0xF000) >> 12)
    )
  ) = vm->gpr[(vArgs & 0x000F)].u8();
}
_END_OP

_DEFINE_OP(ST_RII_16) {
  // st.16 rS, (rD,rI,#s)
  *((uint16*)(
      // Base address
      vm->gpr[(vArgs & 0x00F0) >> 4].pU8() + (
        // Index
        vm->gpr[(vArgs & 0x0F00) >> 8].s32()
        // Scale
        << ((vArgs & 0xF000) >> 12)
    )
  )) = vm->gpr[(vArgs & 0x000F)].u16();
}
_END_OP

_DEFINE_OP(ST_RII_32) {
  // st.32 rS, (rD,rI,#s)
  *((uint32*)(
      // Base address
      vm->gpr[(vArgs & 0x00F0) >> 4].pU8() + (
        // Index
        vm->gpr[(vArgs & 0x0F00) >> 8].s32()
        // Scale
        << ((vArgs & 0xF000) >> 12)
    )
  )) = vm->gpr[(vArgs & 0x000F)].u32();
}
_END_OP


