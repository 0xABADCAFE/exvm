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
  maxNative(INI_TABLE_SIZE),
  maxCode(INI_TABLE_SIZE),
  maxData(INI_TABLE_SIZE)
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Linker::~Linker() {
  if (nativeEnumerator) {
    delete nativeEnumerator;
  }
  if (codeEnumerator) {
    delete codeEnumerator;
  }
  if (dataEnumerator) {
    delete dataEnumerator;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Linker::registerNative(const char* symbol, NativeCall func) {
  if (!symbol || !func) {
    return Error::ILLEGAL_ARGUMENT;
  }
  checkEnumerator(nativeEnumerator);
  return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Linker::registerCode(const char* symbol, const uint16* func) {
  if (!symbol || !func) {
    return Error::ILLEGAL_ARGUMENT;
  }
  checkEnumerator(codeEnumerator);
  return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Linker::registerData(const char* symbol, const void* data) {
  if (!symbol || !data) {
    return Error::ILLEGAL_ARGUMENT;
  }
  checkEnumerator(dataEnumerator);
  return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Linker::checkEnumerator(SymbolEnumerator*& symbolEnumerator) {

  // Check #1 make sure the SynbolEnumerator exists
  if (
    !symbolEnumerator &&
    !(symbolEnumerator = new(std::nothrow)SymbolEnumerator(INI_TABLE_SIZE))
  ) {
    return Error::OUT_OF_MEMORY;
  }

  return Error::SUCCESS;
}

