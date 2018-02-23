//****************************************************************************//
//**                                                                        **//
//** File:         op_adv_vec2_f32_impl.hpp                                 **//
//** Description:  Operations for vec2f                                     **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2017-08-19                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

// Splat fill a vec2f instance
_DEFINE_OP(SPLAT_V2F32) {
  const float32 src = vm->gpr[(vArgs & 0x00F0) >> 4].f32();
  float32*      dst = vm->gpr[(vArgs & 0x000F)].pF32();
  dst[0] = src;
  dst[1] = src;
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Add two vec2f instances
_DEFINE_OP(COPY_V2F32) {
  const float32* src = vm->gpr[(vArgs & 0x00F0) >> 4].pF32();
  float32*       dst = vm->gpr[(vArgs & 0x000F)].pF32();
  dst[0] = src[0];
  dst[1] = src[1];
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Add two vec2f instances
_DEFINE_OP(ADD_V2F32) {
  const float32* src1 = vm->gpr[(vArgs & 0x0F00) >> 8].pF32();
  const float32* src2 = vm->gpr[(vArgs & 0x00F0) >> 4].pF32();
  float32*       dst  = vm->gpr[(vArgs & 0x000F)].pF32();
  dst[0] = src1[0] + src2[0];
  dst[1] = src1[1] + src2[1];
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Subtract two vec2f instances
_DEFINE_OP(SUB_V2F32) {
  const float32* src1 = vm->gpr[(vArgs & 0x0F00) >> 8].pF32();
  const float32* src2 = vm->gpr[(vArgs & 0x00F0) >> 4].pF32();
  float32*       dst  = vm->gpr[(vArgs & 0x000F)].pF32();
  dst[0] = src1[0] - src2[0];
  dst[1] = src1[1] - src2[1];
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Compute the scalar (dot) product of two vec2f instances
_DEFINE_OP(DOT_V2F32) {
  const float32* src1 = vm->gpr[(vArgs & 0x0F00) >> 8].pF32();
  const float32* src2 = vm->gpr[(vArgs & 0x00F0) >> 4].pF32();
  vm->gpr[(vArgs & 0x000F)].f32() = src1[0] * src2[0] + src1[1] * src2[1];
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Multiply a vec2f instance by a scalar
_DEFINE_OP(SCALE_V2F32) {
  float32        fac = vm->gpr[(vArgs & 0x0F00) >> 8].f32();
  const float32* src = vm->gpr[(vArgs & 0x00F0) >> 4].pF32();
  float32*       dst = vm->gpr[(vArgs & 0x000F)].pF32();
  dst[0] = src[0] * fac;
  dst[1] = src[1] * fac;
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Compute the scalar magnitude of a vec2f instance
_DEFINE_OP(MAGN_V2F32) {
  const float32* src  = vm->gpr[(vArgs & 0x00F0) >> 4].pF32();
  vm->gpr[(vArgs & 0x000F)].f32()  = sqrt(src[0] * src[0] + src[1] * src[1]);
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Normalise a vec2f instance
_DEFINE_OP(NORM_V2F32) {
  const float32* src  = vm->gpr[(vArgs & 0x00F0) >> 4].pF32();
  float32*       dst  = vm->gpr[(vArgs & 0x000F)].pF32();
  float32        fac  = 1.0f / sqrt(src[0] * src[0] + src[1] * src[1]);
  dst[0] = fac * src[0];
  dst[1] = fac * src[1];
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Interpolate a point between two vectors. Values outside the range 0-1 are legal and project past
// the initial points along the line segnment between them.
_DEFINE_OP(LERP_V2F32) {
  const float32* src1 = vm->gpr[(vArgs & 0xF000) >> 12].pF32();
  const float32* src2 = vm->gpr[(vArgs & 0x0F00) >> 8].pF32();
  float32        fac  = vm->gpr[(vArgs & 0x00F0) >> 4].f32();
  float32*       dst  = vm->gpr[(vArgs & 0x000F)].pF32();
  dst[0] = src1[0] + (fac * (src2[0] - src1[0]));
  dst[1] = src1[1] + (fac * (src2[1] - src1[1]));
}
_END_OP

// Transform a set if vec2f by a 3x3 matrix. Note that the last matrix row is unused, whereas the last column
// will contain any translation step.

//_xform_v2f32(s,m,d,n) _MKAOP(M3X3_V2F32),   (s) << 12 | (m) << 8 | (d) << 4 | (n),
_DEFINE_OP(M3X3_V2F32) {
  const float32* src = vm->gpr[(vArgs & 0xF000) >> 12].pF32();
  const float32* mtx = vm->gpr[(vArgs & 0x0F00) >> 8].pF32();
  float32*       dst = vm->gpr[(vArgs & 0x00F0) >> 4].pF32();
  uint32         i   = vm->gpr[(vArgs & 0x000F)].u32();

  while (i--) {
    float32 x = *src++;
    float32 y = *src++;
    *dst++ = x*mtx[0] + y*mtx[1] + mtx[2];
    *dst++ = x*mtx[3] + y*mtx[4] + mtx[5];
  }
}
_END_OP

