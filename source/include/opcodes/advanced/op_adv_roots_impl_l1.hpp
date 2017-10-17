//****************************************************************************//
//**                                                                        **//
//** File:         op_adv_roots_impl.hpp                                    **//
//** Description:  Roots and inverse roots                                  **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2017-08-19                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

_DEFINE_OP(SQRT_F32) {
  vm->gpr[(vArgs & 0x000F)].f32() = (float32)std::sqrt(
    (float64)vm->gpr[(vArgs & 0x00F0) >> 4].f32()
  );
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(ISQRT_F32) {
  vm->gpr[(vArgs & 0x000F)].f32() = (float32)(
    1.0 / std::sqrt((float64)vm->gpr[(vArgs & 0x00F0) >> 4].f32())
  );
}
_END_OP

