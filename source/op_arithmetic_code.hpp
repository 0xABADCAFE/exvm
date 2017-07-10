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

_DEFINE_OP(ADD_I8) {
  // add.8 rS,rD
  vm->gpr[_RD(op)].s8() += vm->gpr[_RS(op)].s8();
}
_END_OP

_DEFINE_OP(ADD_I16) {
  // add.16 rS,rD
  vm->gpr[_RD(op)].s16() += vm->gpr[_RS(op)].s16();
}
_END_OP

_DEFINE_OP(ADD_I32) {
  // add.32 rS,rD
  vm->gpr[_RD(op)].s32() += vm->gpr[_RS(op)].s32();
}
_END_OP

_DEFINE_OP(ADD_I64) {
  // add.64 rS,rD
  vm->gpr[_RD(op)].s64() += vm->gpr[_RS(op)].s64();
}
_END_OP

_DEFINE_OP(ADD_F32) {
  // add.f32 rS,rD
  vm->gpr[_RD(op)].f32() += vm->gpr[_RS(op)].f32();
}
_END_OP

_DEFINE_OP(ADD_F64) {
  // add.f64 rS,rD
  vm->gpr[_RD(op)].f64() += vm->gpr[_RS(op)].f64();
}
_END_OP

_DEFINE_OP(ADDI_I8) {
  // addi.8 #n, rX
  // #n is in the lower 8 bits of the extension word
  vm->gpr[_RD(op)].s8() += _EX_U16 & 0xFF;
}
_END_OP

_DEFINE_OP(ADDI_I16) {
  // addi.16 #n, rX
  // #n is in the extension word
  vm->gpr[_RD(op)].s16() += _EX_S16;
}
_END_OP

_DEFINE_OP(ADDI_I32) {
  // addi.32 #n, rX
  // #n is in the extension words
  vm->gpr[_RD(op)].s32() += _EX_S32;
}
_END_OP

// SUBTRACTION /////////////////////////////////////////////////////////////////

_DEFINE_OP(SUB_I8) {
  // sub.8 rS,rD
  vm->gpr[_RD(op)].s8() -= vm->gpr[_RS(op)].s8();
}
_END_OP

_DEFINE_OP(SUB_I16) {
  // sub.16 rS,rD
  vm->gpr[_RD(op)].s16() -= vm->gpr[_RS(op)].s16();
}
_END_OP

_DEFINE_OP(SUB_I32) {
  // sub.32 rS,rD
  vm->gpr[_RD(op)].s32() -= vm->gpr[_RS(op)].s32();
}
_END_OP

_DEFINE_OP(SUB_I64) {
  // sub.64 rS,rD
  vm->gpr[_RD(op)].s64() -= vm->gpr[_RS(op)].s64();
}
_END_OP

_DEFINE_OP(SUB_F32) {
  // sub.f32 rS,rD
  vm->gpr[_RD(op)].f32() -= vm->gpr[_RS(op)].f32();
}
_END_OP

_DEFINE_OP(SUB_F64) {
  // sub.f64 rS,rD
  vm->gpr[_RD(op)].s64() -= vm->gpr[_RS(op)].s64();
}
_END_OP

// MULTIPLICATION //////////////////////////////////////////////////////////////

_DEFINE_OP(MUL_U8) {
  // mul.u8 rS,rD : 16-bit product
  GPR* d = &vm->gpr[_RD(op)];
  d->u16() = (uint16)d->u8() * (uint16)vm->gpr[_RS(op)].u8();
}
_END_OP

_DEFINE_OP(MUL_U16) {
  // mul.u16 rS,rD : 32-bit product
  GPR* d = &vm->gpr[_RD(op)];
  d->u32() = (uint32)d->u16() * (uint32)vm->gpr[_RS(op)].u16();
}
_END_OP

_DEFINE_OP(MUL_U32) {
  // mul.u32 rS,rD : 64-bit product
  GPR* d = &vm->gpr[_RD(op)];
  d->u64() = (uint64)d->u32() * (uint64)vm->gpr[_RS(op)].u32();
}
_END_OP

_DEFINE_OP(MUL_U64) {
  // mul.u64 rS,rD
  vm->gpr[_RD(op)].u64() *= vm->gpr[_RS(op)].u64();
}
_END_OP

_DEFINE_OP(MUL_S8) {
  // mul.s8 rS,rD : 16-bit product
  GPR* d = &vm->gpr[_RD(op)];
  d->s16() = (sint16)d->s8() * (sint16)vm->gpr[_RS(op)].s8();
}
_END_OP

