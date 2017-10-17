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

_DEFINE_OP(ST_RI_64) {
  // st.64 rS, (rD)
  *(vm->gpr[_RD(op)].pU64()) = vm->gpr[_RS(op)].u64();
}
_END_OP

_DEFINE_OP(ST_RIPI_64) {
  // st.64 rS, (rD)+
  *(vm->gpr[_RD(op)].pU64()++) = vm->gpr[_RS(op)].u64();
}
_END_OP


_DEFINE_OP(ST_RIPD_64) {
  // st.64 rS, -(rD)
  *(--vm->gpr[_RD(op)].pU64()) = vm->gpr[_RS(op)].u64();
}
_END_OP


_DEFINE_OP(ST_RID_64) {
  // st.64 rS, (rD,#d16)
  // #d16 is in extension word
  *(vm->gpr[_RD(op)].pU64() + _EX_S16) = vm->gpr[_RS(op)].u64();
}
_END_OP

_DEFINE_OP(ST_64) {
  // st.64 rX, label
  _DECLARE_DATA_SYMBOL(symbol)
  *((uint64*)(vm->dataSymbol[symbol])) = vm->gpr[_RX(op)].u64();
}
_END_OP

