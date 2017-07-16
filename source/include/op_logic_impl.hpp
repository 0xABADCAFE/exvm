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

_DEFINE_OP(AND_8) {
  // and.8 rS,rD
  vm->gpr[_RD(op)].u8() &= vm->gpr[_RS(op)].u8();
}
_END_OP

_DEFINE_OP(AND_16) {
  // and.16 rS,rD
  vm->gpr[_RD(op)].u16() &= vm->gpr[_RS(op)].u16();
}
_END_OP

_DEFINE_OP(AND_32) {
  // and.32 rS,rD
  vm->gpr[_RD(op)].u32() &= vm->gpr[_RS(op)].u32();
}
_END_OP

_DEFINE_OP(AND_64) {
  // and.64 rS,rD
  vm->gpr[_RD(op)].u64() &= vm->gpr[_RS(op)].u64();
}
_END_OP

// BITWISE OR //////////////////////////////////////////////////////////////////

_DEFINE_OP(OR_8) {
  // or.8 rS,rD
  vm->gpr[_RD(op)].u8() |= vm->gpr[_RS(op)].u8();
}
_END_OP

_DEFINE_OP(OR_16) {
  // or.16 rS,rD
  vm->gpr[_RD(op)].u16() |= vm->gpr[_RS(op)].u16();
}
_END_OP

_DEFINE_OP(OR_32) {
  // or.32 rS,rD
  vm->gpr[_RD(op)].u32() |= vm->gpr[_RS(op)].u32();
}
_END_OP

_DEFINE_OP(OR_64) {
  // or.64 rS,rD
  vm->gpr[_RD(op)].u64() |= vm->gpr[_RS(op)].u64();
}
_END_OP

// BITWISE EXCLUSIVE OR ////////////////////////////////////////////////////////

_DEFINE_OP(XOR_8) {
  // xor.8 rS,rD
  vm->gpr[_RD(op)].u8() ^= vm->gpr[_RS(op)].u8();
}
_END_OP

_DEFINE_OP(XOR_16) {
  // xor.16 rS,rD
  vm->gpr[_RD(op)].u16() ^= vm->gpr[_RS(op)].u16();
}
_END_OP

_DEFINE_OP(XOR_32) {
  // xor.32 rS,rD
  vm->gpr[_RD(op)].u32() ^= vm->gpr[_RS(op)].u32();
}
_END_OP

_DEFINE_OP(XOR_64) {
  // xor.64 rS,rD
  vm->gpr[_RD(op)].u64() ^= vm->gpr[_RS(op)].u64();
}
_END_OP

// BITWISE INVERT //////////////////////////////////////////////////////////////

_DEFINE_OP(INV_8) {
  // inv.8 rS,rD
  vm->gpr[_RD(op)].u8() = ~vm->gpr[_RS(op)].u8();
}
_END_OP

_DEFINE_OP(INV_16) {
  // inv.16 rS,rD
  vm->gpr[_RD(op)].u16() = ~vm->gpr[_RS(op)].u16();
}
_END_OP

_DEFINE_OP(INV_32) {
  // inv.32 rS,rD
  vm->gpr[_RD(op)].u32() = ~vm->gpr[_RS(op)].u32();
}
_END_OP

_DEFINE_OP(INV_64) {
  // inv.64 rS,rD
  vm->gpr[_RD(op)].u64() = ~vm->gpr[_RS(op)].u64();
}
_END_OP

// BITWISE SHIFT LEFT //////////////////////////////////////////////////////////

_DEFINE_OP(LSL_8) {
  // lsl.8 rS,rD
  vm->gpr[_RD(op)].u8() <<= vm->gpr[_RS(op)].u8();
}
_END_OP

_DEFINE_OP(LSL_16) {
  // lsl.16 rS,rD
  vm->gpr[_RD(op)].u16() <<= vm->gpr[_RS(op)].u8();
}
_END_OP

