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


_DEFINE_OP(LERP_F32) {
  float32 lerp = vm->gpr[(vArgs & 0x00F0) >> 4].f32();
  vm->gpr[(vArgs & 0x000F)].f32() =
    (lerp * vm->gpr[(vArgs & 0xF000) >> 12].f32()) +
    ((1.0f - lerp) * vm->gpr[(vArgs & 0x0F00) >> 8].f32());
}
_END_OP


_DEFINE_OP(LERP_F64) {
  float64 lerp = vm->gpr[(vArgs & 0x00F0) >> 4].f64();
  vm->gpr[(vArgs & 0x000F)].f64() =
    (lerp * vm->gpr[(vArgs & 0xF000) >> 12].f64()) +
    ((1.0 - lerp) * vm->gpr[(vArgs & 0x0F00) >> 8].f64());
}
_END_OP
