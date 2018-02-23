//****************************************************************************//
//**                                                                        **//
//** File:         op_adv_logs_impl.hpp                                     **//
//** Description:  Logarithmic functions                                    **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2017-08-19                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

_DEFINE_OP(LOGN_F32) {
  vm->gpr[VARG0].f32() = (float32)std::log(
    (float64)vm->gpr[VARG1].f32()
  );
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(LOG2_F32) {
  vm->gpr[VARG0].f32() = (float32)std::log(
    (float64)vm->gpr[VARG1].f32()
  ) * predefinedConstants[VMDefs::CONST_INV_LN_2];
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(LOG10_F32) {
  vm->gpr[VARG0].f32() = (float32)std::log10(
    (float64)vm->gpr[VARG1].f32()
  );
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(LOGX_F32) {
  vm->gpr[VARG0].f32() = (float32)std::log(
    (float64)vm->gpr[VARG1].f32()
  ) / std::log((float64)vm->gpr[VARG2].f32());
}
_END_OP

