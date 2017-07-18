//****************************************************************************//
//**                                                                        **//
//** File:         vm_debug.cpp                                             **//
//** Description:  Debugging definitions                                    **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2017-07-18                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

#include "include/vm.hpp"

#ifdef VM_DEBUG

const char* ExVM::debugLevel(uint32 level) {
  const char* errorLevels[] = {
    "ERR",
    "WRN",
    "INF",
    "DBG"
  };
  if (level < sizeof(errorLevels)/sizeof(const char*)) {
    return errorLevels[level];
  }
  return "---";
}

#endif
