//****************************************************************************//
//**                                                                        **//
//** File:         vm.hpp                                                   **//
//** Description:  Virtual Machine definitions                              **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2001-08-14                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//


#ifndef _VM_DEFS_HPP_
#define _VM_DEFS_HPP_
#include "machine.hpp"

#define VM_DEBUG
#define VM_FULL_DEBUG
#define _VM_LOG_LEVEL 3

#define _VM_LOG_ERROR 0
#define _VM_LOG_WARN 1
#define _VM_LOG_INFO 2
#define _VM_LOG_DEBUG 3

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ExVM Namespace
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ExVM {

  #ifdef VM_DEBUG
    extern const char* debugLevel(uint32 level);
    #define debuglog(level, format, args...) if ( _VM_##level <= _VM_LOG_LEVEL) std::printf("[%s] %s() - " format "\n", debugLevel((uint32)(_VM_##level)), __FUNCTION__, ## args)
    #define dumpstate(v) (v)->dump()
  #else
    #define debuglog(level, format, args...)
    #define dumpstate(v)
  #endif

  // Runtime execution engine
  class Interpreter;

  // Loading and Linking
  class SymbolEnumerator;
  class Linker;

  // Host provided function call
  typedef void (*NativeCall)(Interpreter* vm);

  // Generic error codes
  class Error {
    public:
      enum {
        SUCCESS          = 0,
        ILLEGAL_ARGUMENT = -1,
        OUT_OF_MEMORY    = -2
      };
  };

  class VMDefs {
    public:

      #include "vm_opcodes.hpp"

      typedef enum {
        // bit masks used in multi-register transfers
        BITMASK_R0  = 0x0001,
        BITMASK_R1  = 0x0002,
        BITMASK_R2  = 0x0004,
        BITMASK_R3  = 0x0008,
        BITMASK_R4  = 0x0010,
        BITMASK_R5  = 0x0020,
        BITMASK_R6  = 0x0040,
        BITMASK_R7  = 0x0080,
        BITMASK_R8  = 0x0100,
        BITMASK_R9  = 0x0200,
        BITMASK_R10 = 0x0400,
        BITMASK_R11 = 0x0800,
        BITMASK_R12 = 0x1000,
        BITMASK_R13 = 0x2000,
        BITMASK_R14 = 0x4000,
        BITMASK_R15 = 0x8000
      } MultiRegMask;

      typedef enum {
        RUNNING = 0,
        INITIAL,
        COMPLETED,
        BREAKPOINT,
        ILLEGAL_OPCODE,
        ZERO_DIVIDE,
        REG_STACK_OVERFLOW,
        REG_STACK_UNDERFLOW,
        DATA_STACK_OVERFLOW,
        DATA_STACK_UNDERFLOW,
        CALL_STACK_OVERFLOW,
        CALL_EMPTY,
        CALL_EMPTY_NATIVE,
        UNKNOWN_CODE_SYMBOL,
        UNKNOWN_DATA_SYMBOL,
        UNKNOWN_NATIVE_CODE_SYMBOL,
      } VMStatus;

      enum {
        // Symbol sizes in bits
        DATA_SYMBOL_ID_SIZE   = 20,
        CODE_SYMBOL_ID_SIZE   = 20,
        NATIVE_SYMBOL_ID_SIZE = 20
      };
  };

}
#endif
