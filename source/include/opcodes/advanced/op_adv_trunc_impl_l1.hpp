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


_DEFINE_OP(CEIL_F32) {
  vm->gpr[(vArgs & 0x000F)].f32() = (float32)std::ceil(
    (float64)vm->gpr[(vArgs & 0x00F0) >> 4].f32()
  );
}
_END_OP

_DEFINE_OP(FLOOR_F32) {
  vm->gpr[(vArgs & 0x000F)].f32() = (float32)std::floor((float64)vm->gpr[(vArgs & 0x00F0) >> 4].f32());
}
_END_OP

