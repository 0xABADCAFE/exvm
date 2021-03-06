//****************************************************************************//
//**                                                                        **//
//** File:         op_move_code.hpp                                         **//
//** Description:  Move group opcode implementation                         **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2005-01-29                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

_DEFINE_OP(MV_8) {
  // move.8 rS,rD
  vm->gpr[_RD(op)].u8() = vm->gpr[_RS(op)].u8();
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(MV_16) {
  // move.16 rS,rD
  vm->gpr[_RD(op)].u16() = vm->gpr[_RS(op)].u16();
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(MV_32) {
  // move.32 rS,rD
  vm->gpr[_RD(op)].u32() = vm->gpr[_RS(op)].u32();
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(BSWP_16) {
  // bswap.16 rS,rD
  uint16 word16 = vm->gpr[_RS(op)].u16();
  vm->gpr[_RD(op)].u16() = word16 >> 8 | word16 << 8;
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(BSWP_32) {
  // bswap.32 rS,rD
  uint32 word32 =  vm->gpr[_RS(op)].u32();
  word32        = word32 >> 16 | word32 << 16;
  vm->gpr[_RD(op)].u32() = ((word32 & 0x00FF00FF) << 8) | ((word32 & 0xFF00FF00) >> 8);
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(EXG) {
  // exg rS,rD
  uint64 t = vm->gpr[_RD(op)].u64();
  vm->gpr[_RD(op)].u64() = vm->gpr[_RS(op)].u64();
  vm->gpr[_RS(op)].u64() = t;
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if _VM_INTERPRETER == _VM_INTERPRETER_SWITCH_CASE

_DEFINE_OP(SV) {
  doSV(vm, op);
  if (vm->status != VMDefs::RUNNING) {
    vm->exceptionOffset = EXC_OFFSET_EXT;
    _HALT
  }
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(RS) {
  doRS(vm, op);
  if (vm->status != VMDefs::RUNNING) {
    vm->exceptionOffset = EXC_OFFSET_EXT;
    _HALT
  }
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(PUSH_8) {
  doPUSH_8(vm, op);
  if (vm->status != VMDefs::RUNNING) {
    vm->exceptionOffset = EXC_OFFSET_EXT;
    _HALT
  }
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(PUSH_16) {
  doPUSH_16(vm, op);
  if (vm->status != VMDefs::RUNNING) {
    vm->exceptionOffset = EXC_OFFSET_EXT;
    _HALT
  }
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(PUSH_32) {
  doPUSH_32(vm, op);
  if (vm->status != VMDefs::RUNNING) {
    vm->exceptionOffset = EXC_OFFSET_EXT;
    _HALT
  }
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(POP_8) {
  doPOP_8(vm, op);
  if (vm->status != VMDefs::RUNNING) {
    vm->exceptionOffset = EXC_OFFSET_EXT;
    _HALT
  }
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(POP_16) {
  doPOP_16(vm, op);
  if (vm->status != VMDefs::RUNNING) {
    vm->exceptionOffset = EXC_OFFSET_EXT;
    _HALT
  }
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(POP_32) {
  doPOP_32(vm, op);
  if (vm->status != VMDefs::RUNNING) {
    vm->exceptionOffset = EXC_OFFSET_EXT;
    _HALT
  }
}
_END_OP
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(SALLOC) {
  doSALLOC(vm, op);
  if (vm->status != VMDefs::RUNNING) {
    vm->exceptionOffset = EXC_OFFSET_EXT;
    _HALT
  }
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(SFREE) {
  doSFREE(vm, op);
  if (vm->status != VMDefs::RUNNING) {
    vm->exceptionOffset = EXC_OFFSET_EXT;
    _HALT
  }
}
_END_OP

#endif

