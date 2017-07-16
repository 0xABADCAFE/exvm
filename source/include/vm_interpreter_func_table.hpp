//****************************************************************************//
//**                                                                        **//
//** File:         vm_interpreter_func_table.hpp                            **//
//** Description:  Host Machine definitions                                 **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2001-08-29                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):      Stub replacement for needed exng/xbase.hpp defs          **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

#ifndef _VM_INTERPRETER_FUNC_TABLE_HPP_
  #define _VM_INTERPRETER_FUNC_TABLE_HPP_
  #define _DECLARE_OP(x)  static void do##x(VMCore*, uint16);
  #define _DEFINE_OP(x)   void VMCore::do##x(VMCore* vm, uint16 op)
  #define _REFER_OP(x)    VMCore::do##x
  #define _END_OP
  #define _THROW(x) return;
#endif
