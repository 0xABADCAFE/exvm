//****************************************************************************//
//**                                                                        **//
//** File:         vm_symbol.cpp                                            **//
//** Description:  VMSynbol class definition                                **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2017-07-12                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

#include <cstdio>

#include "include/vm_linker.hpp"

using ExVM::Linker;

int main() {

  Linker testLinker;
  testLinker.registerNative(0, 0);
  return 0;
}

