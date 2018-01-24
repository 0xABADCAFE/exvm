//****************************************************************************//
//**                                                                        **//
//** File:         vm_core.cpp                                              **//
//** Description:  Interpreter class definition                             **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2001-08-29                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

#include <cstdio>
#include "include/vm_core.hpp"
#include "include/vm_inline.hpp"
#include "include/vm_linker.hpp"
#include <new>

#if _VM_INTERPRETER == _VM_INTERPRETER_SWITCH_CASE
  #include "include/vm_interpreter_switch_case.hpp"
#elif _VM_INTERPRETER == _VM_INTERPRETER_CUSTOM
  #include "include/vm_interpreter_custom.hpp"
#endif

using std::nothrow;

using namespace ExVM;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char* Interpreter::statusCodes[] = {
  "Running",
  "Initialised",
  "Completed",
  "Breakpoint",
  "Change instruction set",
  "Illegal opcode",
  "Integer divide by zero",
  "Register stack overflow",
  "Register stack underflow",
  "Data stack overflow",
  "Data stack underflow",
  "Call stack overflow",
  "Call empty address",
  "Call empty native address",
  "Unknown code symbol",
  "Unknown data symbol",
  "Unknown native code symbol",
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Interpreter::Interpreter(size_t rStackSize, size_t dStackSize, size_t cStackSize) :
  regStackSize(rStackSize),
  dataStackSize(dStackSize),
  callStackSize(cStackSize) {
  pc.inst      = 0;
  regStack     = regStackBase  = new(nothrow) uint64   [regStackSize];
  dataStack.u8 = dataStackBase = new(nothrow) uint8    [dataStackSize];
  callStack    = callStackBase = new(nothrow) uint16*  [callStackSize];
  regStackTop  = regStackBase  ? regStackBase  + regStackSize  : 0;
  dataStackTop = dataStackBase ? dataStackBase + dataStackSize : 0;
  callStackTop = callStackBase ? callStackBase + callStackSize : 0;

  nativeCodeSymbol = 0;
  codeSymbol       = 0;
  dataSymbol       = 0;

  for (int i = 0; i < NUM_GPR; i++) {
    gpr[i].u64() = 0;
  }

  nativeCodeSymbolCount = 0;
  codeSymbolCount       = 0;
  dataSymbolCount       = 0;
  debuglog(LOG_INFO, "VM compiled %d-bit native, gpr alignment is %d bytes", X_PTRSIZE, (int)(8 - (((long)gpr) & 7)) );
  debuglog(LOG_INFO, "There are presently %d scalar, %d advanced and %d stream instructions defined", VMDefs::MAX_OP, VMDefs::MAX_ADV, VMDefs::MAX_VEC);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Interpreter::~Interpreter() {
  delete[] callStackBase;
  delete[] dataStackBase;
  delete[] regStackBase;
  debuglog(LOG_INFO, "Destroyed Interpreter");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Interpreter::dump() {
  printf("Interpreter dump\n\n");
  printf("rX: %18s : %12s : %6s : %4s : c\n",
    "64-bit (hex dump)",
    "s32",
    "s16",
    "s8"
  );
  for (int i = 0; i < NUM_GPR; i++) {
    printf("%2d: 0x%08X%08X : %12d : %6d : %4d : %c : %.8f\n", i,
      (unsigned)gpr[i].getMSW(), (unsigned)gpr[i].getLSW(),
      (int)gpr[i].s32(),
      (int)gpr[i].s16(),
      (int)gpr[i].s8(),
      (int)((gpr[i].u8()>32 && gpr[i].u8() < 127) ? gpr[i].u8() : '.'),
      gpr[i].f32()
    );
  }
#if X_PTRSIZE == XA_PTRSIZE64
  printf("PC: %p\n",             pc.inst);
  printf("RS: %p (%td)\n",       regStack, (regStack-regStackBase));
  printf("DS: %p (%td)\n",       dataStack.u8, (dataStack.u8-dataStackBase));
  printf("CS: %p (%td)\n",       callStack, (callStack-callStackBase));
  printf("ST: 0x%08X (%s)\n\n",  (unsigned)status, statusCodes[status]);
#else
  printf("PC: 0x%08X\n",         (unsigned)pc.inst);
  printf("RS: 0x%08X (%d)\n",    (unsigned)regStack, (regStack-regStackBase));
  printf("DS: 0x%08X (%d)\n",    (unsigned)dataStack.u8, (dataStack.u8-dataStackBase));
  printf("CS: 0x%08X (%d)\n",    (unsigned)callStack, (callStack-callStackBase));
  printf("ST: 0x%08X (%s)\n\n",  (unsigned)status, statusCodes[status]);
#endif

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Interpreter::setNativeCodeSymbolTable(NativeCall* symbol, uint32 count) {
  nativeCodeSymbol      = symbol;
  nativeCodeSymbolCount = count;
}

void Interpreter::setCodeSymbolTable(uint16** symbol, uint32 count) {
  codeSymbol      = symbol;
  codeSymbolCount = count;
}

void Interpreter::setDataSymbolTable(void** symbol, uint32 count) {
  dataSymbol      = symbol;
  dataSymbolCount = count;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Interpreter::execute() {
  MilliClock total;
#if X_PTRSIZE == XA_PTRSIZE64
  uint64 numStatements = 0;
  #define FCNT FU64
#else
  uint32 numStatements = 0;
  #define FCNT FU32
#endif
  totalTime            = 0;
  nativeTime           = 0;
  status               = VMDefs::RUNNING;

#if _VM_INTERPRETER == _VM_INTERPRETER_SWITCH_CASE
  #include "include/vm_interpreter_switch_case_impl.hpp"
#elif _VM_INTERPRETER == _VM_INTERPRETER_CUSTOM
  #include "include/vm_interpreter_custom_impl.hpp"
#endif

  totalTime = total.elapsedFrac();
  debuglog(LOG_INFO, "Executed %" FCNT " statements\n", numStatements);
  float64 virtualTime = totalTime - nativeTime;
  float64 mips        = (0.001*numStatements)/virtualTime;
  debuglog(
    LOG_INFO,
    "Total: %.3f ms, native: %.3f ms, virtual: %.3f ms, %.3f MIPS",
    totalTime, nativeTime, virtualTime, mips
  );

}


