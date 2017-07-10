//****************************************************************************//
//**                                                                        **//
//** File:         vm_interpreter_switch_case.hpp                           **//
//** Description:  VMCore class definition                                  **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2001-08-29                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

#ifndef _VM_INTERPRETER_SWITCH_CASE_HPP_
  #define _VM_INTERPRETER_SWITCH_CASE_HPP_
  #include <cmath>

  #define _DECLARE_OP(x)
  #define _DEFINE_OP(x)   case VMDefs::_##x:
  #define _END_OP         break;
  #define _REFER_OP(x)
  #define _THROW(x)       goto interpreter_bailout;

#endif
