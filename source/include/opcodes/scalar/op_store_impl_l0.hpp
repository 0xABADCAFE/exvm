//****************************************************************************//
//**                                                                        **//
//** File:         op_store_code.hpp                                        **//
//** Description:  Store group opcode implementation                        **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2001-08-29                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

_DEFINE_OP(ST_RI_8) {
  // st.8 rS, (rD)
  *(vm->gpr[_RD(op)].pU8()) = vm->gpr[_RS(op)].u8();
}
_END_OP

_DEFINE_OP(ST_RI_16) {
  // st.16 rS, (rD)
  *(vm->gpr[_RD(op)].pU16()) = vm->gpr[_RS(op)].u16();
}
_END_OP

_DEFINE_OP(ST_RI_32) {
  // st.32 rS, (rD)
  *(vm->gpr[_RD(op)].pU32()) = vm->gpr[_RS(op)].u32();
}
_END_OP

_DEFINE_OP(ST_RIPI_8) {
  // st.8 rS, (rD)+
  *(vm->gpr[_RD(op)].pU8()++) = vm->gpr[_RS(op)].u8();
}
_END_OP

_DEFINE_OP(ST_RIPI_16) {
  // st.16 rS, (rD)+
  *(vm->gpr[_RD(op)].pU16()++) = vm->gpr[_RS(op)].u16();
}
_END_OP

_DEFINE_OP(ST_RIPI_32) {
  // st.32 rS, (rD)+
  *(vm->gpr[_RD(op)].pU32()++) = vm->gpr[_RS(op)].u32();
}
_END_OP

_DEFINE_OP(ST_RIPD_8) {
  // st.8 rS, -(rD)
  *(--vm->gpr[_RD(op)].pU8()) = vm->gpr[_RS(op)].u8();
}
_END_OP

_DEFINE_OP(ST_RIPD_16) {
  // st.16 rS, -(rD)
  *(--vm->gpr[_RD(op)].pU16()) = vm->gpr[_RS(op)].u16();
}
_END_OP

_DEFINE_OP(ST_RIPD_32) {
  // st.32 rS, -(rD)
  *(--vm->gpr[_RD(op)].pU32()) = vm->gpr[_RS(op)].u32();
}
_END_OP

_DEFINE_OP(ST_RID_8) {
  // st.8 rS, (rD,#d16)
  // #d16 is in extension word
  *(vm->gpr[_RD(op)].pU8() + _EX_S16) = vm->gpr[_RS(op)].u8();
}
_END_OP

_DEFINE_OP(ST_RID_16) {
  // st.16 rS, (rD,#d16)
  // #d16 is in extension word
  *(vm->gpr[_RD(op)].pU16() + _EX_S16) = vm->gpr[_RS(op)].u16();
}
_END_OP

_DEFINE_OP(ST_RID_32) {
  // st.32 rS, (rD,#d16)
  // #d16 is in extension word
  *(vm->gpr[_RD(op)].pU32() + _EX_S16) = vm->gpr[_RS(op)].u32();
}
_END_OP

_DEFINE_OP(ST_8) {
  // st.8 rX, label
  _DECLARE_DATA_SYMBOL(symbol)
  *((uint8*)(vm->dataSymbol[symbol])) = vm->gpr[_RX(op)].u8();
}
_END_OP

_DEFINE_OP(ST_16) {
  // st.16 rX, label
  _DECLARE_DATA_SYMBOL(symbol)
  *((uint16*)(vm->dataSymbol[symbol])) = vm->gpr[_RX(op)].u16();
}
_END_OP

_DEFINE_OP(ST_32) {
  // st.32 rX, label
  _DECLARE_DATA_SYMBOL(symbol)
  *((uint32*)(vm->dataSymbol[symbol])) = vm->gpr[_RX(op)].u32();
}
_END_OP


