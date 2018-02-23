//****************************************************************************//
//**                                                                        **//
//** File:         op_adv_lerp_impl.hpp                                     **//
//** Description:  Interpolation                                            **//
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
  float32 lerp = vm->gpr[VARG1].f32();
  vm->gpr[VARG0].f32() =
    (lerp * vm->gpr[VARG3].f32()) +
    ((1.0f - lerp) * vm->gpr[VARG2].f32());
}
_END_OP

