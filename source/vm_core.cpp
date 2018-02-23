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
#include <cstring>
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

void Interpreter::setExecutable(Executable* executable) {
  setNativeCodeSymbolTable(executable->nativeCodeAddresses, executable->nativeCodeCount);
  setCodeSymbolTable(executable->codeAddresses, executable->codeCount);
  setDataSymbolTable(executable->dataAddresses, executable->dataCount);
  setPC(executable->codeAddresses[executable->main]);
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
#define DEBUG_SCALAR_COUNT ;

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
#undef DEBUG_SCALAR_COUNT

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "include/vm_interpreter_debugging.hpp"

Interpreter* Interpreter::create(Interpreter::Type type, size_t rStackSize, size_t dStackSize, size_t cStackSize) {
  switch (type) {
    case TYPE_DEBUGGING:
      return new(nothrow) DebuggingInterpreter(rStackSize, dStackSize, cStackSize);
    default:
      return new(nothrow) StandardInterpreter(rStackSize, dStackSize, cStackSize);
  }
}

