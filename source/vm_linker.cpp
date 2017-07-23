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
// Linker::SymbolMap
//
// Implements an automatically enumerated map of registered symbols. Uses the SymbolEnumerator as an implementation
// base.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Linker::SymbolMap : private SymbolEnumerator {
  private:
    Linker::SymbolList symbolList;
    uint32 maxSize;
    uint32 currSize;
    uint32 delta;

  public:

    int length() const {
      return SymbolEnumerator::length();
    }

    SymbolList* getList() {
      symbolList.count = length();
      return &symbolList;
    }

    int addSymbol(const char* symbol);

    SymbolMap(uint32 iniSize, uint32 maxSize, uint32 delta);
    ~SymbolMap();

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// SymbolMap constructor
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Linker::SymbolMap::SymbolMap(uint32 iniSize, uint32 maxSize, uint32 delta) :
  SymbolEnumerator(iniSize),
  maxSize(maxSize),
  currSize(iniSize),
  delta(delta)
{
  symbolList.symbols = 0;
  symbolList.count   = 0;
  debuglog(
    LOG_DEBUG,
    "Created Linker::SymbolMap, initial size %u, max size %u, grow size %u",
    currSize, maxSize, delta
  );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Linker::SymbolMap::~SymbolMap() {
  if (symbolList.symbols) {
    std::free(symbolList.symbols);
    debuglog(LOG_DEBUG, "Freed Linker::SymbolMap::symbolList");
  }
  debuglog(LOG_DEBUG, "Destroyed Linker::SymbolMap");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Linker::SymbolMap::addSymbol(const char* symbol) {
  int result = SymbolEnumerator::add(symbol);

  // If we enumerated the symbol, we need to store it in our SymbolTable
  if (result >= 0) {

    // First time allocation of Symbol table?
    if (
      !symbolList.symbols &&
      !(symbolList.symbols = (Linker::Symbol*)std::calloc(currSize, sizeof(Linker::Symbol)))
    ) {
      debuglog(LOG_ERROR, "Unable to allocate initial Symbol table for %u entries", currSize);
      return Error::OUT_OF_MEMORY;
    }

    // Time to expand symbol table?
    if ((uint32) result >= currSize) {
      uint32 newSize = currSize + delta;
      Symbol* growSymbols = (Linker::Symbol*)std::realloc(symbolList.symbols, newSize * sizeof(Linker::Symbol));
      if (!growSymbols) {
        debuglog(LOG_ERROR, "Unable to grow Symbol table to %u entries", newSize);
        return Error::OUT_OF_MEMORY;
      }

      symbolList.symbols = growSymbols;
      currSize           = newSize;
      debuglog(LOG_INFO, "Expanded Symbol table to %u entries", currSize);
    }

    symbolList.symbols[result].name     = symbol;
    symbolList.symbols[result].symbolId = result;
  }

  return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Linker::addCode(const char* symbol, const uint16* code) {
  if (!code) {
    debuglog(LOG_ERROR, "NULL symbol address passed to %s()", __FUNCTION__);
    return Error::ILLEGAL_SYMBOL_ADDRESS;
  }
  int result = add(codeSymbols, symbol);
  if (result >= 0) {
    codeSymbols->getList()->symbols[result].code = code;
    debuglog(LOG_INFO, "Stored code symbol \'%s\' ID:%d at address %p", symbol, result, code);
  }
  return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Linker::addNative(const char* symbol, NativeCall native) {
  if (!native) {
    debuglog(LOG_ERROR, "NULL symbol address passed to %s()", __FUNCTION__);
    return Error::ILLEGAL_SYMBOL_ADDRESS;
  }
  int result = add(nativeCodeSymbols, symbol);
  if (result >= 0) {
    nativeCodeSymbols->getList()->symbols[result].native = native;
    debuglog(LOG_INFO, "Stored native call symbol \'%s\' ID:%d at address %p", symbol, result, (void*)native);
  }
  return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Linker::addData(const char* symbol, const void* data) {
  if (!data) {
    debuglog(LOG_ERROR, "NULL symbol address passed to %s()", __FUNCTION__);
    return Error::ILLEGAL_SYMBOL_ADDRESS;
  }
  int result = add(dataSymbols, symbol);

  if (result >= 0) {
    dataSymbols->getList()->symbols[result].data = data;
    debuglog(LOG_INFO, "Stored data symbol \'%s\' ID:%d at address %p", symbol, result, data);
  }
  return result;
}

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

Linker::SymbolList* Linker::getCodeSymbols() {
  if (codeSymbols) {
    return codeSymbols->getList();
  }
  debuglog(LOG_WARN, "SymbolMap codeSymbols not instantiated");
  return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Linker::SymbolList* Linker::getNativeCodeSymbols() {
  if (nativeCodeSymbols) {
    return nativeCodeSymbols->getList();
  }
  debuglog(LOG_WARN, "SymbolMap nativeCodeSymbols not instantiated");
  return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Linker::SymbolList* Linker::getDataSymbols() {
  if (dataSymbols) {
    return dataSymbols->getList();
  }
  debuglog(LOG_WARN, "SymbolMap dataSymbols not instantiated");
  return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Linker::add(SymbolMap*& map, const char* symbol) {
  if (!symbol) {
    debuglog(LOG_ERROR, "NULL symbol passed to %s()", __FUNCTION__);
    return Error::ILLEGAL_ARGUMENT;
  }

  // Check #1 make sure the SymbolMap exists
  if (
    !map &&
    !(map = new(std::nothrow)SymbolMap(INI_TABLE_SIZE, MAX_SYMBOLS, INC_TABLE_DELTA))
  ) {
    debuglog(LOG_ERROR, "Unable to allocate SymbolMap");
    return Error::OUT_OF_MEMORY;
  }

  return map->addSymbol(symbol);
}

