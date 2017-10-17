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
  vm->gpr[(vArgs & 0x000F)].f32() = (float32)std::log(
    (float64)vm->gpr[(vArgs & 0x00F0) >> 4].f32()
  );
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(LOG2_F32) {
  vm->gpr[(vArgs & 0x000F)].f32() = (float32)std::log(
    (float64)vm->gpr[(vArgs & 0x00F0) >> 4].f32()
  ) * predefinedConstants[VMDefs::CONST_INV_LN_2];
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(LOG10_F32) {
  vm->gpr[(vArgs & 0x000F)].f32() = (float32)std::log10(
    (float64)vm->gpr[(vArgs & 0x00F0) >> 4].f32()
  );
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(LOGX_F32) {
  vm->gpr[(vArgs & 0x000F)].f32() = (float32)std::log(
    (float64)vm->gpr[(vArgs & 0x00F0) >> 4].f32()
  ) / std::log((float64)vm->gpr[(vArgs & 0x0F00) >> 8].f32());
}
_END_OP

