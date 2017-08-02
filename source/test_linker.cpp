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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void nativePrint(Interpreter* vm) {
  std::puts(vm->getReg(_r0).pCh());
}

// Mock code segment defining a single do nothing function
uint16 mockCodeSegment[] = {
  _ret,
  0xFFFF, // DUMMY - we want to inject a resolved symbol ID here
  0xFFFF,
  0xFFFF,
  0xFFFF,
  0xFFFF,
};

// Mock data segment defining four 32 bit words
uint32 mockDataSegment[] = {
  0xABADCAFE,
  0xDEADBEEF,
  0x01234567,
  0x89ABCDEF
};

// Mock name segment
char mockNameSegment[] =
  // Name               Offset
  "main\0"           // 0
  "nativePrint\0"    // 5
  "zero\0"           // 17
  "one\0"            // 22
  "two\0"            // 26
  "three\0";         // 30

// Mock export symbol table
RawSegmentData::SymbolRef mockExports[] = {
  {
    0 | RawSegmentData::TYPE_CODE,  // Offset of the symbol name "main" in the name segment OR'd with CODE
    0                               // Offset into the code segment (in words)
  }, {
    17 | RawSegmentData::TYPE_DATA, // Offset of the symbol name "zero" in the name segment OR'd with DATA
    0                               // Offset into the data segment (in bytes)
  }, {
    22 | RawSegmentData::TYPE_DATA,
    4,
  }, {
    26 | RawSegmentData::TYPE_DATA,
    8,
  }, {
    30 | RawSegmentData::TYPE_DATA,
    12,
  },

};

// Mock import symbol table
RawSegmentData::SymbolRef mockImports[] = {
  {
    5 | RawSegmentData::TYPE_NATIVE, // Offset of the symbol name "nativePrint" in the name segment OR'd with DATA
    1                                // Offset into the code segment where the symbol ID will be injected
  }, {
    30 | RawSegmentData::TYPE_DATA, // Offset of the symbol name "three" in the name segment OR'd with DATA
    2                               // Offset into the code segment where the symbol ID will be injected
  }, {
    26 | RawSegmentData::TYPE_DATA, // Offset of the symbol name "two" in the name segment OR'd with DATA
    3                               // Offset into the code segment where the symbol ID will be injected
  }, {
    22 | RawSegmentData::TYPE_DATA, // Offset of the symbol name "one" in the name segment OR'd with DATA
    4                               // Offset into the code segment where the symbol ID will be injected
  }, {
    17 | RawSegmentData::TYPE_DATA, // Offset of the symbol name "zero" in the name segment OR'd with DATA
    5                               // Offset into the code segment where the symbol ID will be injected
  }

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {

  RawSegmentData mockLoadSegment = {
    mockCodeSegment,                                         // .codeSegment
    mockDataSegment,                                         // .dataSegment
    mockNameSegment,                                         // .nameSegment
    mockExports,                                             // .exportTable
    mockImports,                                             // .importTable
    RawSegmentData::MAGIC,                                   // .magic
    sizeof(mockExports) / sizeof(RawSegmentData::SymbolRef), // .exportTableLength
    sizeof(mockImports) / sizeof(RawSegmentData::SymbolRef), // .importTableLength
    sizeof(mockCodeSegment) / sizeof(uint16),                // .codeSegmentLength
    sizeof(mockDataSegment),                                 // .dataSegmentLength
    sizeof(mockNameSegment)                                  // .nameSegmentLength
  };

  std::printf(
    "RawSegmentData {\n"
    "\tcodeSegment       : %p\n"
    "\tdataSegment       : %p\n"
    "\tnameSegment       : %p\n"
    "\texportTable       : %p\n"
    "\timportTable       : %p\n"
    "\tmagic             : 0x%08X\n"
    "\texportTableLength : %u\n"
    "\timportTableLength : %u\n"
    "\tcodeSegmentLength : %u\n"
    "\tdataSegmentLength : %u\n"
    "\tnameSegmentLength : %u\n"
    "}\n",
    mockLoadSegment.codeSegment,
    mockLoadSegment.dataSegment,
    mockLoadSegment.nameSegment,
    mockLoadSegment.exportTable,
    mockLoadSegment.importTable,
    mockLoadSegment.magic,
    mockLoadSegment.exportTableLength,
    mockLoadSegment.importTableLength,
    mockLoadSegment.codeSegmentLength,
    mockLoadSegment.dataSegmentLength,
    mockLoadSegment.nameSegmentLength
  );

  std::puts("Code Segment before linking...");
  for (uint32 i=0; i<mockLoadSegment.codeSegmentLength; i++) {
    std::printf("%u : 0x%04X\n", i, mockLoadSegment.codeSegment[i]);
  }

  Linker testLinker;
  testLinker.defineNativeCode("nativePrint", nativePrint);
  testLinker.addRawSegment(&mockLoadSegment);
  testLinker.link();

  std::puts("Code Segment after linking...");
  for (uint32 i=0; i<mockLoadSegment.codeSegmentLength; i++) {
    std::printf("%u : 0x%04X\n", i, mockLoadSegment.codeSegment[i]);
  }

  return 0;
}

