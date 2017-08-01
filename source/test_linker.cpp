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
#include "include/vm_core.hpp"
#include "include/vm_inline.hpp"
#include "include/vm_codemacros.hpp"
#include "include/vm_linker.hpp"

using namespace ExVM;

void nativePrint(Interpreter* vm) {
  std::puts(vm->getReg(_r0).pCh());
}


uint16 dummy[] = {
  _ret
};

const char* greeting = "Hello World!!!\n";
const char* leaving  = "Bye World!!!\n";

int main() {

  Linker testLinker;
  int result;

  std::puts("Testing testLinker.defineData(\"greeting\"), expect ID 0");

  result = testLinker.defineData("greeting", greeting);
  if (result == 0) {
    std::puts("\tSUCCESS");
  } else {
    std::puts("\tFAILED");
  }

  std::puts("Testing testLinker.defineData(\"leaving\"), expect ID 1");
  result = testLinker.defineData("leaving", leaving);
  if (result == 1) {
    std::puts("\tSUCCESS");
  } else {
    std::puts("\tFAILED");
  }

  std::puts("Testing testLinker.defineData(\"greeting\"), expect SymbolEnumerator::Error::DUPLICATE_SYMBOL");
  result = testLinker.defineData("greeting", greeting);
  if (result == SymbolNameEnumerator::Error::DUPLICATE_SYMBOL) {
    std::puts("\tSUCCESS");
  } else {
    std::puts("\tFAILED");
  }

  std::puts("Testing testLinker.defineData(\"leaving\"), expect SymbolEnumerator::Error::DUPLICATE_SYMBOL");
  result = testLinker.defineData("leaving", leaving);
  if (result == SymbolNameEnumerator::Error::DUPLICATE_SYMBOL) {
    std::puts("\tSUCCESS");
  } else {
    std::puts("\tFAILED");
  }

  std::puts("Testing testLinker.defineNativeCode(\"greeting\"), expect ID 0");
  result = testLinker.defineNativeCode("print", nativePrint);
  if (result == 0) {
    std::puts("\tSUCCESS");
  } else {
    std::puts("\tFAILED");
  }

  std::puts("Testing testLinker.defineCode(\"main\"), expect ID 0");
  result = testLinker.defineCode("main", dummy);
  if (result == 0) {
    std::puts("\tSUCCESS");
  } else {
    std::puts("\tFAILED");
  }

  std::printf("Sizeof RawSegmentData: %u\n", sizeof(RawSegmentData));

  return 0;
}

