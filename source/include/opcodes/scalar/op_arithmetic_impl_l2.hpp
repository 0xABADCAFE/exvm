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

_DEFINE_OP(ADD_I64) {
  // add.64 rS,rD
  vm->gpr[_RD(op)].s64() += vm->gpr[_RS(op)].s64();
}
_END_OP

_DEFINE_OP(ADD_F64) {
  // add.f64 rS,rD
  vm->gpr[_RD(op)].f64() += vm->gpr[_RS(op)].f64();
}
_END_OP

// SUBTRACTION /////////////////////////////////////////////////////////////////

_DEFINE_OP(SUB_I64) {
  // sub.64 rS,rD
  vm->gpr[_RD(op)].s64() -= vm->gpr[_RS(op)].s64();
}
_END_OP

_DEFINE_OP(SUB_F64) {
  // sub.f64 rS,rD
  vm->gpr[_RD(op)].s64() -= vm->gpr[_RS(op)].s64();
}
_END_OP

// MULTIPLICATION //////////////////////////////////////////////////////////////

_DEFINE_OP(MUL_U64) {
  // mul.u64 rS,rD
  vm->gpr[_RD(op)].u64() *= vm->gpr[_RS(op)].u64();
}
_END_OP

_DEFINE_OP(MUL_S64) {
  // mul.s64 rS,rD
  vm->gpr[_RD(op)].s64() *= vm->gpr[_RS(op)].s64();
}
_END_OP

_DEFINE_OP(MUL_F64) {
  // mul.f32 rS,rD
  vm->gpr[_RD(op)].f64() *= vm->gpr[_RS(op)].f64();
}
_END_OP

// DIVISION ////////////////////////////////////////////////////////////////////

_DEFINE_OP(DIV_U64) {
  // div.u64 rS,rD
  uint64 d = vm->gpr[_RS(op)].u64();
  if (!d) {
    vm->status = VMDefs::ZERO_DIVIDE;
    _HALT
  }
  vm->gpr[_RD(op)].u64() /= d;
}
_END_OP

_DEFINE_OP(DIV_S64) {
  // div.s64 rS,rD
  sint64 d = vm->gpr[_RS(op)].s64();
  if (!d) {
    vm->status = VMDefs::ZERO_DIVIDE;
    _HALT
  }
  vm->gpr[_RD(op)].s64() /= d;
}
_END_OP

_DEFINE_OP(DIV_F64) {
  // div.f32 rS,rD
  vm->gpr[_RD(op)].f64() /= vm->gpr[_RS(op)].f64();
}
_END_OP

// MODULUS /////////////////////////////////////////////////////////////////////

_DEFINE_OP(MOD_U64) {
  // mod.u64 rS,rD
  uint64 d = vm->gpr[_RS(op)].u64();
  if (!d) {
    vm->status = VMDefs::ZERO_DIVIDE;
    _HALT
  }
  vm->gpr[_RD(op)].u64() %= d;
}
_END_OP

_DEFINE_OP(MOD_S64) {
  // mod.s64 rS,rD
  sint64 d = vm->gpr[_RS(op)].s64();
  if (!d) {
    vm->status = VMDefs::ZERO_DIVIDE;
    _HALT
  }
  vm->gpr[_RD(op)].s64() %= d;
}
_END_OP

_DEFINE_OP(MOD_F64) {
  // mod.f64 rS,rD
  vm->gpr[_RD(op)].f64() = std::fmod(vm->gpr[_RD(op)].f64(), vm->gpr[_RS(op)].f64());
}
_END_OP

// NEGATE //////////////////////////////////////////////////////////////////////

_DEFINE_OP(NEG_S64) {
  // neg.s64 rS,rD
  vm->gpr[_RD(op)].s64() = -(vm->gpr[_RS(op)].s64());
}
_END_OP

_DEFINE_OP(NEG_F64) {
  // neg.s8 rS,rD
  vm->gpr[_RD(op)].f64() = -(vm->gpr[_RS(op)].f64());
}
_END_OP

// SHIFT RIGHT /////////////////////////////////////////////////////////////////

_DEFINE_OP(ASR_S64) {
  // asl.s64 rS,rD
  vm->gpr[_RD(op)].s64() >>= vm->gpr[_RS(op)].u8();
}
_END_OP

// MINIMUM /////////////////////////////////////////////////////////////////////

_DEFINE_OP(MIN_S64) {
  // min.s64 rS,rD
  sint64 &d = vm->gpr[_RD(op)].s64();
  sint64 s = vm->gpr[_RS(op)].s64();
  if (s < d) {
    d = s;
  }
}
_END_OP

_DEFINE_OP(MIN_F64) {
  // min.f64 rS,rD
  float64 &d = vm->gpr[_RD(op)].f64();
  float64 s = vm->gpr[_RS(op)].f64();
  if (s < d) {
    d = s;
  };
}
_END_OP

// MAXIMUM /////////////////////////////////////////////////////////////////////

_DEFINE_OP(MAX_S64) {
  // max.s64 rS,rD
  sint64 &d = vm->gpr[_RD(op)].s64();
  sint64 s = vm->gpr[_RS(op)].s64();
  if (s > d) {
    d = s;
  }
}
_END_OP

_DEFINE_OP(MAX_F64) {
  // max.f64 rS,rD
  float64 &d = vm->gpr[_RD(op)].f64();
  float64 s = vm->gpr[_RS(op)].f64();
  if (s>d) d = s;
}
_END_OP

