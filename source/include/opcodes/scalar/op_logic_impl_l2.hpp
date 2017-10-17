//****************************************************************************//
//**                                                                        **//
//** File:         op_logic_code.hpp                                        **//
//** Description:  Logic group opcode implementation                        **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2001-08-29                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

// BITWISE AND /////////////////////////////////////////////////////////////////

_DEFINE_OP(AND_64) {
  // and.64 rS,rD
  vm->gpr[_RD(op)].u64() &= vm->gpr[_RS(op)].u64();
}
_END_OP

// BITWISE OR //////////////////////////////////////////////////////////////////

_DEFINE_OP(OR_64) {
  // or.64 rS,rD
  vm->gpr[_RD(op)].u64() |= vm->gpr[_RS(op)].u64();
}
_END_OP

// BITWISE EXCLUSIVE OR ////////////////////////////////////////////////////////

_DEFINE_OP(XOR_64) {
  // xor.64 rS,rD
  vm->gpr[_RD(op)].u64() ^= vm->gpr[_RS(op)].u64();
}
_END_OP

// BITWISE INVERT //////////////////////////////////////////////////////////////

_DEFINE_OP(INV_64) {
  // inv.64 rS,rD
  vm->gpr[_RD(op)].u64() = ~vm->gpr[_RS(op)].u64();
}
_END_OP

// BITWISE SHIFT LEFT //////////////////////////////////////////////////////////

_DEFINE_OP(LSL_64) {
  // lsl.64 rS,rD
  vm->gpr[_RD(op)].u64() <<= vm->gpr[_RS(op)].u8();
}
_END_OP

// BITWISE SHIFT RIGHT /////////////////////////////////////////////////////////

_DEFINE_OP(LSR_64) {
  // lsl.64 rS,rD
  vm->gpr[_RD(op)].u64() >>= vm->gpr[_RS(op)].u8();
}
_END_OP

// BITWISE ROTATE LEFT /////////////////////////////////////////////////////////

_DEFINE_OP(ROL_64) {
  uint64 val              = vm->gpr[_RD(op)].u64();
  uint32 shift            = vm->gpr[_RS(op)].u8() & 0x3F;
  vm->gpr[_RD(op)].u64()  = (val << shift | val >> (64 - shift));
}
_END_OP

// BITWISE ROTATE RIGHT ////////////////////////////////////////////////////////

_DEFINE_OP(ROR_64) {
  uint64 val              = vm->gpr[_RD(op)].u64();
  uint32 shift            = vm->gpr[_RS(op)].u8() & 0x3F;
  vm->gpr[_RD(op)].u64()  = (val >> shift | val << (64 - shift));
}
_END_OP

