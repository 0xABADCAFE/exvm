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

// Splat fill a vec3f instance
_DEFINE_OP(SPLAT_V3F32) {
  const float32 src = vm->gpr[(vArgs & 0x00F0) >> 4].f32();
  float32*      dst = vm->gpr[(vArgs & 0x000F)].pF32();
  dst[0] = src;
  dst[1] = src;
  dst[2] = src;
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Add two vec3f instances
_DEFINE_OP(COPY_V3F32) {
  const float32* src = vm->gpr[(vArgs & 0x00F0) >> 4].pF32();
  float32*       dst = vm->gpr[(vArgs & 0x000F)].pF32();
  dst[0] = src[0];
  dst[1] = src[1];
  dst[2] = src[2];
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Add two vec3f instances
_DEFINE_OP(ADD_V3F32) {
  const float32* src1 = vm->gpr[(vArgs & 0x0F00) >> 8].pF32();
  const float32* src2 = vm->gpr[(vArgs & 0x00F0) >> 4].pF32();
  float32*       dst  = vm->gpr[(vArgs & 0x000F)].pF32();
  dst[0] = src1[0] + src2[0];
  dst[1] = src1[1] + src2[1];
  dst[2] = src1[2] + src2[2];
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Subtract two vec3f instances
_DEFINE_OP(SUB_V3F32) {
  const float32* src1 = vm->gpr[(vArgs & 0x0F00) >> 8].pF32();
  const float32* src2 = vm->gpr[(vArgs & 0x00F0) >> 4].pF32();
  float32*       dst  = vm->gpr[(vArgs & 0x000F)].pF32();
  dst[0] = src1[0] - src2[0];
  dst[1] = src1[1] - src2[1];
  dst[2] = src1[2] - src2[2];
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Conpute the cross product of two vec3 instances
_DEFINE_OP(CROSS_V3F32) {
  const float32* src1 = vm->gpr[(vArgs & 0x0F00) >> 8].pF32();
  const float32* src2 = vm->gpr[(vArgs & 0x00F0) >> 4].pF32();
  float32*       dst  = vm->gpr[(vArgs & 0x000F)].pF32();

  // x =  v1.y * v2.z - v1.z * v2.y,
  // y =  v1.z * v2.x - v1.x * v2.z,
  // z =  v1.x * v2.y - v1.y * v2.x
  dst[0] = src1[1] * src2[2] - src1[2] * src2[1];
  dst[1] = src1[2] * src2[0] - src1[0] * src2[2];
  dst[2] = src1[0] * src2[1] - src1[1] * src2[0];
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Compute the scalar (dot) product of two vec3f instances
_DEFINE_OP(DOT_V3F32) {
  const float32* src1 = vm->gpr[(vArgs & 0x0F00) >> 8].pF32();
  const float32* src2 = vm->gpr[(vArgs & 0x00F0) >> 4].pF32();
  vm->gpr[(vArgs & 0x000F)].f32() = src1[0] * src2[0] + src1[1] * src2[1] + src1[2] * src2[2];
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Multiply a vec3f instance by a scalar
_DEFINE_OP(SCALE_V3F32) {
  float32        fac = vm->gpr[(vArgs & 0x0F00) >> 8].f32();
  const float32* src = vm->gpr[(vArgs & 0x00F0) >> 4].pF32();
  float32*       dst = vm->gpr[(vArgs & 0x000F)].pF32();
  dst[0] = src[0] * fac;
  dst[1] = src[1] * fac;
  dst[2] = src[2] * fac;
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Compute the scalar magnitude of a vec3f instance
_DEFINE_OP(MAGN_V3F32) {
  const float32* src  = vm->gpr[(vArgs & 0x00F0) >> 4].pF32();
  vm->gpr[(vArgs & 0x000F)].f32()  = sqrt(src[0] * src[0] + src[1] * src[1] + src[2] * src[2]);
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Normalise a vec3f instance
_DEFINE_OP(NORM_V3F32) {
  const float32* src  = vm->gpr[(vArgs & 0x00F0) >> 4].pF32();
  float32*       dst  = vm->gpr[(vArgs & 0x000F)].pF32();
  float32        fac  = 1.0f / sqrt(src[0] * src[0] + src[1] * src[1] + src[2] * src[2]);
  dst[0] = fac * src[0];
  dst[1] = fac * src[1];
  dst[2] = fac * src[2];
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Interpolate a point between two vectors. Values outside the range 0-1 are legal and project past
// the initial points along the line segnment between them.
_DEFINE_OP(LERP_V3F32) {
  const float32* src1 = vm->gpr[(vArgs & 0xF000) >> 12].pF32();
  const float32* src2 = vm->gpr[(vArgs & 0x0F00) >> 8].pF32();
  float32        fac  = vm->gpr[(vArgs & 0x00F0) >> 4].f32();
  float32*       dst  = vm->gpr[(vArgs & 0x000F)].pF32();
  dst[0] = src1[0] + (fac * (src2[0] - src1[0]));
  dst[1] = src1[1] + (fac * (src2[1] - src1[1]));
  dst[2] = src1[2] + (fac * (src2[2] - src1[2]));
}
_END_OP

// Transform a set if vec3f by a 4x4 matrix. Note that the last matrix row is unused, whereas the last column
// will contain any translation step.

_DEFINE_OP(M4X4_V3F32) {
  const float32* src = vm->gpr[(vArgs & 0xF000) >> 12].pF32();
  const float32* mtx = vm->gpr[(vArgs & 0x0F00) >> 8].pF32();
  float32*       dst = vm->gpr[(vArgs & 0x00F0) >> 4].pF32();
  uint32         i   = vm->gpr[(vArgs & 0x000F)].u32();

  while (i--) {

  }
}
_END_OP

