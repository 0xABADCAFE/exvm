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

/*
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
*/

