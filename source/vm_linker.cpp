//****************************************************************************//
//**                                                                        **//
//** File:         vm_linker.cpp                                            **//
//** Description:  VMSLinker class definition                               **//
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

#include <new>

using namespace ExVM;

struct VMLinker::Resolved {
  union {
    NativeCall native,
    const uint16*  func,
    const uint8*   data;
  };
  const char* symbol;
  int         symbolID;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Constructor
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

VMLinker::VMLinker() :
  native(0),
  code(0)
  data(0)
{
  
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int VMLinker::registerNative(const char* symbol, NativeCall func) {
  return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int VMLinker::registerCode(const char* symbol, const uint16* func) {
  return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int VMLinker::registerData(const char* symbol, const void* data) {
  return 0;
}

