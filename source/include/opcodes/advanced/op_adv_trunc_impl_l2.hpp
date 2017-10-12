//****************************************************************************//
//**                                                                        **//
//** File:         op_adv_trunc_impl.hpp                                    **//
//** Description:  Truncation and rounding                                  **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2017-08-19                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

_DEFINE_OP(CEIL_F64) {
  vm->gpr[(vArgs & 0x000F)].f64() = std::ceil(vm->gpr[(vArgs & 0x00F0) >> 4].f64());
}
_END_OP

_DEFINE_OP(FLOOR_F64) {
  vm->gpr[(vArgs & 0x000F)].f64() = std::floor(vm->gpr[(vArgs & 0x00F0) >> 4].f64());
}
_END_OP
