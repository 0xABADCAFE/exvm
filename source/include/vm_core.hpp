//****************************************************************************//
//**                                                                        **//
//** File:         vm_core.hpp                                              **//
//** Description:  Virtual Machine Core definitions                         **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2001-08-29                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

#ifndef _VM_CORE_HPP_
#define _VM_CORE_HPP_
#include "vm.hpp"
#include "vm_targetmacros.hpp"

namespace ExVM {

  struct Executable;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Interpreter
//
// Represents the core interpreter for the virtual machine and is primarily responsible for the runtime execution of
// virtual code.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  class FunctionalTest;
  class Interpreter {

    friend ExVM::FunctionalTest;

    public:
      enum {
        NUM_GPR         = 16,   // Number of general purpose registers
        GPR_FIRST       = 0,
        GPR_LAST        = NUM_GPR - 1,
        DEF_REG_STACK   = 1024, // Default register save/restore stack size, in entries
        DEF_DATA_STACK  = 4096, // Default data stack size, in bytes
        DEF_CALL_STACK  = 4096  // Default call stack size, in entries
      };

      #include "vm_gpr.hpp"

    protected:
      #if X_PTRSIZE == XA_PTRSIZE32
      void* padding;
      #endif
      GPR gpr[Interpreter::NUM_GPR];    // register set

      union {
        const uint16*  inst;   // normal interpretation
        const uint8*   extU8;
        const uint16*  extU16;
        const uint32*  extU32;
        const sint8*   extS8;
        const sint16*  extS16;
        const sint32*  extS32;
        const float32* extF32;
      } pc;         // program counter

      uint16**  callStack;  // return address stack
      uint64*   regStack;   // register save/restore stack
      union {
        uint8*  u8;
        uint16* u16;
        uint32* u32;
        uint64* u64;
      } dataStack;  // general data stack

      uint16**  callStackBase;
      uint64*   regStackBase;
      uint8*    dataStackBase;

      uint16**  callStackTop;
      uint64*   regStackTop;
      uint8*    dataStackTop;

      NativeCall* nativeCodeSymbol;
      uint16**    codeSymbol;
      void**      dataSymbol;
      uint32      status;

      size_t  regStackSize;
      size_t  dataStackSize;
      size_t  callStackSize;

      float64 totalTime;
      float64 nativeTime;

      uint32  nativeCodeSymbolCount;
      uint32  codeSymbolCount;
      uint32  dataSymbolCount;

      static const char* statusCodes[];

    public:

      Interpreter(size_t rStackSize, size_t dStackSize, size_t cStackSize);
      virtual ~Interpreter();

      uint32  getStatus() const {
        return status;
      }

      GPR&    getReg(sint32 i) {
        return gpr[(i & 0xF)];
      }

      void setNativeCodeSymbolTable(NativeCall* symbol, uint32 count);
      void setCodeSymbolTable(uint16** symbol, uint32 count);
      void setDataSymbolTable(void** symbol, uint32 count);
      void setExecutable(Executable* executable);
      void setPC(uint16* newPC) {
        pc.inst = newPC;
      }

      virtual void execute() = 0;
  };

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// StandardInterpreter
//
// Represents the core interpreter for the virtual machine and is primarily responsible for the runtime execution of
// virtual code.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  class StandardInterpreter : public Interpreter {

    friend ExVM::FunctionalTest;

    public:
      StandardInterpreter(size_t rStackSize = DEF_REG_STACK, size_t dStackSize = DEF_DATA_STACK, size_t cStackSize = DEF_CALL_STACK);
      ~StandardInterpreter();

      void dump();
      void execute();

    private:
      // Specific handler functions for opcodes that require more than a couple of inline statements
      static void doBCALL8(StandardInterpreter* vm, uint16 op);
      static void doBCALL16(StandardInterpreter* vm, uint16 op);
      static void doCALL(StandardInterpreter* vm, uint16 op);
      static void doCALLN(StandardInterpreter* vm, uint16 op);
      static void doICALL(StandardInterpreter* vm, uint16 op);
      static void doICALLN(StandardInterpreter* vm, uint16 op);
      static void doSV(StandardInterpreter* vn, uint16 op);
      static void doRS(StandardInterpreter* vn, uint16 op);
      static void doPUSH_8(StandardInterpreter* vm, uint16 op);
      static void doPUSH_16(StandardInterpreter* vm, uint16 op);
      static void doPUSH_32(StandardInterpreter* vm, uint16 op);
      static void doPUSH_64(StandardInterpreter* vm, uint16 op);
      static void doPOP_8(StandardInterpreter* vm, uint16 op);
      static void doPOP_16(StandardInterpreter* vm, uint16 op);
      static void doPOP_32(StandardInterpreter* vm, uint16 op);
      static void doPOP_64(StandardInterpreter* vm, uint16 op);
      static void doSALLOC(StandardInterpreter* vm, uint16 op);
      static void doSFREE(StandardInterpreter* vm, uint16 op);
      static void doVEC1(StandardInterpreter* vm, uint16 op);
      static void doADV(StandardInterpreter* vm, uint16 op);
  };
/*
  class DebuggingInterpreter : public Interpreter {
  };
*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Executable
//
// Represents the runtime linked and ready to execute VM program.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  struct Executable {
    NativeCall* nativeCodeAddresses;
    uint16**    codeAddresses;
    void**      dataAddresses;
    uint32      nativeCodeCount;
    uint32      codeCount;
    uint32      dataCount;
    uint32      main;

    static Executable* allocate(uint32 nativeCount, uint32 codeCount, uint32 dataCount);
    static void release(Executable* executable);
  };

  inline void Interpreter::setExecutable(Executable* executable) {
    setNativeCodeSymbolTable(executable->nativeCodeAddresses, executable->nativeCodeCount);
    setCodeSymbolTable(executable->codeAddresses, executable->codeCount);
    setDataSymbolTable(executable->dataAddresses, executable->dataCount);
    setPC(executable->codeAddresses[executable->main]);
  }
}
#endif
