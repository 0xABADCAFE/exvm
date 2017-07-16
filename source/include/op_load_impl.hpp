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

_DEFINE_OP(LDQ) {
  // ld.64 #n,rX, #n = 0-15
  // #n is in the operand byte
  vm->gpr[_RD(op)].u64() = _RS(op);
}
_END_OP

_DEFINE_OP(LD_I16_8) {
  // ld.8 #n,rX, #n = -128 - 127
  // #n is in the lower 8 bits of the extension word
  vm->gpr[_RD(op)].u8() = _EX_U16 & 0xFF;
}
_END_OP

_DEFINE_OP(LD_I16_16) {
  // ld.16 #n,rX, #n = -32768 - 32767
  // #n is in the extension word
  vm->gpr[_RD(op)].u16() = _EX_U16;
}
_END_OP

_DEFINE_OP(LD_I16_32) {
  // ld.32 #n,rX, #n = -32768 - 32767
  // #n is in the extension word, treat as signed for expansion.
  vm->gpr[_RD(op)].s32() = _EX_S16;
}
_END_OP

_DEFINE_OP(LD_I16_64) {
  // ld.64 #n,rX, #n = -32768 - 32767
  // #n is in the extension word, treat as signed for expansion.
  vm->gpr[_RD(op)].s64() = _EX_S16;
}
_END_OP

_DEFINE_OP(LD_I32_32) {
  // ld.32 #n,rX, #n = -2^31 - (2^31)-1
  // #n is in the 32-bit extension word.
  vm->gpr[_RD(op)].u32() = _EX_U32;
}
_END_OP

_DEFINE_OP(LD_I32_64) {
  // ld.64 #n,rX, #n = -2^31 - (2^31)-1
  // #n is in the 32-bit extension word, treat as signed for expansion.
  vm->gpr[_RD(op)].s64() = _EX_S32;
}
_END_OP

_DEFINE_OP(LD_F32) {
  // ld.f32 #n,rX, #n = MIN_FLOAT - MAX_FLOAT
  // #n is in the 32-bit extension word, equivalent to LD_I32_32.
  // FIXME: update instruction set?
  vm->gpr[_RD(op)].u32() = _EX_U32;
}
_END_OP

_DEFINE_OP(LD_RI_8) {
  // ld.8 (rS),rD
  vm->gpr[_RD(op)].u8() = *(vm->gpr[_RS(op)].pU8());
}
_END_OP

_DEFINE_OP(LD_RI_16) {
  // ld.16 (rS),rD
  vm->gpr[_RD(op)].u16() = *(vm->gpr[_RS(op)].pU16());
}
_END_OP

_DEFINE_OP(LD_RI_32) {
  // ld.32 (rS),rD
  vm->gpr[_RD(op)].u32() = *(vm->gpr[_RS(op)].pU32());
}
_END_OP

_DEFINE_OP(LD_RI_64) {
  // ld.64 (rS),rD
  vm->gpr[_RD(op)].u64() = *(vm->gpr[_RS(op)].pU64());
}
_END_OP

_DEFINE_OP(LD_RIPI_8) {
  // ld.8 (rS)+,rD
  vm->gpr[_RD(op)].u8() = *(vm->gpr[_RS(op)].pU8()++);
}
_END_OP

_DEFINE_OP(LD_RIPI_16) {
  // ld.16 (rS)+,rD
  vm->gpr[_RD(op)].u16() = *(vm->gpr[_RS(op)].pU16()++);
}
_END_OP

_DEFINE_OP(LD_RIPI_32) {
  // ld.32 (rS)+,rD
  vm->gpr[_RD(op)].u32() = *(vm->gpr[_RS(op)].pU32()++);
}
_END_OP

_DEFINE_OP(LD_RIPI_64) {
  // ld.64 (rS)+,rD
  vm->gpr[_RD(op)].u64() = *(vm->gpr[_RS(op)].pU64()++);
}
_END_OP

_DEFINE_OP(LD_RIPD_8) {
  // ld.8 -(rS),rD
  vm->gpr[_RD(op)].u8() = *(--vm->gpr[_RS(op)].pU8());
}
_END_OP

_DEFINE_OP(LD_RIPD_16) {
  // ld.16 -(rS),rD
  vm->gpr[_RD(op)].u16() = *(--vm->gpr[_RS(op)].pU16());
}
_END_OP

