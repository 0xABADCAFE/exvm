//****************************************************************************//
//**                                                                        **//
//** File:         op_vec_sdiv_saturated_impl.hpp                           **//
//** Description:  Scalar on Vector Division                                **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2017-08-15                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

_DEFINE_OP(VSDIVS_S64) {
  vm->status = VMDefs::BREAKPOINT;
  return;
//   // Super naive reference implementation
//   sint64  val = vm->gpr[VARG3].s64();
//   if (!val) {
//     vm->status = VMDefs::ZERO_DIVIDE;
//     return;
//   }
//   sint64* src = vm->gpr[VARG2].pS64();
//   sint64* dst = vm->gpr[VARG1].pS64();
//   uint32  i   = vm->gpr[VARG0].u32();
//   while (i--) {
//     *dst++ = *src++ / val;
//   }
}
_END_OP

