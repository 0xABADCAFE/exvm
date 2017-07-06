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

_DEFINE_OP(MV_16) {
  // move.16 rS,rD
  vm->gpr[_RD(op)].u16() = vm->gpr[_RS(op)].u16();
}
_END_OP

_DEFINE_OP(MV_32) {
  // move.32 rS,rD
  vm->gpr[_RD(op)].u32() = vm->gpr[_RS(op)].u32();
}
_END_OP

_DEFINE_OP(MV_64) {
  // move.64 rS,rD
  vm->gpr[_RD(op)].u64() = vm->gpr[_RS(op)].u64();
}
_END_OP

_DEFINE_OP(BSWP_16) {
  // bswap.16 rS,rD
  uint16 word16 = vm->gpr[_RS(op)].u16();
  vm->gpr[_RD(op)].u16() = word16>>8 | word16<<8;
}
_END_OP

_DEFINE_OP(BSWP_32) {
  // bswap.32 rS,rD
  uint32 word32 =  vm->gpr[_RS(op)].u32();
  word32        = word32>>16 | word32<<16;
  vm->gpr[_RD(op)].u32() = ((word32 & 0x00FF00FF)<<8) | ((word32 & 0xFF00FF00)>>8);
}
_END_OP

_DEFINE_OP(BSWP_64) {
  // bswap.64 rS,rD
  GPR* reg = &vm->gpr[_RS(op)];
  uint32 v1 = reg->getMSW(); v1 = v1<<16 | v1>>16;
  uint32 v2 = reg->getLSW(); v2 = v2<<16 | v2>>16;
  reg = &vm->gpr[_RD(op)];
  reg->getLSW() = ((v1 & 0x00FF00FF)<<8) | ((v1 & 0xFF00FF00)>>8);
  reg->getMSW() = ((v2 & 0x00FF00FF)<<8) | ((v2 & 0xFF00FF00)>>8);
}
_END_OP

_DEFINE_OP(EXG) {
  // exg rS,rD
  uint64 t = vm->gpr[_RD(op)].u64();
  vm->gpr[_RD(op)].u64() = vm->gpr[_RS(op)].u64();
  vm->gpr[_RS(op)].u64() = t;
}
_END_OP

_DEFINE_OP(SV) {
  // save r1,r2...
  uint16  mask  = _EX_U16;
  GPR*    r     = vm->gpr;

  while (mask && (vm->regStack < vm->regStackTop)) {
    if (mask&0x0001) {
      *vm->regStack++ = r->u64();
    }
    ++r;
    mask>>=1;
  }
  if (mask) {
    // not all the registers were saved, signifying an overflow
    vm->status = VMDefs::REG_STACK_OVERFLOW;
    #ifdef VM_FULL_DEBUG
    printf("Runtime error: register stack overflow\n");
    vm->dump();
    #endif
    _THROW(-1)
  }
}
_END_OP

_DEFINE_OP(RS) {
  // restore r1,r2...
  uint16  mask  = _EX_U16;
  GPR*    r     = vm->gpr+15;
  while (mask && (vm->regStack > vm->regStackBase)) {
    if (mask&0x8000) {
      r->u64() = *(--vm->regStack);
    }
    --r;
    mask<<=1;
  }
  if (mask) {
    // not all the registers were restored, signifying an underflow
    vm->status = VMDefs::REG_STACK_UNDERFLOW;
    #ifdef VM_FULL_DEBUG
    printf("Runtime error: register stack underflow\n");
    vm->dump();
    #endif
    _THROW(-1)
  }

}
_END_OP

_DEFINE_OP(PUSH_8) {
  uint16 mask =  _EX_U16;
  GPR*  r = vm->gpr;
  while (mask && (vm->dataStack.u8 < vm->dataStackTop)) {
    if (mask & 1) {
      *vm->dataStack.u16++ = r->u8();
    }
    r++;
    mask>>=1;
  }
  if (mask) {
    // not all the data were pushed, signifying an overflow
    vm->status = VMDefs::REG_STACK_OVERFLOW;
    #ifdef VM_FULL_DEBUG
    printf("Runtime error: data stack overflow\n");
    vm->dump();
    #endif
    _THROW(-1)
  }
}
_END_OP

