//****************************************************************************//
//**                                                                        **//
//** File:         op_adv_trig_impl.hpp                                     **//
//** Description:  Trigonometric functions                                  **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2017-08-19                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

_DEFINE_OP(ACOS_F32) {
  vm->gpr[(vArgs & 0x000F)].f32() = (float32)std::acos(
    (float64)vm->gpr[(vArgs & 0x00F0) >> 4].f32()
  );
}
_END_OP


_DEFINE_OP(ACOS_F64) {
  vm->gpr[(vArgs & 0x000F)].f64() = std::acos(
     vm->gpr[(vArgs & 0x00F0) >> 4].f64()
  );
}
_END_OP


_DEFINE_OP(ASIN_F32) {
  vm->gpr[(vArgs & 0x000F)].f32() = (float32)std::asin(
    (float64)vm->gpr[(vArgs & 0x00F0) >> 4].f32()
  );
}
_END_OP


_DEFINE_OP(ASIN_F64) {
  vm->gpr[(vArgs & 0x000F)].f64() = std::asin(
     vm->gpr[(vArgs & 0x00F0) >> 4].f64()
  );
}
_END_OP


_DEFINE_OP(ATAN_F32) {
  vm->gpr[(vArgs & 0x000F)].f32() = (float32)std::atan(
    (float64)vm->gpr[(vArgs & 0x00F0) >> 4].f32()
  );
}
_END_OP


_DEFINE_OP(ATAN_F64) {
  vm->gpr[(vArgs & 0x000F)].f64() = std::atan(
     vm->gpr[(vArgs & 0x00F0) >> 4].f64()
  );
}
_END_OP


_DEFINE_OP(COS_F32) {
  vm->gpr[(vArgs & 0x000F)].f32() = (float32)std::cos(
    (float64)vm->gpr[(vArgs & 0x00F0) >> 4].f32()
  );
}
_END_OP


_DEFINE_OP(COS_F64) {
  vm->gpr[(vArgs & 0x000F)].f64() = std::cos(
     vm->gpr[(vArgs & 0x00F0) >> 4].f64()
  );
}
_END_OP


_DEFINE_OP(SIN_F32) {
  vm->gpr[(vArgs & 0x000F)].f32() = (float32)std::sin(
    (float64)vm->gpr[(vArgs & 0x00F0) >> 4].f32()
  );
}
_END_OP


_DEFINE_OP(SIN_F64) {
  vm->gpr[(vArgs & 0x000F)].f64() = std::sin(
     vm->gpr[(vArgs & 0x00F0) >> 4].f64()
  );
}
_END_OP


_DEFINE_OP(TAN_F32) {
  vm->gpr[(vArgs & 0x000F)].f32() = (float32)std::tan(
    (float64)vm->gpr[(vArgs & 0x00F0) >> 4].f32()
  );
}
_END_OP


_DEFINE_OP(TAN_F64) {
  vm->gpr[(vArgs & 0x000F)].f64() = std::tan(
     vm->gpr[(vArgs & 0x00F0) >> 4].f64()
  );
}
_END_OP


_DEFINE_OP(COSH_F32) {
  vm->gpr[(vArgs & 0x000F)].f32() = (float32)std::cosh(
    (float64)vm->gpr[(vArgs & 0x00F0) >> 4].f32()
  );
}
_END_OP


_DEFINE_OP(COSH_F64) {
  vm->gpr[(vArgs & 0x000F)].f64() = std::cosh(
     vm->gpr[(vArgs & 0x00F0) >> 4].f64()
  );
}
_END_OP


_DEFINE_OP(SINH_F32) {
  vm->gpr[(vArgs & 0x000F)].f32() = (float32)std::sinh(
    (float64)vm->gpr[(vArgs & 0x00F0) >> 4].f32()
  );
}
_END_OP


_DEFINE_OP(SINH_F64) {
  vm->gpr[(vArgs & 0x000F)].f64() = std::sinh(
     vm->gpr[(vArgs & 0x00F0) >> 4].f64()
  );
}
_END_OP


_DEFINE_OP(TANH_F32) {
  vm->gpr[(vArgs & 0x000F)].f32() = (float32)std::tanh(
    (float64)vm->gpr[(vArgs & 0x00F0) >> 4].f32()
  );
}
_END_OP


_DEFINE_OP(TANH_F64) {
  vm->gpr[(vArgs & 0x000F)].f64() = std::tanh(
     vm->gpr[(vArgs & 0x00F0) >> 4].f64()
  );
}
_END_OP


_DEFINE_OP(SINCOS_F32) {
  float64 val = (float64)vm->gpr[(vArgs & 0x0F00) >> 8].f32();
  vm->gpr[(vArgs & 0x000F)].f32()      = (float32)std::sin(val);
  vm->gpr[(vArgs & 0x00F0) >> 4].f32() = (float32)std::cos(val);
}
_END_OP


_DEFINE_OP(SINCOS_F64) {
  float64 val = vm->gpr[(vArgs & 0x0F00) >> 8].f64();
  vm->gpr[(vArgs & 0x000F)].f64()      = std::sin(val);
  vm->gpr[(vArgs & 0x00F0) >> 4].f64() = std::cos(val);
}
_END_OP
