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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(MV_64) {
  // move.64 rS,rD
  vm->gpr[_RD(op)].u64() = vm->gpr[_RS(op)].u64();
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(BSWP_64) {
  // bswap.64 rS,rD
  GPR* reg = &vm->gpr[_RS(op)];
  uint32 v1 = reg->getMSW(); v1 = v1 << 16 | v1 >> 16;
  uint32 v2 = reg->getLSW(); v2 = v2 << 16 | v2 >> 16;
  reg = &vm->gpr[_RD(op)];
  reg->getLSW() = ((v1 & 0x00FF00FF) << 8) | ((v1 & 0xFF00FF00) >> 8);
  reg->getMSW() = ((v2 & 0x00FF00FF) << 8) | ((v2 & 0xFF00FF00) >> 8);
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if _VM_INTERPRETER == _VM_INTERPRETER_SWITCH_CASE

_DEFINE_OP(PUSH_64) {
  doPUSH_64(vm, op);
  if (vm->status != VMDefs::RUNNING) {
    _HALT
  }
}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(POP_64) {
  doPOP_64(vm, op);
  if (vm->status != VMDefs::RUNNING) {
    _HALT
  }
}
_END_OP

#endif

