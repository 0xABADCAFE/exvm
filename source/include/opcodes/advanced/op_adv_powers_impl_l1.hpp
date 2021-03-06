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

_DEFINE_OP(EXP_F32) {
  vm->gpr[VARG0].f32() = (float32)std::exp(
    (float64)vm->gpr[VARG1].f32()
  );
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(POW_F32) {
  vm->gpr[VARG0].f32() = (float32)(
    std::pow(
      (float64)vm->gpr[VARG1].f32(),
      (float64)vm->gpr[VARG2].f32()
    )
  );
}
_END_OP

