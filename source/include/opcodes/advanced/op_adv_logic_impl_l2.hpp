//****************************************************************************//
//**                                                                        **//
//** File:         op_adv_logic_impl.hpp                                    **//
//** Description:  Logic                                                    **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2017-08-19                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

_DEFINE_OP(LSLM_64) {
  uint64 val  = vm->gpr[VARG3].u64();
  uint64 mask = vm->gpr[VARG2].u64();
  uint64 val2 = ((val & mask) << vm->gpr[VARG1].u32()) & mask;
  vm->gpr[VARG0].u64() = val2 | (val & ~mask);
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(LSRM_64) {
  uint64 val  = vm->gpr[VARG3].u64();
  uint64 mask = vm->gpr[VARG2].u64();
  uint64 val2 = ((val & mask) >> vm->gpr[VARG1].u32()) & mask;
  vm->gpr[VARG0].u64() = val2 | (val & ~mask);
}
_END_OP

