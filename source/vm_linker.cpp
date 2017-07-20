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

class Linker::SymbolResolver : private SymbolEnumerator {
  public:

    int length() const { return SymbolEnumerator::length(); }

    int addSymbol(const char* symbol, const void* addr);

    SymbolResolver(uint32 iniSize) : SymbolEnumerator(iniSize) {
      debuglog(LOG_DEBUG, "Created Linker::SymbolResolver");
    }

    ~SymbolResolver() {
      debuglog(LOG_DEBUG, "Destroyed Linker::SymbolResolver");
    }

};

int Linker::SymbolResolver::addSymbol(const char* symbol, const void* addr) {
  return SymbolEnumerator::add(symbol);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Constructor
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Linker::Linker() : codeSymbolResolver(0), nativeCodeSymbolResolver(0), dataSymbolResolver(0)
{
  debuglog(LOG_DEBUG, "Created Linker");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Linker::~Linker() {
  if (codeSymbolResolver) {
    delete codeSymbolResolver;
  }
  if (nativeCodeSymbolResolver) {
    delete nativeCodeSymbolResolver;
  }
  if (dataSymbolResolver) {
    delete dataSymbolResolver;
  }
  debuglog(LOG_DEBUG, "Destroyed Linker");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Linker::addSymbol(SymbolResolver*& resolver, const char* symbol, const void* addr) {
  if (!symbol) {
    debuglog(LOG_ERROR, "NULL symbol passed to %s()", __FUNCTION__);
    return Error::ILLEGAL_ARGUMENT;
  }
  if (!addr) {
    debuglog(LOG_ERROR, "NULL symbol address passed to %s()", __FUNCTION__);
    return Error::ILLEGAL_SYMBOL_ADDRESS;
  }

  // Check #1 make sure the SymbolResolver exists
  if (
    !resolver &&
    !(resolver = new(std::nothrow)SymbolResolver(INI_TABLE_SIZE))
  ) {
    debuglog(LOG_ERROR, "Unable to allocate SymbolResolver");
    return Error::OUT_OF_MEMORY;
  }

  resolver->addSymbol(symbol, addr);

  debuglog(LOG_INFO, "SymbolResolver has %d entries", resolver->length());
  return Error::SUCCESS;
}

