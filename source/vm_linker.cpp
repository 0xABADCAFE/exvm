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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Linker Constructor
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Linker::Linker() : codeSymbols(0), nativeCodeSymbols(0), dataSymbols(0)
{
  debuglog(LOG_DEBUG, "Created Linker");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Linker Destructor
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Linker::~Linker() {
  if (codeSymbols) {
    delete codeSymbols;
  }
  if (nativeCodeSymbols) {
    delete nativeCodeSymbols;
  }
  if (dataSymbols) {
    delete dataSymbols;
  }

  debuglog(LOG_DEBUG, "Destroyed Linker");
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Linker Destructor
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Linker::defineSymbol(SymbolMap*& map, const char* name, const void* address) {

  // Check #1 make sure the SymbolMap exists
  if (
    !map &&
    !(map = new(std::nothrow)SymbolMap())
  ) {

    debuglog(LOG_ERROR, "Unable to allocate SymbolMap");

    return Error::OUT_OF_MEMORY;
  }

  return map->define(name, address);
}





