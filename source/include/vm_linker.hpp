//****************************************************************************//
//**                                                                        **//
//** File:         vm_linker.hpp                                            **//
//** Description:  Linker definitions                                       **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2017-07-12                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

#ifndef _VM_LINKER_HPP_
  #define _VM_LINKER_HPP_
  #include "vm.hpp"
  #include "vm_symbol.hpp"

namespace ExVM {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// RawSegmentData
//
// This type represents the expected format of an ExVM object file after loading. An object file will have:
//
//   * A code segment containing ExVM opcodes (may be zero length)
//   * A data segment containing global data entries (may be zero length)
//   * A name heap - a set of strings for all the symbol names that are imported and exported. This is shared so that
//     a string need only be declared once if it is both exported and imported by the same code.
//   * A table of Symbols Exported - contains the type and offset of the Symbol within the appropriate Segment and
//     the offset of the symbol name in the name heap.
//   * A table of Symbols Imported - Same structure as the Exported set, with the distinction that the offset indicates
//     the offset into the code Segment where the resolved Symbol ID should be injected at runtime.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


  struct RawSegmentData {
    enum {
      // Valid for exported and imported symbols
      TYPE_CODE   = 0x00000000,

      // Valid for exported and imported symbols
      TYPE_DATA   = 0x40000000,

      // Valid for imported symbols only
      TYPE_NATIVE = 0x80000000,

      // Masks used in entries table
      TYPE_MASK   = 0xC0000000,
      OFFSET_MASK = ~TYPE_MASK
    };

    struct SymbolRef {
      uint32 symbolData;

      // For exports, defines the offset in either the data or code Segment of the named entitiy.
      // For imports, defines the offset in the codeSegment where the resolved Symbol ID should be injected.
      uint32 offset;

      // Extract the expected name of the synbolData reference from the symbolNames heap
      const char* getSymbolName(const char* base) {
        return &base[(symbolData & OFFSET_MASK)];
      }

      // Extract the SymbolType from the symbolData reference.
      uint32 getSymbolType() {
        return symbolData & TYPE_MASK;
      }
    };

    // Location of the Code Segment, an array of 16-bit ExVM instruction words
    uint16*      codeSegment;

    // Location of the Data Segment
    void*        dataSegment;

    // Location of the symbol name heap
    const char*  symbolNames;

    // Symbols that are exported
    SymbolRef *exports;

    // Symbols that are imported
    SymbolRef *imports;
  };

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Linker
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  class Linker {
    private:
      SymbolMap* codeSymbols;
      SymbolMap* nativeCodeSymbols;
      SymbolMap* dataSymbols;

      int defineSymbol(SymbolMap*& map, const char* name, const void* address);

    public:
/*
      class Error : public ExVM::Error {

      };
*/

      int defineNativeCode(const char* name, NativeCall native) {
        return defineSymbol(nativeCodeSymbols, name, (const void*)native);
      }

      int defineCode(const char* name, const uint16* code) {
        return defineSymbol(codeSymbols, name, code);
      }

      int defineData(const char* name, const void* data) {
        return defineSymbol(dataSymbols, name, data);
      }

      Linker();
      ~Linker();
  };

}

#endif
