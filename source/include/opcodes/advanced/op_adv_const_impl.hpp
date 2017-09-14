//****************************************************************************//
//**                                                                        **//
//** File:         op_adv_const_impl.hpp                                    **//
//** Description:  Load Constants                                           **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2017-08-19                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

_DEFINE_OP(LD_CONST_F32) {
  vm->gpr[(vArgs & 0x000F)].f32() = (float32)predefinedConstants[
    (vArgs & 0x000F) >> 4
  ];
}
_END_OP

_DEFINE_OP(LD_CONST_F64) {
  vm->gpr[(vArgs & 0x000F)].f64() = predefinedConstants[
    (vArgs & 0x000F) >> 4
  ];
}
_END_OP
