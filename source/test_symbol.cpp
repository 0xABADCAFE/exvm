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

using namespace ExVM;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Perform some basic tests of the SymbolNameEnumerator class
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void testSymbolNameEnumerator() {
  std::puts("Performing SymbolNameEnumerator tests...");

  // Create a symbol table big enough for 3 unique symbols
  SymbolNameEnumerator symbolEnumerator(3);

  // Strucuture up some conformance test data
  struct TestData {
    const char* symbol; // the symbol string
    int         result; // the expected return value from add()
  } testData [] = {
    {"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz@_", 0 }, // Expect this to get ID 0
    {"Breaking Bad", SymbolNameEnumerator::Error::ILLEGAL_SYMBOL_CHAR },          // Expect this to fail
    {"_totallyLegit123", 1 },                                                 // Expect this to get ID 1
    {"_totallyLegit123", SymbolNameEnumerator::Error::DUPLICATE_SYMBOL },         // Expect this to fail
    {"_totallyLegit456", 2 },                                                 // Expect this to get ID 2
    {"alasNoMoreRoom", SymbolNameEnumerator::Error::TABLE_FULL }                  // Expect this to fail
  };

  // Now test the behaviour of add()
  std::puts("Testing SymbolNameEnumerator::add()...");
  for (size_t i = 0; i < sizeof(testData) / sizeof(TestData); i++) {
    std::printf(
      "\tAttempting to add symbol: %-64s with expected result : %2d ... ",
      testData[i].symbol,
      testData[i].result
    );
    int result = symbolEnumerator.enumerate(testData[i].symbol);
    if (result == testData[i].result) {
      std::puts("SUCCESS!");
    } else {
      std::printf("FAILURE: %d\n", result);
    }
  }

  size_t length = symbolEnumerator.getNextID();

  std::printf("\nAdded %d unique symbols\n\n", (int)length);

  // Now test the behaviour of get()
  std::puts("Testing SymbolNameEnumerator::get() with the original set of symbols...");
  for (size_t i = 0; i < sizeof(testData) / sizeof(TestData); i++) {
    std::printf(
      "\t%-64s : %d\n",
      testData[i].symbol,
      (int)symbolEnumerator.getID(testData[i].symbol)
    );
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char* greeting = "Hello World!!!\n";
const char* leaving  = "Bye World!!!\n";

void testSymbolMap() {
  std::puts("Performing SymbolMap tests...");

  SymbolMap symbolMap;
  symbolMap.define("greeting", (char*)greeting);
  symbolMap.define("leaving",  (char*)leaving);
  symbolMap.define("greeting", (char*)leaving);

  const Symbol* list = symbolMap.getList();

  for (uint32 i = 0; i < symbolMap.size(); i++) {
    std::printf("\t%u : %s @ %p\n", i, list[i].name, list[i].address.raw);
  }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {

  testSymbolNameEnumerator();
  testSymbolMap();

  return 0;
}

