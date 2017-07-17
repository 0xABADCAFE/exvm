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

struct Linker::Resolved {
  union {
    NativeCall    native;
    const uint16* func;
    const uint8*  data;
  };
  const char* symbol;
  int         symbolID;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Constructor
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Linker::Linker() :
  native(0),
  code(0),
  data(0),
  nativeEnumerator(0),
  codeEnumerator(0),
  dataEnumerator(0),
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Linker::registerNative(const char* symbol, NativeCall func) {
  return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Linker::registerCode(const char* symbol, const uint16* func) {
  return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Linker::registerData(const char* symbol, const void* data) {
  return 0;
}

