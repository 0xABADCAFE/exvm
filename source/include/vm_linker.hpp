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
    const char*  nameSegment;

    // Symbols that are exported
    SymbolRef*   exports;

    // Symbols that are imported
    SymbolRef*   imports;

    // This section represents the beginning of the data that is actually loaded.

    // Magic identifier
    uint32 magic;

    // The number of exported symbols
    uint32 exportsLength;

    // The number of imported synbo;s
    uint32 importsLength;

    // The number of ExVM instruction words (16-bit) in the full codeSegment
    uint32 codeSegmentLength;

    // The number of bytes in the dataSegment
    uint32 dataSegmentLength;

    // The number of bytes in the nameSegment
    uint32 nameSegmentLength;

    // This will actually be allocated along with all the data inlined in memory. What follows is the expected layout
    // SymbolRef[exportsLength]  8 bytes per entry
    // SymbolRef[importsLength]  8 bytes per entry
    // uint16[codeSegmentLength] 2 bytes per etnry
    // <padding to next 64-bit aligned address>
    // uint8[dataSegmentLength]  1 byte per entry
    // char[nameSegmentLength]   1 byte per entry
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

      // RawSegmentData pointer table, kkeeps track of all the RawSegmentData entries that have been added.
      RawSegmentData** rawSegments;
      uint32           numRawSegments;

      // Current allocation size for RawSegmentData array
      uint32 currSize;

      // Increment size for RawSegmentData array
      uint32 delta;

      int defineSymbol(SymbolMap*& map, const char* name, const void* address);

    public:

      class Error : public ExVM::Error {
        enum {
          INVALID_SEGMENT = -200
        };
      };

      enum {
        DEF_INI_TABLE_SIZE     = 128,
        DEF_INC_TABLE_DELTA    = 128
      };

      uint32 getNumSegments() const {
        return numRawSegments;
      }

      int defineNativeCode(const char* name, NativeCall native) {
        return defineSymbol(nativeCodeSymbols, name, (const void*)native);
      }

      int defineCode(const char* name, const uint16* code) {
        return defineSymbol(codeSymbols, name, code);
      }

      int defineData(const char* name, const void* data) {
        return defineSymbol(dataSymbols, name, data);
      }

      // Add a RawSegmentData for linking
      int addRawSegment(RawSegmentData* rawSegment);

      // Run the linking Process
      int link();

      Linker(uint32 defSegmentCount = DEF_INI_TABLE_SIZE, uint32 defSegmentDelta = DEF_INC_TABLE_DELTA);
      ~Linker();

    private:
      // Add all the exported symbols in each RawSegmentData entry to the appropriate Map and enumerate
      int enumerateAllSymbols();

      // Inject the enumerated symbolID into the code for each RawSegmentData's import list.
      int resolveToEnumerated();
  };

}

#endif
