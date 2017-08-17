//****************************************************************************//
//**                                                                        **//
//** File:         op_vector_table.cpp                                      **//
//** Description:  Function Table build model                               **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2017-08-17                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

#include "include/machine.hpp"

#if _VM_INTERPRETER == _VM_INTERPRETER_FUNC_TABLE
  #include "include/vm_core.hpp"
  #include <cstdio>

  #include "include/vm_interpreter_func_table.hpp"
using namespace ExVM;

// vector instruction set

const Interpreter::Handler Interpreter::vectorHandlers[256] = {
  _REFER_OP(ILLEGAL)
};

#endif