_DEFINE_OP(MUL_S16) {
  // mul.s16 rS,rD : 32-bit product
  GPR* d = &vm->gpr[_RD(op)];
  d->s32() = (sint32)d->s16() * (sint32)vm->gpr[_RS(op)].s16();
}
_END_OP

_DEFINE_OP(MUL_S32) {
  // mul.s8 rS,rD : 64-bit product
  GPR* d = &vm->gpr[_RD(op)];
  d->s64() = (sint64)d->s32() * (sint64)vm->gpr[_RS(op)].s32();
}
_END_OP

_DEFINE_OP(MUL_S64) {
  // mul.s64 rS,rD
  vm->gpr[_RD(op)].s64() *= vm->gpr[_RS(op)].s64();
}
_END_OP

_DEFINE_OP(MUL_F32) {
  // mul.f32 rS,rD
  vm->gpr[_RD(op)].f32() *= vm->gpr[_RS(op)].f32();
}
_END_OP

_DEFINE_OP(MUL_F64) {
  // mul.f32 rS,rD
  vm->gpr[_RD(op)].f64() *= vm->gpr[_RS(op)].f64();
}
_END_OP

// DIVISION ////////////////////////////////////////////////////////////////////

_DEFINE_OP(DIV_U8) {
  // div.u8 rS,rD
  uint8 d = vm->gpr[_RS(op)].u8();
  if (!d) {
    vm->status = VMDefs::ZERO_DIVIDE;
    _THROW(-1)
  }
  vm->gpr[_RD(op)].u8() /= d;
}
_END_OP

_DEFINE_OP(DIV_U16) {
  // div.u16 rS,rD
  uint16 d = vm->gpr[_RS(op)].u16();
  if (!d) {
    vm->status = VMDefs::ZERO_DIVIDE;
    _THROW(-1)
  }
  vm->gpr[_RD(op)].u16() /= d;
}
_END_OP

_DEFINE_OP(DIV_U32) {
  // div.u32 rS,rD
  uint32 d = vm->gpr[_RS(op)].u32();
  if (!d) {
    vm->status = VMDefs::ZERO_DIVIDE;
    _THROW(-1)
  }
  vm->gpr[_RD(op)].u32() /= d;
}
_END_OP

_DEFINE_OP(DIV_U64) {
  // div.u64 rS,rD
  uint64 d = vm->gpr[_RS(op)].u64();
  if (!d) {
    vm->status = VMDefs::ZERO_DIVIDE;
    _THROW(-1)
  }
  vm->gpr[_RD(op)].u64() /= d;
}
_END_OP

_DEFINE_OP(DIV_S8) {
  // div.s8 rS,rD
  sint8 d = vm->gpr[_RS(op)].s8();
  if (!d) {
    vm->status = VMDefs::ZERO_DIVIDE;
    _THROW(-1)
  }
  vm->gpr[_RD(op)].s8() /= d;
}
_END_OP

_DEFINE_OP(DIV_S16) {
  // div.s16 rS,rD
  sint8 d = vm->gpr[_RS(op)].s16();
  if (!d) {
    vm->status = VMDefs::ZERO_DIVIDE;
    _THROW(-1)
  }
  vm->gpr[_RD(op)].s16() /= d;
}
_END_OP

_DEFINE_OP(DIV_S32) {
  // div.s32 rS,rD
  sint8 d = vm->gpr[_RS(op)].s32();
  if (!d) {
    vm->status = VMDefs::ZERO_DIVIDE;
    _THROW(-1)
  }
  vm->gpr[_RD(op)].s32() /= d;
}
_END_OP

_DEFINE_OP(DIV_S64) {
  // div.s64 rS,rD
  sint64 d = vm->gpr[_RS(op)].s64();
  if (!d) {
    vm->status = VMDefs::ZERO_DIVIDE;
    _THROW(-1)
  }
  vm->gpr[_RD(op)].s64() /= d;
}
_END_OP

_DEFINE_OP(DIV_F32) {
  // div.f32 rS,rD
  vm->gpr[_RD(op)].f32() /= vm->gpr[_RS(op)].f32();
}
_END_OP

_DEFINE_OP(DIV_F64) {
  // div.f32 rS,rD
  vm->gpr[_RD(op)].f64() /= vm->gpr[_RS(op)].f64();
}
_END_OP

// MODULUS /////////////////////////////////////////////////////////////////////

_DEFINE_OP(MOD_U8) {
  // mod.u8 rS,rD
  uint8 d = vm->gpr[_RS(op)].u8();
  if (!d) {
    vm->status = VMDefs::ZERO_DIVIDE;
    _THROW(-1)
  }
  vm->gpr[_RD(op)].u8() %= d;
}
_END_OP