_DEFINE_OP(PUSH_16) {
  uint16 mask =  _EX_U16;
  GPR*  r = vm->gpr;
  while (mask && (vm->dataStack.u8 < vm->dataStackTop)) {
    if (mask & 1) {
      *vm->dataStack.u16++ = r->u8();
    }
    ++r;
    mask>>=1;
  }
  if (mask) {
    // not all the data were pushed, signifying an overflow
    vm->status = VMDefs::REG_STACK_OVERFLOW;
    #ifdef VM_FULL_DEBUG
    printf("Runtime error: data stack overflow\n");
    vm->dump();
    #endif
    _THROW(-1)
  }
}
_END_OP

_DEFINE_OP(PUSH_32) {
  uint16 mask =  _EX_U16;
  GPR*  r = vm->gpr;
  while (mask && (vm->dataStack.u8 < vm->dataStackTop)) {
    if (mask & 1) {
      *vm->dataStack.u32++ = r->u32();
    }
    ++r;
    mask>>=1;
  }
  if (mask) {
    // not all the data were pushed, signifying an overflow
    vm->status = VMDefs::REG_STACK_OVERFLOW;
    #ifdef VM_FULL_DEBUG
    printf("Runtime error: data stack overflow\n");
    vm->dump();
    #endif
    _THROW(-1)
  }
}
_END_OP

_DEFINE_OP(PUSH_64) {
  uint16 mask =  _EX_U16;
  GPR*  r = vm->gpr;
  while (mask && (vm->dataStack.u8 < vm->dataStackTop)) {
    if (mask & 1) {
      *vm->dataStack.u64++ = r->u64();
    }
    ++r;
    mask>>=1;
  }
  if (mask) {
    // not all the data were pushed, signifying an overflow
    vm->status = VMDefs::REG_STACK_OVERFLOW;
    #ifdef VM_FULL_DEBUG
    printf("Runtime error: data stack overflow\n");
    vm->dump();
    #endif
    _THROW(-1)
  }
}
_END_OP

_DEFINE_OP(POP_8) {
  uint16 mask =  _EX_U16;
  GPR*  r = vm->gpr+15;
  while (mask && (vm->dataStack.u8 > vm->dataStackBase)) {
    if (mask & 0x8000) {
      r->u8() = *(--vm->dataStack.u16);
    }
    --r;
    mask<<=1;
  }
  if (mask) {
    // not all the data were popped, signifying an underflow
    vm->status = VMDefs::REG_STACK_UNDERFLOW;
    #ifdef VM_FULL_DEBUG
    printf("Runtime error: data stack underflow\n");
    vm->dump();
    #endif
    _THROW(-1)
  }
}
_END_OP

_DEFINE_OP(POP_16) {
  uint16 mask =  _EX_U16;
  GPR*  r = vm->gpr+15;
  while (mask && (vm->dataStack.u8 > vm->dataStackBase)) {
    if (mask & 0x8000) {
      r->u16() = *(--vm->dataStack.u16);
    }
    --r;
    mask<<=1;
  }
  if (mask) {
    // not all the data were popped, signifying an underflow
    vm->status = VMDefs::REG_STACK_UNDERFLOW;
    #ifdef VM_FULL_DEBUG
    printf("Runtime error: data stack underflow\n");
    vm->dump();
    #endif
    _THROW(-1)
  }
}
_END_OP

_DEFINE_OP(POP_32) {
  uint16 mask =  _EX_U16;
  GPR*  r = vm->gpr+15;
  while (mask && (vm->dataStack.u8 > vm->dataStackBase)) {
    if (mask & 0x8000) {
      r->u32() = *(--vm->dataStack.u32);
    }
    --r;
    mask<<=1;
  }
  if (mask) {
    // not all the data were popped, signifying an underflow
    vm->status = VMDefs::REG_STACK_UNDERFLOW;
    #ifdef VM_FULL_DEBUG
    printf("Runtime error: data stack underflow\n");
    vm->dump();
    #endif
    _THROW(-1)
  }
}
_END_OP

_DEFINE_OP(POP_64) {
  uint16 mask =  _EX_U16;
  GPR*  r = vm->gpr+15;
  while (mask && (vm->dataStack.u8 > vm->dataStackBase)) {
    if (mask & 0x8000) {
      r->u64() = *(--vm->dataStack.u64);
    }
    --r;
    mask<<=1;
  }
  if (mask) {
    // not all the data were popped, signifying an underflow
    vm->status = VMDefs::REG_STACK_UNDERFLOW;
    #ifdef VM_FULL_DEBUG
    printf("Runtime error: data stack underflow\n");
    vm->dump();
    #endif
    _THROW(-1)
  }
}
_END_OP

