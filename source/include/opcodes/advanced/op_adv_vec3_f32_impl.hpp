//****************************************************************************//
//**                                                                        **//
//** File:         op_adv_vec3_f32_impl.hpp                                 **//
//** Description:  Operations for vec3f                                     **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2017-08-19                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//


_DEFINE_OP(ADDV3_F32) {
  const float32* src1 = vm->gpr[(vArgs & 0x0F00) >> 8].pF32();
  const float32* src2 = vm->gpr[(vArgs & 0x00F0) >> 4].pF32();
  float32*       dst  = vm->gpr[(vArgs & 0x000F)].pF32();
  dst[0] = src1[0] + src2[0];
  dst[1] = src1[1] + src2[1];
  dst[2] = src1[2] + src2[2];
}
_END_OP

_DEFINE_OP(SUBV3_F32) {
  const float32* src1 = vm->gpr[(vArgs & 0x0F00) >> 8].pF32();
  const float32* src2 = vm->gpr[(vArgs & 0x00F0) >> 4].pF32();
  float32*       dst  = vm->gpr[(vArgs & 0x000F)].pF32();
  dst[0] = src1[0] - src2[0];
  dst[1] = src1[1] - src2[1];
  dst[2] = src1[2] - src2[2];
}
_END_OP

_DEFINE_OP(CRSV3_F32) {
  const float32* src1 = vm->gpr[(vArgs & 0x0F00) >> 8].pF32();
  const float32* src2 = vm->gpr[(vArgs & 0x00F0) >> 4].pF32();
  float32*       dst  = vm->gpr[(vArgs & 0x000F)].pF32();

  // x =  v1.y * v2.z - v1.z * v2.y,
  // y =  v1.z * v2.x - v1.x * v2.z,
  // z =  v1.x * v2.y - v1.y * v2.x
  dst[0] = src1[1] * src2[3] - src1[2] * src2[1];
  dst[1] = src1[2] * src2[0] - src1[0] * src2[3];
  dst[2] = src1[0] * src2[1] - src1[1] * src2[0];
}
_END_OP

_DEFINE_OP(DOTV3_F32) {
  const float32* src1 = vm->gpr[(vArgs & 0x0F00) >> 8].pF32();
  const float32* src2 = vm->gpr[(vArgs & 0x00F0) >> 4].pF32();
  vm->gpr[(vArgs & 0x000F)].f32() = src1[0] * src2[0] + src1[1] * src2[1] + src1[2] * src2[2];
}
_END_OP

_DEFINE_OP(NRMV3_F32) {
  const float32* src  = vm->gpr[(vArgs & 0x00F0) >> 4].pF32();
  float32*       dst  = vm->gpr[(vArgs & 0x000F)].pF32();
  float32        fac  = 1.0f / sqrt(src[0] * src[0] + src[1] * src[1] + src[2] * src[2]);
  dst[0] = fac * src[0];
  dst[1] = fac * src[1];
  dst[2] = fac * src[2];
}
_END_OP

