//****************************************************************************//
//**                                                                        **//
//** File:         op_adv_vec3_f64_impl.hpp                                 **//
//** Description:  Operations for vec3d                                     **//
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
_DEFINE_OP(SPLAT_V3F64) {
  const float64 src = vm->gpr[(vArgs & 0x00F0) >> 4].f64();
  float64*      dst = vm->gpr[(vArgs & 0x000F)].pF64();
  dst[0] = src;
  dst[1] = src;
  dst[2] = src;
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Add two vec3f instances
_DEFINE_OP(COPY_V3F64) {
  const float64* src = vm->gpr[(vArgs & 0x00F0) >> 4].pF64();
  float64*       dst = vm->gpr[(vArgs & 0x000F)].pF64();
  dst[0] = src[0];
  dst[1] = src[1];
  dst[2] = src[2];
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Add two vec3f instances
_DEFINE_OP(ADD_V3F64) {
  const float64* src1 = vm->gpr[(vArgs & 0x0F00) >> 8].pF64();
  const float64* src2 = vm->gpr[(vArgs & 0x00F0) >> 4].pF64();
  float64*       dst  = vm->gpr[(vArgs & 0x000F)].pF64();
  dst[0] = src1[0] + src2[0];
  dst[1] = src1[1] + src2[1];
  dst[2] = src1[2] + src2[2];
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Subtract two vec3f instances
_DEFINE_OP(SUB_V3F64) {
  const float64* src1 = vm->gpr[(vArgs & 0x0F00) >> 8].pF64();
  const float64* src2 = vm->gpr[(vArgs & 0x00F0) >> 4].pF64();
  float64*       dst  = vm->gpr[(vArgs & 0x000F)].pF64();
  dst[0] = src1[0] - src2[0];
  dst[1] = src1[1] - src2[1];
  dst[2] = src1[2] - src2[2];
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Conpute the cross product of two vec3 instances
_DEFINE_OP(CROSS_V3F64) {
  const float64* src1 = vm->gpr[(vArgs & 0x0F00) >> 8].pF64();
  const float64* src2 = vm->gpr[(vArgs & 0x00F0) >> 4].pF64();
  float64*       dst  = vm->gpr[(vArgs & 0x000F)].pF64();

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
_DEFINE_OP(DOT_V3F64) {
  const float64* src1 = vm->gpr[(vArgs & 0x0F00) >> 8].pF64();
  const float64* src2 = vm->gpr[(vArgs & 0x00F0) >> 4].pF64();
  vm->gpr[(vArgs & 0x000F)].f64() = src1[0] * src2[0] + src1[1] * src2[1] + src1[2] * src2[2];
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Multiply a vec3f instance by a scalar
_DEFINE_OP(SCALE_V3F64) {
  float64        fac = vm->gpr[(vArgs & 0x0F00) >> 8].f64();
  const float64* src = vm->gpr[(vArgs & 0x00F0) >> 4].pF64();
  float64*       dst = vm->gpr[(vArgs & 0x000F)].pF64();
  dst[0] = src[0] * fac;
  dst[1] = src[1] * fac;
  dst[2] = src[2] * fac;
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Compute the scalar magnitude of a vec3f instance
_DEFINE_OP(MAGN_V3F64) {
  const float64* src  = vm->gpr[(vArgs & 0x00F0) >> 4].pF64();
  vm->gpr[(vArgs & 0x000F)].f64()  = sqrt(src[0] * src[0] + src[1] * src[1] + src[2] * src[2]);
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Normalise a vec3f instance
_DEFINE_OP(NORM_V3F64) {
  const float64* src  = vm->gpr[(vArgs & 0x00F0) >> 4].pF64();
  float64*       dst  = vm->gpr[(vArgs & 0x000F)].pF64();
  float64        fac  = 1.0f / sqrt(src[0] * src[0] + src[1] * src[1] + src[2] * src[2]);
  dst[0] = fac * src[0];
  dst[1] = fac * src[1];
  dst[2] = fac * src[2];
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Interpolate a point between two vectors. Values outside the range 0-1 are legal and project past
// the initial points along the line segnment between them.
_DEFINE_OP(LERP_V3F64) {
  const float64* src1 = vm->gpr[(vArgs & 0xF000) >> 12].pF64();
  const float64* src2 = vm->gpr[(vArgs & 0x0F00) >> 8].pF64();
  float64        fac  = vm->gpr[(vArgs & 0x00F0) >> 4].f64();
  float64*       dst  = vm->gpr[(vArgs & 0x000F)].pF64();
  dst[0] = src1[0] + (fac * (src2[0] - src1[0]));
  dst[1] = src1[1] + (fac * (src2[1] - src1[1]));
  dst[2] = src1[2] + (fac * (src2[2] - src1[2]));
}
_END_OP

// Transform a set if vec3f by a 4x4 matrix. Note that the last matrix row is unused, whereas the last column
// will contain any translation step.

_DEFINE_OP(M4X4_V3F64) {

}
_END_OP
