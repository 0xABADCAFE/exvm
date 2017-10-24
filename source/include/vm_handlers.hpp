//****************************************************************************//
//**                                                                        **//
//** File:         vm_handlers.hpp                                          **//
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
#error vmhandlers.hpp must not be included manually!
#endif
#define _DECLARE_OP(x)  static void do##x(ExVM::Interpreter*, uint16);

typedef void (*Handler)(Interpreter*, uint16);

#include "opcodes/scalar/jump_table_defs.hpp"
#include "opcodes/advanced/jump_table_defs.hpp"
#include "opcodes/vector/jump_table_defs.hpp"

