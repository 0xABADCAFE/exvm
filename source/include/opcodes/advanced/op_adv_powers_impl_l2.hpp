//****************************************************************************//
//**                                                                        **//
//** File:         op_adv_powers_impl.hpp                                   **//
//** Description:  Powers and exponentiation                                **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2017-08-19                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

_DEFINE_OP(EXP_F64) {
  vm->gpr[VARG0].f64() = std::exp(vm->gpr[VARG1].f64());
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(POW_F64) {
  vm->gpr[VARG0].f64() = std::pow(
    vm->gpr[VARG1].f64(),
    vm->gpr[VARG2].f64()
  );
}
_END_OP
