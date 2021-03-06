//****************************************************************************//
//**                                                                        **//
//** File:         op_adv_vec2_f64_impl.hpp                                 **//
//** Description:  Operations for vec2d                                     **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2017-08-19                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

// Splat fill a vec2d instance
_DEFINE_OP(SPLAT_V2F64) {
  const float64 src = vm->gpr[VARG1].f64();
  float64*      dst = vm->gpr[VARG0].pF64();
  dst[0] = src;
  dst[1] = src;
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Add two vec2d instances
_DEFINE_OP(COPY_V2F64) {
  const float64* src = vm->gpr[VARG1].pF64();
  float64*       dst = vm->gpr[VARG0].pF64();
  dst[0] = src[0];
  dst[1] = src[1];
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Add two vec2d instances
_DEFINE_OP(ADD_V2F64) {
  const float64* src1 = vm->gpr[VARG2].pF64();
  const float64* src2 = vm->gpr[VARG1].pF64();
  float64*       dst  = vm->gpr[VARG0].pF64();
  dst[0] = src1[0] + src2[0];
  dst[1] = src1[1] + src2[1];
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Subtract two vec2d instances
_DEFINE_OP(SUB_V2F64) {
  const float64* src1 = vm->gpr[VARG2].pF64();
  const float64* src2 = vm->gpr[VARG1].pF64();
  float64*       dst  = vm->gpr[VARG0].pF64();
  dst[0] = src1[0] - src2[0];
  dst[1] = src1[1] - src2[1];
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Compute the scalar (dot) product of two vec2d instances
_DEFINE_OP(DOT_V2F64) {
  const float64* src1 = vm->gpr[VARG2].pF64();
  const float64* src2 = vm->gpr[VARG1].pF64();
  vm->gpr[VARG0].f64() = src1[0] * src2[0] + src1[1] * src2[1];
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Multiply a vec2d instance by a scalar
_DEFINE_OP(SCALE_V2F64) {
  float64        fac = vm->gpr[VARG2].f64();
  const float64* src = vm->gpr[VARG1].pF64();
  float64*       dst = vm->gpr[VARG0].pF64();
  dst[0] = src[0] * fac;
  dst[1] = src[1] * fac;
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Compute the scalar magnitude of a vec2d instance
_DEFINE_OP(MAGN_V2F64) {
  const float64* src  = vm->gpr[VARG1].pF64();
  vm->gpr[VARG0].f64()  = sqrt(src[0] * src[0] + src[1] * src[1]);
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Normalise a vec2d instance
_DEFINE_OP(NORM_V2F64) {
  const float64* src  = vm->gpr[VARG1].pF64();
  float64*       dst  = vm->gpr[VARG0].pF64();
  float64        fac  = 1.0f / sqrt(src[0] * src[0] + src[1] * src[1]);
  dst[0] = fac * src[0];
  dst[1] = fac * src[1];
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Interpolate a point between two vectors. Values outside the range 0-1 are legal and project past
// the initial points along the line segnment between them.
_DEFINE_OP(LERP_V2F64) {
  const float64* src1 = vm->gpr[VARG3].pF64();
  const float64* src2 = vm->gpr[VARG2].pF64();
  float64        fac  = vm->gpr[VARG1].f64();
  float64*       dst  = vm->gpr[VARG0].pF64();
  dst[0] = src1[0] + (fac * (src2[0] - src1[0]));
  dst[1] = src1[1] + (fac * (src2[1] - src1[1]));
}
_END_OP

// Transform a set if vec2d by a 3x3 matrix. Note that the last matrix row is unused, whereas the last column
// will contain any translation step.

_DEFINE_OP(M3X3_V2F64) {
  const float64* src = vm->gpr[VARG3].pF64();
  const float64* mtx = vm->gpr[VARG2].pF64();
  float64*       dst = vm->gpr[VARG1].pF64();
  uint32         i   = vm->gpr[VARG0].u32();

  while (i--) {
    float64 x = *src++;
    float64 y = *src++;
    *dst++ = x*mtx[0] + y*mtx[1] + mtx[2];
    *dst++ = x*mtx[3] + y*mtx[4] + mtx[5];
  }
}
_END_OP

