//****************************************************************************//
//**                                                                        **//
//** File:         op_adv_load_code.hpp                                     **//
//** Description:  Load group opcode implementation                         **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2001-08-29                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

_DEFINE_OP(LD_RII_64) {
  // ld.16 (rS,rI,#s),rD
  vm->gpr[(vArgs & 0x000F)].u64() = *((uint64*)(
      // Base address
      vm->gpr[(vArgs & 0x00F0) >> 4].pU8() + (
        // Index
        vm->gpr[(vArgs & 0x0F00) >> 8].s32()
        // Scale
        << ((vArgs & 0xF000) >> 12)
    )
  ));
}
_END_OP

