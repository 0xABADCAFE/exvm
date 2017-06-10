//****************************************************************************//
//**                                                                        **//
//** File:         op_store.cpp                                             **//
//** Description:  Store group opcode implementation                        **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2001-08-29                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

#include "machine.hpp"

#if _VM_INTERPRETER == _VM_INTERPRETER_FUNC_TABLE
  #include "vmcore.hpp"
  #include "vminline.hpp"
  #include <cstdio>

// Upon entry, the pc points to the 16-bit word following the current opcode.
// Normally, this would be the address of the next opcode. Handlers that use
// extension words must ensure that they increment the pc so that it points
// to the next opcode.

// Arguments:
// vm is a pointer to the VMCore instance
// op is the current opcode word

  #include "op_store_code.hpp"

#endif
