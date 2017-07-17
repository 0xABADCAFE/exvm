//****************************************************************************//
//**                                                                        **//
//** File:         machine.cpp                                              **//
//** Description:  Support class definitions                                **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2001-08-29                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

#include "include/machine.hpp"

using namespace ExVM;

#if (_VM_HOST_OS == _VM_HOST_LINUX_I386) || (_VM_HOST_OS == _VM_HOST_LINUX_X64)
  #include "include/platforms/machine_linux_generic_impl.hpp"
#elif _VM_HOST_OS == _VM_HOST_WIN32_I386
  #include "include/platforms/machine_win32_impl.hpp"
#elif (_VM_HOST_OS == _VM_HOST_AMIGAOS3_68K)
  #include "include/platforms/machine_amiga_68k_impl.hpp"
#elif (_VM_HOST_OS == _VM_HOST_AMIGAOS3_WARPUP)
  #include "include/platforms/machine_amiga_wos_impl.hpp"
#elif (_VM_HOST_OS == _VM_HOST_AMIGAOS4_PPC)
  #include "include/platforms/machine_amiga_os4_impl.hpp"
#endif