_DEFINE_OP(MOD_U16) {
  // mod.u16 rS,rD
  uint16 d = vm->gpr[_RS(op)].u16();
  if (!d) {
    vm->status = VMDefs::ZERO_DIVIDE;
    _THROW(-1)
  }
  vm->gpr[_RD(op)].u16() %= d;
}
_END_OP

_DEFINE_OP(MOD_U32) {
  // mod.u32 rS,rD
  uint32 d = vm->gpr[_RS(op)].u32();
  if (!d) {
    vm->status = VMDefs::ZERO_DIVIDE;
    _THROW(-1)
  }
  vm->gpr[_RD(op)].u32() %= d;
}
_END_OP

_DEFINE_OP(MOD_U64) {
  // mod.u64 rS,rD
  uint64 d = vm->gpr[_RS(op)].u64();
  if (!d) {
    vm->status = VMDefs::ZERO_DIVIDE;
    _THROW(-1)
  }
  vm->gpr[_RD(op)].u64() %= d;
}
_END_OP

_DEFINE_OP(MOD_S8) {
  // mod.s8 rS,rD
  sint8 d = vm->gpr[_RS(op)].s8();
  if (!d) {
    vm->status = VMDefs::ZERO_DIVIDE;
    _THROW(-1)
  }
  vm->gpr[_RD(op)].s8() %= d;
}
_END_OP

_DEFINE_OP(MOD_S16) {
  // mod.s16 rS,rD
  sint16 d = vm->gpr[_RS(op)].s16();
  if (!d) {
    vm->status = VMDefs::ZERO_DIVIDE;
    _THROW(-1)
  }
  vm->gpr[_RD(op)].s16() %= d;
}
_END_OP

_DEFINE_OP(MOD_S32) {
  // mod.s32 rS,rD
  sint32 d = vm->gpr[_RS(op)].s32();
  if (!d) {
    vm->status = VMDefs::ZERO_DIVIDE;
    _THROW(-1)
  }
  vm->gpr[_RD(op)].s32() %= d;
}
_END_OP

_DEFINE_OP(MOD_S64) {
  // mod.s64 rS,rD
  sint64 d = vm->gpr[_RS(op)].s64();
  if (!d) {
    vm->status = VMDefs::ZERO_DIVIDE;
    _THROW(-1)
  }
  vm->gpr[_RD(op)].s64() %= d;
}
_END_OP

_DEFINE_OP(MOD_F32) {
  // mod.f32 rS,rD
  vm->gpr[_RD(op)].f32() = (float32) std::fmod((float64)vm->gpr[_RD(op)].f32(), (float64)vm->gpr[_RS(op)].f32());
}
_END_OP

_DEFINE_OP(MOD_F64) {
  // mod.f64 rS,rD
  vm->gpr[_RD(op)].f64() = std::fmod(vm->gpr[_RD(op)].f64(), vm->gpr[_RS(op)].f64());
}
_END_OP

// NEGATE //////////////////////////////////////////////////////////////////////

_DEFINE_OP(NEG_S8) {
  // neg.s8 rS,rD
  vm->gpr[_RD(op)].s8() = -(vm->gpr[_RS(op)].s8());
}
_END_OP

_DEFINE_OP(NEG_S16) {
  // neg.s16 rS,rD
  vm->gpr[_RD(op)].s16() = -(vm->gpr[_RS(op)].s16());
}
_END_OP

_DEFINE_OP(NEG_S32) {
  // neg.s32 rS,rD
  vm->gpr[_RD(op)].s32() = -(vm->gpr[_RS(op)].s32());
}
_END_OP

_DEFINE_OP(NEG_S64) {
  // neg.s64 rS,rD
  vm->gpr[_RD(op)].s64() = -(vm->gpr[_RS(op)].s64());
}
_END_OP

_DEFINE_OP(NEG_F32) {
  // neg.f32 rS,rD
  vm->gpr[_RD(op)].f32() = -(vm->gpr[_RS(op)].f32());
}
_END_OP

_DEFINE_OP(NEG_F64) {
  // neg.s8 rS,rD
  vm->gpr[_RD(op)].f64() = -(vm->gpr[_RS(op)].f64());
}
_END_OP