_DEFINE_OP(LD_RIPD_32) {
  // ld.32 -(rS),rD
  vm->gpr[_RD(op)].u32() = *(--vm->gpr[_RS(op)].pU32());
}
_END_OP

_DEFINE_OP(LD_RIPD_64) {
  // ld.64 -(rS),rD
  vm->gpr[_RD(op)].u64() = *(--vm->gpr[_RS(op)].pU64());
}
_END_OP

_DEFINE_OP(LD_RID_8) {
  // ld.8 (rS,#d16),rD
  // #d16 is in extension word
  vm->gpr[_RD(op)].u8() = *(vm->gpr[_RS(op)].pU8() + _EX_S16);
}
_END_OP

_DEFINE_OP(LD_RID_16) {
  // ld.16 (rS,#d16),rD
  // #d16 is in extension word
  vm->gpr[_RD(op)].u16() = *((uint16*)(vm->gpr[_RS(op)].pU8() + _EX_S16));
}
_END_OP

_DEFINE_OP(LD_RID_32) {
  // ld.32 (rS,#d16),rD
  // #d16 is in extension word
  vm->gpr[_RD(op)].u32() = *((uint32*)(vm->gpr[_RS(op)].pU8() + _EX_S16));
}
_END_OP

_DEFINE_OP(LD_RID_64) {
  // ld.64 (rS,#d16),rD
  // #d16 is in extension word
  vm->gpr[_RD(op)].u64() = *((uint64*)(vm->gpr[_RS(op)].pU8() + _EX_S16));
}
_END_OP

_DEFINE_OP(LD_RII_8) {
  // ld.8 (rS,rI,#s),rD
  // #s : rI are in the extension word
  uint16 ex = _EX_U16;
  vm->gpr[_RD(op)].u8() = *(vm->gpr[_RS(op)].pU8() +  // rS
                          (vm->gpr[_RI(ex)].s32() *   // rI
                          _SC(ex)));                  // s
}
_END_OP

_DEFINE_OP(LD_RII_16) {
  // ld.16 (rS,rI,#s),rD
  // #s : rI are in the extension word
  uint16 ex = _EX_U16;
  vm->gpr[_RD(op)].u16() = *((uint16*)(vm->gpr[_RS(op)].pU8() + // rS
                            (vm->gpr[_RI(ex)].s32() *           // rI
                            _SC(ex))));                         // s
}
_END_OP

_DEFINE_OP(LD_RII_32) {
  // ld.32 (rS,rI,#s),rD
  // #s : rI are in the extension word
  uint16 ex = _EX_U16;
  vm->gpr[_RD(op)].u32() = *((uint32*)(vm->gpr[_RS(op)].pU8() + // rS
                            (vm->gpr[_RI(ex)].s32() *           // rI
                            _SC(ex))));                         // s
}
_END_OP

_DEFINE_OP(LD_RII_64) {
  // ld.16 (rS,rI,#s),rD
  // #s:rI are in the extension word
  uint16 ex = _EX_U16;
  vm->gpr[_RD(op)].u64() = *((uint64*)(vm->gpr[_RS(op)].pU8() + // rS
                            (vm->gpr[_RI(ex)].s32() *           // rI
                            _SC(ex))));                         // s
}
_END_OP

_DEFINE_OP(LD_8) {
  // ld.8 label, rX
  _DECLARE_DATA_SYMBOL(symbol)
  vm->gpr[_RX(op)].u8() = *((uint8*)(vm->dataSymbol[symbol]));
}
_END_OP

_DEFINE_OP(LD_16) {
  // ld.16 label, rX
  _DECLARE_DATA_SYMBOL(symbol)
  vm->gpr[_RX(op)].u16()  = *((uint16*)(vm->dataSymbol[symbol]));
}
_END_OP

_DEFINE_OP(LD_32) {
  // ld.32 label, rX
  _DECLARE_DATA_SYMBOL(symbol)
  vm->gpr[_RX(op)].u32()  = *((uint32*)(vm->dataSymbol[symbol]));
}
_END_OP

_DEFINE_OP(LD_64) {
  // ld.64 label, rX
  _DECLARE_DATA_SYMBOL(symbol)
  vm->gpr[_RX(op)].u64()  = *((uint64*)(vm->dataSymbol[symbol]));
}
_END_OP

_DEFINE_OP(LD_ADDR) {
  // lda label, rX
  _DECLARE_DATA_SYMBOL(symbol)
  vm->gpr[_RX(op)].u64()  = (uint64)vm->dataSymbol[symbol];
}
_END_OP

