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

#define VM_FULL_DEBUG

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ExVM Namespace
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ExVM {

  // Runtime execution engine
  class Interpreter;

  // Loading and Linking
  class SymbolEnumerator;
  class Linker;

  // Host provided function call
  typedef void (*NativeCall)(Interpreter* vm);


  // types:
  // .s8, .s16, .s32, .s64 - signed integer
  // .u8, .u16, .u32, .u64 - unsigned integer
  // .f32, .f64            - float
  // .i                    - any integer type
  // .f                    - any float type
  // .a                    - any arithmetic type

  // .8, .16, .32, .64     - size only (untyped)
  // .x                    - any operand

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
  };

}
#endif
