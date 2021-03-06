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

_DEFINE_OP(ST_RII_64) {
  // st.64 rS, (rD,rI,#s)
  *((uint64*)(
      // Base address
      vm->gpr[VARG1].pU8() + (
        // Index
        vm->gpr[VARG2].s32()
        // Scale
        << (VARG3)
    )
  )) = vm->gpr[VARG0].u64();
}
_END_OP

