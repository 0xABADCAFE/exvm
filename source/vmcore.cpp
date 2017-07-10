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
#include "vmcore.hpp"
#include "vminline.hpp"
#include <new>

#if (_VM_HOST_OS == _VM_HOST_AMIGAOS3_68K) && (_VM_INTERPRETER == _VM_INTERPRETER_CUSTOM)
#include <exec/tasks.h>
#include <clib/exec_protos.h>

extern "C" {
  uint32 trap_68K();
}

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
  "Call empty native address"
};

VMCore::VMCore(size_t rStackSize, size_t dStackSize, size_t cStackSize) :
  regStackSize(rStackSize),
  dataStackSize(dStackSize),
  callStackSize(cStackSize) {
  pc.inst       = 0;
  regStack     = regStackBase  = new(nothrow) uint64   [regStackSize];
  dataStack.u8 = dataStackBase = new(nothrow) uint8    [dataStackSize];
  callStack    = callStackBase = new(nothrow) uint16*  [callStackSize];
  regStackTop  = regStackBase  ? regStackBase  + regStackSize  : 0;
  dataStackTop = dataStackBase ? dataStackBase + dataStackSize : 0;
  callStackTop = callStackBase ? callStackBase + callStackSize : 0;
  for (int i = 0; i < NUM_GPR; i++) {
    gpr[i].u64() = 0;
  }

#if _VM_INTERPRETER == _VM_INTERPRETER_FUNC_TABLE
  currHandler = normal;
#else
  //currHandler = 0;
#endif

  printf("VM compiled %d-bit native\n", X_PTRSIZE);
  printf("There are presently %d core instructions defined\n", VMDefs::MAX_OP);

/*
  printf("sizeof (VMDefs) = %zd\n", sizeof(VMDefs));
  printf("sizeof (VMCore) = %zd\n", sizeof(VMCore));
  printf("There are presently %d core instructions defined\n", VMDefs::MAX_OP);
  printf("Constructed VMCore:\nreg Stack %zd entries\ndataStack %zd bytes\ncallStack %zd levels\n", regStackSize, dataStackSize, callStackSize);
*/
}

VMCore::~VMCore() {
  delete[] callStackBase;
  delete[] dataStackBase;
  delete[] regStackBase;
  printf("Destroyed VMCore\n");
}

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
#if _VM_INTERPRETER == _VM_INTERPRETER_FUNC_TABLE
  printf("HT: 0x%08X\n",  (unsigned)currHandler);
#endif
  printf("PC: 0x%08X\n",         (unsigned)pc.inst);
  printf("RS: 0x%08X (%d)\n",    (unsigned)regStack, (regStack-regStackBase));
  printf("DS: 0x%08X (%d)\n",    (unsigned)dataStack.u8, (dataStack.u8-dataStackBase));
  printf("CS: 0x%08X (%d)\n",    (unsigned)callStack, (callStack-callStackBase));
  printf("ST: 0x%08X (%s)\n\n",  (unsigned)status, statusCodes[status]);
#endif

}

#if _VM_INTERPRETER == _VM_INTERPRETER_SWITCH_CASE
  #include <cmath>

int VMCore::innerExecute() {
  int numStatements   = 0;
  register VMCore* vm = this;
  register uint16  op;

forever:
  op = *pc.inst++;
  switch (op>>8) {
    #include "op_control_code.hpp"
    #include "op_load_code.hpp"
    #include "op_store_code.hpp"
    #include "op_move_code.hpp"
    #include "op_jump_code.hpp"
    #include "op_convert_code.hpp"
    #include "op_arithmetic_code.hpp"
    #include "op_logic_code.hpp"
    default:
      printf("No handler yet defined for opcode 0x%04X\n", (unsigned)op);
        status = VMDefs::BREAKPOINT;
        return ++numStatements;
    }
    ++numStatements;
  goto forever;

  // We can't get here, but the compiler needs to see it
  return numStatements;
}

#endif

void VMCore::execute() {
  int numStatements = 0;
  totalTime         = 0;
  nativeTime        = 0;
  status            = VMDefs::RUNNING;

#if _VM_INTERPRETER == _VM_INTERPRETER_FUNC_TABLE

  MilliClock total;
  // simple model, no exception based return, check status after each instruction
  while (status==VMDefs::RUNNING) {
    register const Handler* h = currHandler; // temp pointer;
    while (status == VMDefs::RUNNING) {
      uint16 op = *pc.inst++;
      h[(op>>8)](this, op);
      ++numStatements;
    }
  }
  totalTime = total.elapsedFrac();

#elif _VM_INTERPRETER == _VM_INTERPRETER_SWITCH_CASE

  MilliClock total;
  numStatements = innerExecute();
  totalTime     = total.elapsedFrac();

#elif _VM_INTERPRETER == _VM_INTERPRETER_CUSTOM

  // assembler model, so far only the 68K has this
  #if _VM_HOST_OS == _VM_HOST_AMIGAOS3_68K

  // set up CPU trap handling, written in asm
  Task* thisTask         = FindTask(0);
  void* old68KTrap       = thisTask->tc_TrapCode;
  thisTask->tc_TrapCode  = (void*)(&trap_68K);

  MilliClock total;
  // jump into the asm execute code
  asm(
    "\n/*************************************/\n\n"
    "\tmove.l %0, a0\n"
    "\tjsr _execute_68K\n"
    "\n/*************************************/\n\n"
    :                                 // no outputs
    : "g"(this)                       // inputs
    : "d0", "d1", "a0", "a1","cc"     // clobbers
  );
  totalTime = total.elapsedFrac();

  // reset the trap code to whatever it was previously
  thisTask->tc_TrapCode = old68KTrap;

  #else // not 68K amigaos?
    #error Only the 680x0 target currently supports custom implementation
  #endif
#endif

  printf("Executed %d statements\n", numStatements);
  float64 virtualTime = totalTime - nativeTime;
  float64 mips        = (0.001*numStatements)/virtualTime;
  printf(
    "Total: %.3f ms, native: %.3f ms, virtual: %.3f ms, %.3f MIPs\n",
    totalTime, nativeTime, virtualTime, mips
  );

}

