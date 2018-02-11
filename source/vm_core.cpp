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
//
// Base Interpreter
//
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

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Interpreter::~Interpreter() {
  delete[] callStackBase;
  delete[] dataStackBase;
  delete[] regStackBase;
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
//
// StandardInterpreter
//
// Represents the core interpreter for the virtual machine and is primarily responsible for the runtime execution of
// virtual code.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "include/vm_interpreter_standard.hpp"

StandardInterpreter::StandardInterpreter(size_t rStackSize, size_t dStackSize, size_t cStackSize) :
Interpreter(rStackSize, dStackSize, cStackSize) {

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

StandardInterpreter::~StandardInterpreter() {

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void StandardInterpreter::dump() {

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void StandardInterpreter::execute() {

  status = VMDefs::RUNNING;

#define CLASS StandardInterpreter
#define COUNT_STATEMENTS ;
#define DEBUG_RETURN
#define DEBUG_BRANCH_UNCONDITIONAL
#define DEBUG_BRANCH_TAKEN
#define DEBUG_BRANCH_NOT_TAKEN

#if _VM_INTERPRETER == _VM_INTERPRETER_SWITCH_CASE
  #include "include/vm_interpreter_switch_case_impl.hpp"
#elif _VM_INTERPRETER == _VM_INTERPRETER_CUSTOM
  #include "include/vm_interpreter_custom_impl.hpp"
#endif

#undef CLASS
#undef COUNT_STATEMENTS
#undef DEBUG_RETURN
#undef DEBUG_BRANCH_UNCONDITIONAL
#undef DEBUG_BRANCH_TAKEN
#undef DEBUG_BRANCH_NOT_TAKEN
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// DebuggingInterpreter
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "include/vm_interpreter_debugging.hpp"

const char* DebuggingInterpreter::statusCodes[] = {
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

DebuggingInterpreter::DebuggingInterpreter(size_t rStackSize, size_t dStackSize, size_t cStackSize) :
Interpreter(rStackSize, dStackSize, cStackSize), debugFlags(0xFFFFFFFF) {
  debuglog(LOG_INFO, "VM compiled %d-bit native, gpr alignment is %d bytes", X_PTRSIZE, (int)(8 - (((long)gpr) & 7)) );
  debuglog(LOG_INFO, "There are presently %d scalar, %d advanced and %d stream instructions defined", VMDefs::MAX_OP, VMDefs::MAX_ADV, VMDefs::MAX_VEC);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DebuggingInterpreter::~DebuggingInterpreter() {
  debuglog(LOG_INFO, "Destroyed Interpreter");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void DebuggingInterpreter::dump() {
  std::printf("DebuggingInterpreter dump\n\n");
  std::printf("rX: %18s : %12s : %6s : %4s : c\n",
    "64-bit (hex dump)",
    "s32",
    "s16",
    "s8"
  );
  for (int i = 0; i < NUM_GPR; i++) {
    std::printf("%2d: 0x%08X%08X : %12d : %6d : %4d : %c : %.8f\n", i,
      (unsigned)gpr[i].getMSW(), (unsigned)gpr[i].getLSW(),
      (int)gpr[i].s32(),
      (int)gpr[i].s16(),
      (int)gpr[i].s8(),
      (int)((gpr[i].u8()>32 && gpr[i].u8() < 127) ? gpr[i].u8() : '.'),
      gpr[i].f32()
    );
  }
#if X_PTRSIZE == XA_PTRSIZE64
  std::printf("PC: %p\n",             pc.inst);
  std::printf("RS: %p (%td)\n",       regStack, (regStack-regStackBase));
  std::printf("DS: %p (%td)\n",       dataStack.u8, (dataStack.u8-dataStackBase));
  std::printf("CS: %p (%td)\n",       callStack, (callStack-callStackBase));
  std::printf("ST: 0x%08X (%s)\n\n",  (unsigned)status, statusCodes[status]);
#else
  std::printf("PC: 0x%08X\n",         (unsigned)pc.inst);
  std::printf("RS: 0x%08X (%d)\n",    (unsigned)regStack, (regStack-regStackBase));
  std::printf("DS: 0x%08X (%d)\n",    (unsigned)dataStack.u8, (dataStack.u8-dataStackBase));
  std::printf("CS: 0x%08X (%d)\n",    (unsigned)callStack, (callStack-callStackBase));
  std::printf("ST: 0x%08X (%s)\n\n",  (unsigned)status, statusCodes[status]);
#endif
  std::puts("Stats Collected:");
  std::printf(
    "\tInstructions Executed: %" FU64 "\n",
    totalStatements
  );
  std::printf(
    "\tFunction Calls : %" FU32 "\n"
    "\t   Normal (sym): %" FU32 "\n"
    "\t   Local (anon): %" FU32 "\n"
    "\t   Native      : %" FU32 "\n",
    (functionCalls + nativeFunctionCalls + branchCalls),
    functionCalls,
    branchCalls,
    nativeFunctionCalls
  );

  std::printf(
    "\tBranches         : %" FU32 "\n"
    "\t   Unconditional : %" FU32 "\n"
    "\t   Taken         : %" FU32 "\n"
    "\t   Not Taken     : %" FU32 "\n",
    (unconditionalBranches + conditionalBranchesTaken + conditionalBranchesNotTaken),
    unconditionalBranches,
    conditionalBranchesTaken,
    conditionalBranchesNotTaken
  );

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void DebuggingInterpreter::execute() {
  MilliClock total;
#if X_PTRSIZE == XA_PTRSIZE64
  uint64 numStatements        = 0;
  #define FCNT FU64
#else
  uint32 numStatements        = 0;
  #define FCNT FU32
#endif
  totalTime                   = 0;
  nativeTime                  = 0;
  functionCalls               = 0;
  nativeFunctionCalls         = 0;
  branchCalls                 = 0;
  conditionalBranchesTaken    = 0;
  conditionalBranchesNotTaken = 0;
  unconditionalBranches       = 0;
  status                      = VMDefs::RUNNING;

#define CLASS DebuggingInterpreter
#define COUNT_STATEMENTS ++numStatements;
#define DEBUG_RETURN if (vm->debugFlags & FLAG_LOG_CALLS) { debuglog(LOG_INFO, "Returning"); }
#define DEBUG_BRANCH_UNCONDITIONAL ++unconditionalBranches;
#define DEBUG_BRANCH_TAKEN         ++conditionalBranchesTaken;
#define DEBUG_BRANCH_NOT_TAKEN     else { ++conditionalBranchesNotTaken; }

#if _VM_INTERPRETER == _VM_INTERPRETER_SWITCH_CASE
  #include "include/vm_interpreter_switch_case_impl.hpp"
#elif _VM_INTERPRETER == _VM_INTERPRETER_CUSTOM
  #include "include/vm_interpreter_custom_impl.hpp"
#endif

#undef CLASS
#undef COUNT_STATEMENTS
#undef DEBUG_RETURN

  totalTime = total.elapsedFrac();
  totalStatements     = numStatements;
  debuglog(LOG_INFO, "Executed %" FCNT " statements\n", numStatements);
  float64 virtualTime = totalTime - nativeTime;
  float64 mips        = (0.001*numStatements)/virtualTime;
  debuglog(
    LOG_INFO,
    "Total: %.3f ms, native: %.3f ms, virtual: %.3f ms, %.3f MIPS",
    totalTime, nativeTime, virtualTime, mips
  );

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Interpreter* Interpreter::create(Interpreter::Type type, size_t rStackSize, size_t dStackSize, size_t cStackSize) {
  switch (type) {
    case TYPE_DEBUGGING:
      return new(nothrow) DebuggingInterpreter(rStackSize, dStackSize, cStackSize);
    default:
      return new(nothrow) StandardInterpreter(rStackSize, dStackSize, cStackSize);
  }
}

