//****************************************************************************//
//**                                                                        **//
//** File:         op_arithmetic_code.hpp                                   **//
//** Description:  Arithmetic group opcode implementation                   **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2001-08-29                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

// ADDITION ////////////////////////////////////////////////////////////////////

_DEFINE_OP(ADD_F32) {
  // add.f32 rS,rD
  vm->gpr[_RD(op)].f32() += vm->gpr[_RS(op)].f32();
}
_END_OP

// SUBTRACTION /////////////////////////////////////////////////////////////////

_DEFINE_OP(SUB_F32) {
  // sub.f32 rS,rD
  vm->gpr[_RD(op)].f32() -= vm->gpr[_RS(op)].f32();
}
_END_OP

// MULTIPLICATION //////////////////////////////////////////////////////////////


_DEFINE_OP(MUL_F32) {
  // mul.f32 rS,rD
  vm->gpr[_RD(op)].f32() *= vm->gpr[_RS(op)].f32();
}
_END_OP

// DIVISION ////////////////////////////////////////////////////////////////////


_DEFINE_OP(DIV_F32) {
  // div.f32 rS,rD
  vm->gpr[_RD(op)].f32() /= vm->gpr[_RS(op)].f32();
}
_END_OP

// MODULUS /////////////////////////////////////////////////////////////////////

_DEFINE_OP(MOD_F32) {
  // mod.f32 rS,rD
  vm->gpr[_RD(op)].f32() = (float32) std::fmod((float64)vm->gpr[_RD(op)].f32(), (float64)vm->gpr[_RS(op)].f32());
}
_END_OP

// NEGATE //////////////////////////////////////////////////////////////////////

_DEFINE_OP(NEG_F32) {
  // neg.f32 rS,rD
  vm->gpr[_RD(op)].f32() = -(vm->gpr[_RS(op)].f32());
}
_END_OP

// MINIMUM /////////////////////////////////////////////////////////////////////

_DEFINE_OP(MIN_F32) {
  // min.f32 rS,rD
  float32 &d = vm->gpr[_RD(op)].f32();
  float32 s = vm->gpr[_RS(op)].f32();
  if (s < d) {
    d = s;
  }
}
_END_OP

// MAXIMUM /////////////////////////////////////////////////////////////////////

_DEFINE_OP(MAX_F32) {
  // max.f32 rS,rD
  float32 &d = vm->gpr[_RD(op)].f32();
  float32 s = vm->gpr[_RS(op)].f32();
  if (s > d) {
    d = s;
  }
}
_END_OP

