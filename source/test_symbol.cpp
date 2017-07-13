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

int main() {

  // Create a symbol table big enough for 3 unique symbols
  VMSymbolTable symbolTable(3);

  struct TestData {
    const char* symbol;
    int         result;
  } testData [] = {
    {"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_", 0 }, // Expect this to get ID 0
    {"Breaking Bad", VMSymbolTable::ERR_ILLEGAL_SYMBOL_CHAR },               // Expect this to fail   
    {"_totallyLegit123", 1 },                                                // Expect this to get ID 1
    {"_totallyLegit123", VMSymbolTable::ERR_DUPLICATE_SYMBOL },              // Expect this to fail
    {"_totallyLegit456", 2 },                                                // Expect this to get ID 2
    {"alasNoMoreRoom", VMSymbolTable::ERR_TABLE_FULL }                       // Expect this to fail
  };



  for (size_t i = 0; i < sizeof(testData) / sizeof(TestData); i++) {
    std::printf(
      "Attempting to add symbol: %-64s with expected result : %2d ... ",
      testData[i].symbol,
      testData[i].result
    );
    int result = symbolTable.add(testData[i].symbol);
    if (result == testData[i].result) {
      std::puts("SUCCESS!");
    } else {
      std::printf("FAILURE: %d\n", result);
    }
  }

  return 0;
}

