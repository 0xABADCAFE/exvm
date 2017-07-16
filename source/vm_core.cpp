//****************************************************************************//
//**                                                                        **//
//** File:         vm_core.cpp                                              **//
//** Description:  VMCore class definition                                  **//
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
#include "include/vminline.hpp"
#include <new>

#if _VM_INTERPRETER == _VM_INTERPRETER_FUNC_TABLE
  #include "include/vm_interpreter_func_table.hpp"
#elif _VM_INTERPRETER == _VM_INTERPRETER_SWITCH_CASE
  #include "include/vm_interpreter_switch_case.hpp"
#elif _VM_INTERPRETER == _VM_INTERPRETER_CUSTOM
  #include "include/vm_interpreter_custom.hpp"
#endif

using std::nothrow;

const char* VMCore::statusCodes[] = {
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

////////////////////////////////////////////////////////////////////////////////

VMCore::VMCore(size_t rStackSize, size_t dStackSize, size_t cStackSize) :
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

  printf("VM compiled %d-bit native\n", X_PTRSIZE);
  printf("There are presently %d core instructions defined\n", VMDefs::MAX_OP);

/*
  printf("sizeof (VMDefs) = %zd\n", sizeof(VMDefs));
  printf("sizeof (VMCore) = %zd\n", sizeof(VMCore));
  printf("There are presently %d core instructions defined\n", VMDefs::MAX_OP);
  printf("Constructed VMCore:\nreg Stack %zd entries\ndataStack %zd bytes\ncallStack %zd levels\n", regStackSize, dataStackSize, callStackSize);
*/
}

////////////////////////////////////////////////////////////////////////////////

VMCore::~VMCore() {
  delete[] callStackBase;
  delete[] dataStackBase;
  delete[] regStackBase;
  printf("Destroyed VMCore\n");
}

////////////////////////////////////////////////////////////////////////////////

void VMCore::dump() {
  printf("VMCore dump\n\n");
  printf("rX: %18s : %12s : %6s : %4s : c\n",
    "64-bit (hex dump)",
    "s32",
    "s16",
    "s8"
  );
  for (int i = 0; i < NUM_GPR; i++) {
    printf("%2d: 0x%08X%08X : %12d : %6d : %4d : %c : %.8f\n", i,
      (unsigned)gpr[i].getMSW(), (unsigned)gpr[i].getLSW(),
      gpr[i].s32(),
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

////////////////////////////////////////////////////////////////////////////////

void VMCore::setNativeCodeSymbolTable(Native* symbol, uint16 count) {
  nativeCodeSymbol      = symbol;
  nativeCodeSymbolCount = count;

  printf("Native Code Symbols : %p [%d]\n", symbol, (int)count);
}

void VMCore::setCodeSymbolTable(uint16** symbol, uint16 count) {
  codeSymbol      = symbol;
  codeSymbolCount = count;

  printf("Code Symbols : %p [%d]\n", symbol, (int)count);
}

void VMCore::setDataSymbolTable(void** symbol, uint16 count) {
  dataSymbol      = symbol;
  dataSymbolCount = count;

  printf("Data Symbols : %p [%d]\n", symbol, (int)count);
}

////////////////////////////////////////////////////////////////////////////////

void VMCore::execute() {
  MilliClock total;
  int numStatements = 0;
  totalTime         = 0;
  nativeTime        = 0;
  status            = VMDefs::RUNNING;

#if _VM_INTERPRETER == _VM_INTERPRETER_FUNC_TABLE
  #include "include/vm_interpreter_func_table_impl.hpp"
#elif _VM_INTERPRETER == _VM_INTERPRETER_SWITCH_CASE
  #include "include/vm_interpreter_switch_case_impl.hpp"
#elif _VM_INTERPRETER == _VM_INTERPRETER_CUSTOM
  #include "include/vm_interpreter_custom_impl.hpp"
#endif

  totalTime = total.elapsedFrac();
  printf("Executed %d statements\n", numStatements);
  float64 virtualTime = totalTime - nativeTime;
  float64 mips        = (0.001*numStatements)/virtualTime;
  printf(
    "Total: %.3f ms, native: %.3f ms, virtual: %.3f ms, %.3f MIPs\n",
    totalTime, nativeTime, virtualTime, mips
  );

}

