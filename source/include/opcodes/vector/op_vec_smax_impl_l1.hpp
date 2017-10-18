//****************************************************************************//
//**                                                                        **//
//** File:         op_vec_smax.hpp                                          **//
//** Description:  Find maximum scalar in vector                            **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2017-08-15                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

// Floatng point
_DEFINE_OP(VSMAX_F32) {
  // Super naive reference implementation
  float32* src = vm->gpr[(vArgs & 0x00F0) >> 4].pF32();
  uint32   i   = vm->gpr[(vArgs & 0x000F)].u32();
  float32  val = *src;

  // Bail if we find max
  while (i--) {
    float32 val2 = *src++;
    if (val2 > val) {
      val = val2;
    }
  }
  vm->gpr[(vArgs & 0x0F00) >> 8].f32() = val;
}
_END_OP

