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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// VMCore
//
// Represents the core interpreter for the virtual machine and is primarily responsible for the runtime execution of
// virtual code.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class VMCore {
  public:
    enum {
      NUM_GPR         = 16,   // Number of general purpose registers
      DEF_REG_STACK   = 1024, // Default register save/restore stack size, in entries
      DEF_DATA_STACK  = 4096, // Default data stack size, in bytes
      DEF_CALL_STACK  = 4096  // Default call stack size, in entries
    };

    typedef void (*Native)(VMCore* vm);

    #include "vm_gpr.hpp"

  private:
    GPR       gpr[VMCore::NUM_GPR];    // register set

    union {
      const uint16*         inst;   // normal interpretation
      const uint8*          extU8;
      const uint16*         extU16;
      const uint32*         extU32;
      const uint64*         extU64;
      const sint8*          extS8;
      const sint16*         extS16;
      const sint32*         extS32;
      const sint64*         extS64;
      const uint16* const * extCodeAddr;
      const Native* const * extNativeCodeAddr;
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

    Native*   nativeCodeSymbol;
    uint16**  codeSymbol;  
    void**    dataSymbol;

    uint32    status;

    size_t    regStackSize;
    size_t    dataStackSize;
    size_t    callStackSize;
    
    float64   totalTime;
    float64   nativeTime;

    uint16    nativeCodeSymbolCount;
    uint16    codeSymbolCount;
    uint16    dataSymbolCount;

    #if _VM_INTERPRETER == _VM_INTERPRETER_FUNC_TABLE
      #include "vm_handlers.hpp"
    #endif
    static const char* statusCodes[];

  public:

    VMCore(size_t rStackSize = DEF_REG_STACK, size_t dStackSize = DEF_DATA_STACK, size_t cStackSize = DEF_CALL_STACK);
    ~VMCore();

    uint32  getStatus() const {
      return status;
    }

  public:
 
    void setNativeCodeSymbolTable(Native* symbol, uint16 count);
    void setCodeSymbolTable(uint16** symbol, uint16 count);
    void setDataSymbolTable(void** symbol, uint16 count);

    GPR& getReg(sint32 i) {
      return gpr[(i & 0xF)];
    }

    void setPC(uint16* newPC) {
      pc.inst = newPC;
    }

    void dump();

    void execute();
    
};

#endif
