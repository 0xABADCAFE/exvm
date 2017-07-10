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

_DEFINE_OP(ST_RI_64) {
  // st.64 rS, (rD)
  *(vm->gpr[_RD(op)].pU64()) = vm->gpr[_RS(op)].u64();
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

_DEFINE_OP(ST_RIPI_64) {
  // st.64 rS, (rD)+
  *(vm->gpr[_RD(op)].pU64()++) = vm->gpr[_RS(op)].u64();
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

_DEFINE_OP(ST_RIPD_64) {
  // st.64 rS, -(rD)
  *(--vm->gpr[_RD(op)].pU64()) = vm->gpr[_RS(op)].u64();
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

_DEFINE_OP(ST_RID_64) {
  // st.64 rS, (rD,#d16)
  // #d16 is in extension word
  *(vm->gpr[_RD(op)].pU64() + _EX_S16) = vm->gpr[_RS(op)].u64();
}
_END_OP

_DEFINE_OP(ST_RII_8) {
  // st.8 rS, (rD,rI,#s)
  // #s : rI are in the extension word
  uint16 ex = _EX_U16;
  *(vm->gpr[_RD(op)].pU8()+(vm->gpr[_RI(ex)].s32()*_SC(ex))) = vm->gpr[_RS(op)].u8();
}
_END_OP

_DEFINE_OP(ST_RII_16) {
  // st.16 rS, (rD,rI,#s)
  // #s : rI are in the extension word
  uint16 ex = _EX_U16;
  *((uint16*)(vm->gpr[_RD(op)].pU8()+(vm->gpr[_RI(ex)].s32() * _SC(ex)))) = vm->gpr[_RS(op)].u16();
}
_END_OP

_DEFINE_OP(ST_RII_32) {
  // st.32 rS, (rD,rI,#s)
  // #s : rI are in the extension word
  uint16 ex = _EX_U16;
  *((uint32*)(vm->gpr[_RD(op)].pU8()+(vm->gpr[_RI(ex)].s32() * _SC(ex)))) = vm->gpr[_RS(op)].u32();
}
_END_OP

_DEFINE_OP(ST_RII_64) {
  // st.64 rS, (rD,rI,#s)
  // #s : rI are in the extension word
  uint16 ex = _EX_U16;
  *((uint64*)(vm->gpr[_RD(op)].pU8()+(vm->gpr[_RI(ex)].s32() * _SC(ex)))) = vm->gpr[_RS(op)].u64();
}
_END_OP

_DEFINE_OP(ST_8) {
  // st.8 rX, label
  // runtime evaluated address is in 32-bit extension word (32-bit systems) after parsing.
  *((uint8*)(_EX_PTR)) = vm->gpr[_RX(op)].u8();
}
_END_OP

_DEFINE_OP(ST_16) {
  // st.16 rX, label
  // runtime evaluated address is in 32-bit extension word (32-bit systems) after parsing.
  *((uint16*)(_EX_PTR)) = vm->gpr[_RX(op)].u16();
}
_END_OP

_DEFINE_OP(ST_32) {
  // st.32 rX, label
  // runtime evaluated address is in 32-bit extension word (32-bit systems) after parsing.
  *((uint32*)(_EX_PTR)) = vm->gpr[_RX(op)].u32();
}
_END_OP

_DEFINE_OP(ST_64) {
  // st.64 rX, label
  // runtime evaluated address is in 32-bit extension word (32-bit systems) after parsing.
  *((uint64*)(_EX_PTR)) = vm->gpr[_RX(op)].u64();
}
_END_OP

