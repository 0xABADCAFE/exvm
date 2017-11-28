//****************************************************************************//
//**                                                                        **//
//** File:         op_load_code.hpp                                         **//
//** Description:  Load group opcode implementation                         **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2001-08-29                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

_DEFINE_OP(LD_16_I64) {
  // ld.64 #n,rX, #n = -32768 - 32767
  // #n is in the extension word, treat as signed for expansion.
  vm->gpr[_RD(op)].s64() = _EX_S16;
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(LD_32_I64) {
  // ld.64 #n,rX, #n = -2^31 - (2^31)-1
  // #n is in the 32-bit extension word, treat as signed for expansion.
  vm->gpr[_RD(op)].s64() = _EX_S32;
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(LD_32_F64) {
  // ld.f64 #n,rX, #n = FLOAT_MIN - FLOAT_MAX
  // #n is in the 32-bit extension word, treat as single precision floating point for expansion.s
  vm->gpr[_RD(op)].f64() = _EX_F32;
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(LD_RI_64) {
  // ld.64 (rS),rD
  vm->gpr[_RD(op)].u64() = *(vm->gpr[_RS(op)].pU64());
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(LD_RIPI_64) {
  // ld.64 (rS)+,rD
  vm->gpr[_RD(op)].u64() = *(vm->gpr[_RS(op)].pU64()++);
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(LD_RIPD_64) {
  // ld.64 -(rS),rD
  vm->gpr[_RD(op)].u64() = *(--vm->gpr[_RS(op)].pU64());
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(LD_RID_64) {
  // ld.64 (rS,#d16),rD
  // #d16 is in extension word
  vm->gpr[_RD(op)].u64() = *((uint64*)(vm->gpr[_RS(op)].pU8() + _EX_S16));
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(LD_64) {
  // ld.64 label, rX
  _DECLARE_DATA_SYMBOL(symbol)
  vm->gpr[_RS(op)].u64()  = *((uint64*)(vm->dataSymbol[symbol]));
}
_END_OP

