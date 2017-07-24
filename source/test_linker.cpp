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
/*
  Linker testLinker;
  int result;

  std::puts("Testing testLinker.addData(\"greeting\"), expect ID 0");

  result = testLinker.addData("greeting", greeting);
  if (result == 0) {
    std::puts("\tSUCCESS");
  } else {
    std::puts("\tFAILED");
  }

  std::puts("Testing testLinker.addData(\"leaving\"), expect ID 1");
  result = testLinker.addData("leaving", leaving);
  if (result == 1) {
    std::puts("\tSUCCESS");
  } else {
    std::puts("\tFAILED");
  }

  std::puts("Testing testLinker.addData(\"greeting\"), expect SymbolEnumerator::Error::DUPLICATE_SYMBOL");
  result = testLinker.addData("greeting", greeting);
  if (result == SymbolEnumerator::Error::DUPLICATE_SYMBOL) {
    std::puts("\tSUCCESS");
  } else {
    std::puts("\tFAILED");
  }

  std::puts("Testing testLinker.addData(\"leaving\"), expect SymbolEnumerator::Error::DUPLICATE_SYMBOL");
  result = testLinker.addData("leaving", leaving);
  if (result == SymbolEnumerator::Error::DUPLICATE_SYMBOL) {
    std::puts("\tSUCCESS");
  } else {
    std::puts("\tFAILED");
  }

  std::puts("Testing testLinker.addNative(\"greeting\"), expect ID 0");
  result = testLinker.addNative("print", nativePrint);
  if (result == 0) {
    std::puts("\tSUCCESS");
  } else {
    std::puts("\tFAILED");
  }

  std::puts("Testing testLinker.addCode(\"main\"), expect ID 0");
  result = testLinker.addCode("main", dummy);
  if (result == 0) {
    std::puts("\tSUCCESS");
  } else {
    std::puts("\tFAILED");
  }

  std::puts("Testing getCodeSymbols()...");
  Linker::SymbolList*
  list = testLinker.getCodeSymbols();

  for (uint32 i=0; i < list->count; i++) {
    std::printf("\t%i : %s : %p\n", i, list->symbols[i].name, list->symbols[i].data);
  }

  std::puts("Testing getDataSymbols()...");
  list = testLinker.getDataSymbols();
  for (uint32 i=0; i < list->count; i++) {
    std::printf("\t%i : %s : %p\n", i, list->symbols[i].name, list->symbols[i].data);
  }

  std::puts("Testing getNativeCodeSymbols()...");
  list = testLinker.getNativeCodeSymbols();
  for (uint32 i=0; i < list->count; i++) {
    std::printf("\t%i : %s : %p\n", i, list->symbols[i].name, list->symbols[i].data);
  }
*/
  return 0;
}

