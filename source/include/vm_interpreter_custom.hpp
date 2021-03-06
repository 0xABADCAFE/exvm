//****************************************************************************//
//**                                                                        **//
//** File:         vm_custom_interpreter.hpp                                **//
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

#ifndef _VM_INTERPRETER_CUSTOM_HPP_
  #define _VM_INTERPRETER_CUSTOM_HPP_
  #if (_VM_HOST_OS == _VM_HOST_AMIGAOS3_68K)
    #include "platforms/vm_custom_interpreter_amiga_68k.hpp"
  #else
    #error No custom interpreter for the current target
  #endif

  /*
    #define _DECLARE_OP(x)
    #define _DEFINE_OP(x)
    #define _END_OP
    #define _REFER_OP(x)
    #define _HALT
  */
#endif

