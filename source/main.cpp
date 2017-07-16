//****************************************************************************//
//**                                                                        **//
//** File:         main.cpp                                                 **//
//** Description:  Test Application                                         **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2001-08-29                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//


#include <new>
#include <cstdio>
#include <cstdlib>
#include "include/vm_core.hpp"
#include "include/vm_inline.hpp"
#include "include/vm_codemacros.hpp"

using namespace std;

////////////////////////////////////////////////////////////////////////////////

_VM_EXTERN(virtualProgram);

extern void runTestExample();

int main() {
  runTestExample();
  return 0;
}
