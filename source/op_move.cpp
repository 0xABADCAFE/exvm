//****************************************************************************//
//**                                                                        **//
//** File:         op_move.cpp                                              **//
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
#include "include/vm_core.hpp"
#include "include/vm_inline.hpp"
#include "include/machine.hpp"
#include <cstdio>

#if _VM_INTERPRETER == _VM_INTERPRETER_FUNC_TABLE

  #include "include/vm_interpreter_func_table.hpp"


// Upon entry, the pc points to the 16-bit word following the current opcode.
// Normally, this would be the address of the next opcode. Handlers that use
// extension words must ensure that they increment the pc so that it points
// to the next opcode.

// Arguments:
// vm is a pointer to the VMCore instance
// op is the current opcode word

  #include "include/opcodes/scalar/op_move_impl.hpp"

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ExVM::Interpreter::doSV(ExVM::Interpreter* vm, uint16 op UNUSED) {
  uint16  mask  = _EX_U16;
  GPR*    r     = vm->gpr;

  while (mask && (vm->regStack < vm->regStackTop)) {
    if (mask & 0x0001) {
      *vm->regStack++ = r->u64();
    }
    ++r;
    mask >>= 1;
  }
  if (mask) {
    // not all the registers were saved, signifying an overflow
    vm->status = VMDefs::REG_STACK_OVERFLOW;
    debuglog(LOG_ERROR, "Register stack overflow");
    dumpstate(vm);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ExVM::Interpreter::doRS(ExVM::Interpreter* vm, uint16 op UNUSED) {
  uint16  mask  = _EX_U16;
  GPR*    r     = vm->gpr + GPR_LAST;
  while (mask && (vm->regStack > vm->regStackBase)) {
    if (mask & 0x8000) {
      r->u64() = *(--vm->regStack);
    }
    --r;
    mask<<=1;
  }
  if (mask) {
    // not all the registers were restored, signifying an underflow
    vm->status = VMDefs::REG_STACK_UNDERFLOW;
    debuglog(LOG_ERROR, "Register stack underflow");
    dumpstate(vm);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ExVM::Interpreter::doPUSH_8(ExVM::Interpreter* vm, uint16 op UNUSED) {
  uint16 mask =  _EX_U16;
  GPR*  r = vm->gpr;
  while (mask && (vm->dataStack.u8 < vm->dataStackTop)) {
    if (mask & 1) {
      *vm->dataStack.u16++ = r->u8();
    }
    r++;
    mask >>= 1;
  }
  if (mask) {
    // not all the data were pushed, signifying an overflow
    vm->status = VMDefs::DATA_STACK_OVERFLOW;
    debuglog(LOG_ERROR, "Data stack overflow in PUSH_8");
    dumpstate(vm);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ExVM::Interpreter::doPUSH_16(ExVM::Interpreter* vm, uint16 op UNUSED) {
  uint16 mask =  _EX_U16;
  GPR*  r = vm->gpr;
  while (mask && (vm->dataStack.u8 < vm->dataStackTop)) {
    if (mask & 1) {
      *vm->dataStack.u16++ = r->u16();
    }
    ++r;
    mask >>= 1;
  }
  if (mask) {
    // not all the data were pushed, signifying an overflow
    vm->status = VMDefs::DATA_STACK_OVERFLOW;
    debuglog(LOG_ERROR, "Data stack overflow in PUSH_16");
    dumpstate(vm);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ExVM::Interpreter::doPUSH_32(ExVM::Interpreter* vm, uint16 op UNUSED) {
  uint16 mask =  _EX_U16;
  GPR*  r = vm->gpr;
  while (mask && (vm->dataStack.u8 < vm->dataStackTop)) {
    if (mask & 1) {
      *vm->dataStack.u32++ = r->u32();
    }
    ++r;
    mask >>= 1;
  }
  if (mask) {
    // not all the data were pushed, signifying an overflow
    vm->status = VMDefs::DATA_STACK_OVERFLOW;
    debuglog(LOG_ERROR, "Data stack overflow in PUSH_32");
    dumpstate(vm);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ExVM::Interpreter::doPUSH_64(ExVM::Interpreter* vm, uint16 op UNUSED) {
  uint16 mask =  _EX_U16;
  GPR*  r = vm->gpr;
  while (mask && (vm->dataStack.u8 < vm->dataStackTop)) {
    if (mask & 1) {
      *vm->dataStack.u64++ = r->u64();
    }
    ++r;
    mask >>= 1;
  }
  if (mask) {
    // not all the data were pushed, signifying an overflow
    vm->status = VMDefs::DATA_STACK_OVERFLOW;
    debuglog(LOG_ERROR, "Data stack overflow in PUSH_64");
    dumpstate(vm);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ExVM::Interpreter::doPOP_8(ExVM::Interpreter* vm, uint16 op UNUSED) {
  uint16 mask =  _EX_U16;
  GPR*  r = vm->gpr + GPR_LAST;
  while (mask && (vm->dataStack.u8 > vm->dataStackBase)) {
    if (mask & 0x8000) {
      r->u8() = *(--vm->dataStack.u16);
    }
    --r;
    mask <<= 1;
  }
  if (mask) {
    // not all the data were popped, signifying an underflow
    vm->status = VMDefs::DATA_STACK_UNDERFLOW;
    debuglog(LOG_ERROR, "Data stack underflow in POP_8");
    dumpstate(vm);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ExVM::Interpreter::doPOP_16(ExVM::Interpreter* vm, uint16 op UNUSED) {
  uint16 mask =  _EX_U16;
  GPR*  r = vm->gpr + GPR_LAST;
  while (mask && (vm->dataStack.u8 > vm->dataStackBase)) {
    if (mask & 0x8000) {
      r->u16() = *(--vm->dataStack.u16);
    }
    --r;
    mask <<= 1;
  }
  if (mask) {
    // not all the data were popped, signifying an underflow
    vm->status = VMDefs::DATA_STACK_UNDERFLOW;
    debuglog(LOG_ERROR, "Data stack underflow in POP_16");
    dumpstate(vm);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ExVM::Interpreter::doPOP_32(ExVM::Interpreter* vm, uint16 op UNUSED) {
  uint16 mask =  _EX_U16;
  GPR*  r = vm->gpr + GPR_LAST;
  while (mask && (vm->dataStack.u8 > vm->dataStackBase)) {
    if (mask & 0x8000) {
      r->u32() = *(--vm->dataStack.u32);
    }
    --r;
    mask <<= 1;
  }
  if (mask) {
    // not all the data were popped, signifying an underflow
    vm->status = VMDefs::DATA_STACK_UNDERFLOW;
    debuglog(LOG_ERROR, "Data stack underflow in POP_32");
    dumpstate(vm);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ExVM::Interpreter::doPOP_64(ExVM::Interpreter* vm, uint16 op UNUSED) {
  uint16 mask =  _EX_U16;
  GPR*  r = vm->gpr + GPR_LAST;
  while (mask && (vm->dataStack.u8 > vm->dataStackBase)) {
    if (mask & 0x8000) {
      r->u64() = *(--vm->dataStack.u64);
    }
    --r;
    mask <<= 1;
  }
  if (mask) {
    // not all the data were popped, signifying an underflow
    vm->status = VMDefs::DATA_STACK_UNDERFLOW;
    debuglog(LOG_ERROR, "Data stack underflow in POP_64");
    dumpstate(vm);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ExVM::Interpreter::doSALLOC(ExVM::Interpreter* vm, uint16 op) {
  uint16 size =  _EX_U16;
  if ((vm->dataStack.u8 + size) < vm->dataStackTop) {
    vm->gpr[_RD(op)].pU8() = vm->dataStack.u8;
    vm->dataStack.u8 += size;
  } else {
    vm->status = VMDefs::DATA_STACK_OVERFLOW;
    debuglog(LOG_ERROR, "Data stack overflow in SALLOC");
    dumpstate(vm);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ExVM::Interpreter::doSFREE(ExVM::Interpreter* vm, uint16 op UNUSED) {
  uint8* last = vm->gpr[_RD(op)].pU8();
  if (last < vm->dataStackBase) {
    vm->status = VMDefs::DATA_STACK_UNDERFLOW;
    debuglog(LOG_ERROR, "Data stack underflow in SFREE");
    dumpstate(vm);
  } else if (last >= vm->dataStackTop) {
    vm->status = VMDefs::DATA_STACK_OVERFLOW;
    debuglog(LOG_ERROR, "Data stack overflow in SFREE");
    dumpstate(vm);
  } else {
    vm->dataStack.u8 = last;
  }
}