_DEFINE_OP(LSL_32) {
  // lsl.32 rS,rD
  vm->gpr[_RD(op)].u32() <<= vm->gpr[_RS(op)].u8();
}
_END_OP

_DEFINE_OP(LSL_64) {
  // lsl.64 rS,rD
  vm->gpr[_RD(op)].u64() <<= vm->gpr[_RS(op)].u8();
}
_END_OP

// BITWISE SHIFT RIGHT /////////////////////////////////////////////////////////

_DEFINE_OP(LSR_8) {
  // lsl.8 rS,rD
  vm->gpr[_RD(op)].u8() >>= vm->gpr[_RS(op)].u8();
}
_END_OP

_DEFINE_OP(LSR_16) {
  // lsl.16 rS,rD
  vm->gpr[_RD(op)].u16() >>= vm->gpr[_RS(op)].u8();
}
_END_OP

_DEFINE_OP(LSR_32) {
  // lsl.32 rS,rD
  vm->gpr[_RD(op)].u32() >>= vm->gpr[_RS(op)].u8();
}
_END_OP

_DEFINE_OP(LSR_64) {
  // lsl.64 rS,rD
  vm->gpr[_RD(op)].u64() >>= vm->gpr[_RS(op)].u8();
}
_END_OP

// BITWISE ROTATE LEFT /////////////////////////////////////////////////////////

_DEFINE_OP(ROL_8) {
  uint32 val              = vm->gpr[_RD(op)].u8();
  uint32 shift            = vm->gpr[_RS(op)].u8() & 0x7;
  vm->gpr[_RD(op)].u8() = (val << shift | val >> (8 - shift));
}
_END_OP

_DEFINE_OP(ROL_16) {
  uint32 val              = vm->gpr[_RD(op)].u16();
  uint32 shift            = vm->gpr[_RS(op)].u8() & 0xF;
  vm->gpr[_RD(op)].u16()  = (val << shift | val >> (16 - shift));
}
_END_OP

_DEFINE_OP(ROL_32) {
  uint32 val              = vm->gpr[_RD(op)].u32();
  uint32 shift            = vm->gpr[_RS(op)].u8() & 0x1F;
  vm->gpr[_RD(op)].u32()  = (val << shift | val >> ( 32 - shift));
}
_END_OP

_DEFINE_OP(ROL_64) {
  uint64 val              = vm->gpr[_RD(op)].u64();
  uint32 shift            = vm->gpr[_RS(op)].u8() & 0x3F;
  vm->gpr[_RD(op)].u64()  = (val << shift | val >> (64 - shift));
}
_END_OP

// BITWISE ROTATE RIGHT ////////////////////////////////////////////////////////

_DEFINE_OP(ROR_8) {
  uint32 val            = vm->gpr[_RD(op)].u8();
  uint32 shift          = vm->gpr[_RS(op)].u8() & 0x7;
  vm->gpr[_RD(op)].u8() = (val >> shift | val << (8 - shift));
}
_END_OP

_DEFINE_OP(ROR_16) {
  uint32 val              = vm->gpr[_RD(op)].u16();
  uint32 shift            = vm->gpr[_RS(op)].u8() & 0xF;
  vm->gpr[_RD(op)].u16()  = (val >> shift | val << (16 - shift));
}
_END_OP

_DEFINE_OP(ROR_32) {
  uint32 val              = vm->gpr[_RD(op)].u32();
  uint32 shift            = vm->gpr[_RS(op)].u8() & 0x1F;
  vm->gpr[_RD(op)].u32()  = (val >> shift | val << (32 - shift));
}
_END_OP

_DEFINE_OP(ROR_64) {
  uint64 val              = vm->gpr[_RD(op)].u64();
  uint32 shift            = vm->gpr[_RS(op)].u8() & 0x3F;
  vm->gpr[_RD(op)].u64()  = (val >> shift | val << (64 - shift));
}
_END_OP
