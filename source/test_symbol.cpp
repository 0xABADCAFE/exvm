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

  // Strucuture up some conformance test data
  struct TestData {
    const char* symbol; // the symbol string
    int         result; // the expected return value from add()
  } testData [] = {
    {"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_", 0 }, // Expect this to get ID 0
    {"Breaking Bad", VMSymbolTable::ERR_ILLEGAL_SYMBOL_CHAR },               // Expect this to fail
    {"_totallyLegit123", 1 },                                                // Expect this to get ID 1
    {"_totallyLegit123", VMSymbolTable::ERR_DUPLICATE_SYMBOL },              // Expect this to fail
    {"_totallyLegit456", 2 },                                                // Expect this to get ID 2
    {"alasNoMoreRoom", VMSymbolTable::ERR_TABLE_FULL }                       // Expect this to fail
  };

  // Now test the behaviour of add()
  std::puts("Testing VMSymbolTable::add()...");
  for (size_t i = 0; i < sizeof(testData) / sizeof(TestData); i++) {
    std::printf(
      "\tAttempting to add symbol: %-64s with expected result : %2d ... ",
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

  size_t length = symbolTable.length();

  std::printf("\nAdded %d unique symbols\n\n", (int)length);

  // Now test the behaviour of get()
  std::puts("Testing VMSymbolTable::get() with the original set of symbols...");
  for (size_t i = 0; i < sizeof(testData) / sizeof(TestData); i++) {
    std::printf(
      "\t%-64s : %d\n",
      testData[i].symbol,
      (int)symbolTable.get(testData[i].symbol)
    );
  }

  // Now test the symbol map
  std::printf("\nDumping full symbol map of %d valid entries...\n", (int)length);

  const char** symbolMap = symbolTable.getMap();
  for (size_t i = 0; i < length; i++) {
    std::printf("\t%d : %s\n", (int)i, symbolMap[i]);
  }

  // Test the convenience methods:
  std::puts("\nTesting operator overloads...");

  std::printf("\tsymbolTable[\"_totallyLegit123\"] = %d\n\n", symbolTable["_totallyLegit123"]);

  return 0;
}

