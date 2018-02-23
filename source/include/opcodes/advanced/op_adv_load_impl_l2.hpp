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
  vm->gpr[VARG0].u64() = *((uint64*)(
      // Base address
      vm->gpr[VARG1].pU8() + (
        // Index
        vm->gpr[VARG2].s32()
        // Scale
        << (VARG3)
    )
  ));
}
_END_OP