// SHIFT LEFT //////////////////////////////////////////////////////////////////
/*
_DEFINE_OP(ASL_S8) {
  // asl.s8 rS,rD
  vm->gpr[_RD(op)].s8() <<= vm->gpr[_RS(op)].u8();
}
_END_OP

_DEFINE_OP(ASL_S16) {
  // asl.s16 rS,rD
  vm->gpr[_RD(op)].s16() <<= vm->gpr[_RS(op)].u8();
}
_END_OP

_DEFINE_OP(ASL_S32) {
  // asl.s32 rS,rD
  vm->gpr[_RD(op)].s32() <<= vm->gpr[_RS(op)].u8();
}
_END_OP

_DEFINE_OP(ASL_S64) {
  // asl.s64 rS,rD
  vm->gpr[_RD(op)].s64() <<= vm->gpr[_RS(op)].u8();
}
_END_OP
*/
// SHIFT RIGHT /////////////////////////////////////////////////////////////////

_DEFINE_OP(ASR_S8) {
  // asl.s8 rS,rD
  vm->gpr[_RD(op)].s8() >>= vm->gpr[_RS(op)].u8();
}
_END_OP

_DEFINE_OP(ASR_S16) {
  // asl.s16 rS,rD
  vm->gpr[_RD(op)].s16() >>= vm->gpr[_RS(op)].u8();
}
_END_OP

_DEFINE_OP(ASR_S32) {
  // asl.s32 rS,rD
  vm->gpr[_RD(op)].s32() >>= vm->gpr[_RS(op)].u8();
}
_END_OP

_DEFINE_OP(ASR_S64) {
  // asl.s64 rS,rD
  vm->gpr[_RD(op)].s64() >>= vm->gpr[_RS(op)].u8();
}
_END_OP

// MINIMUM /////////////////////////////////////////////////////////////////////

_DEFINE_OP(MIN_S8) {
  // min.s8 rS,rD
  sint8 &d = vm->gpr[_RD(op)].s8();
  sint8 s = vm->gpr[_RS(op)].s8();
  if (s < d) {
    d = s;
  }
}
_END_OP

_DEFINE_OP(MIN_S16) {
  // min.s16 rS,rD
  sint16 &d = vm->gpr[_RD(op)].s16();
  sint16 s = vm->gpr[_RS(op)].s16();
  if (s < d) {
    d = s;
  }
}
_END_OP

_DEFINE_OP(MIN_S32) {
  // min.s32 rS,rD
  sint32 &d = vm->gpr[_RD(op)].s32();
  sint32 s = vm->gpr[_RS(op)].s32();
  if (s<d) d = s;
}
_END_OP

_DEFINE_OP(MIN_S64) {
  // min.s64 rS,rD
  sint64 &d = vm->gpr[_RD(op)].s64();
  sint64 s = vm->gpr[_RS(op)].s64();
  if (s < d) {
    d = s;
  }
}
_END_OP

_DEFINE_OP(MIN_F32) {
  // min.f32 rS,rD
  float32 &d = vm->gpr[_RD(op)].f32();
  float32 s = vm->gpr[_RS(op)].f32();
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

_DEFINE_OP(MAX_S8) {
  // max.s8 rS,rD
  sint8 &d = vm->gpr[_RD(op)].s8();
  sint8 s = vm->gpr[_RS(op)].s8();
  if (s > d) {
    d = s;
  }
}
_END_OP

_DEFINE_OP(MAX_S16) {
  // max.s16 rS,rD
  sint16 &d = vm->gpr[_RD(op)].s16();
  sint16 s = vm->gpr[_RS(op)].s16();
  if (s > d) {
    d = s;
  }
}
_END_OP

_DEFINE_OP(MAX_S32) {
  // max.s32 rS,rD
  sint32 &d = vm->gpr[_RD(op)].s32();
  sint32 s = vm->gpr[_RS(op)].s32();
  if (s > d) {
    d = s;
  }
}
_END_OP

_DEFINE_OP(MAX_S64) {
  // max.s64 rS,rD
  sint64 &d = vm->gpr[_RD(op)].s64();
  sint64 s = vm->gpr[_RS(op)].s64();
  if (s > d) {
    d = s;
  }
}
_END_OP

_DEFINE_OP(MAX_F32) {
  // max.f32 rS,rD
  float32 &d = vm->gpr[_RD(op)].f32();
  float32 s = vm->gpr[_RS(op)].f32();
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

// MISC /////////////////////////////////////////////////////////////////////

_DEFINE_OP(MUL_ADD_F32) {
  vm->gpr[_RD(op)].f32() = vm->gpr[_RS(op)].f32() * vm->gpr[_EX_U8_1].f32() + vm->gpr[_EX_U8_2].f32();
  ++vm->pc.extU16;
}
_END_OP

_DEFINE_OP(MUL_ADD_F64) {
  vm->gpr[_RD(op)].f64() = vm->gpr[_RS(op)].f64() * vm->gpr[_EX_U8_1].f64() + vm->gpr[_EX_U8_2].f64();
  ++vm->pc.extU16;
}
_END_OP

