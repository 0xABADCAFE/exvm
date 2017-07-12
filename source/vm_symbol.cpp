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

#include "include/vm_symbol.hpp"

VMSymbolTable::VMSymbolTable(int maxSymbolID) :
  maxSymbolID(maxSymbolID),
  nextSymbolID(0)
{

}

VMSymbolTable::~VMSymbolTable() {

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Convert an ASCII character code from the set 0-9A-Za-z_ to a mapped code 0-62

int VMSymbolTable::mapChar(int c) {
  if (c >= '0' && c <= '9') {
    return c - '0';
  }
  if (c >= 'A' && c <= 'Z') {
    return 10 + c - 'A';
  }
  if (c >= 'a' && c <= 'z') {
    return 38 + c - 'a';
  }
  if (c == '_') {
    return 62;
  }
  return ERR_ILLEGAL_SYMBOL_CHAR;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int VMSymbolTable::add(const char* name) {

  const char* pNextChar = name;
  while (int currentChar = (int) *pNextChar++) {
    int mappedChar = mapChar(currentChar);
    if (mappedChar < 0) {
      return mappedChar;
    }
  }
  return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {

  VMSymbolTable dataSymbols(65536);

  int result = dataSymbols.add("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_");

  return 0;
}
