//****************************************************************************//
//**                                                                        **//
//** File:         vm_interpreter_custom_amiga_68k.hpp                      **//
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

#include <exec/tasks.h>
#include <clib/exec_protos.h>

extern "C" {
  uint32 trap_68K();
}

