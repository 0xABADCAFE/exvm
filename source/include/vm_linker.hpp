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
  #include "vm_rawsegment.hpp"
  #include "vm_core.hpp"
  #include "vm_symbol.hpp"

namespace ExVM {

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

      // RawSegmentData pointer table, keeps track of all the RawSegmentData entries that have been added.
      RawSegmentData** rawSegments;
      uint32           numRawSegments;

      // Current allocation size for RawSegmentData array
      uint32 currSize;

      // Increment size for RawSegmentData array
      uint32 delta;

      int defineSymbol(SymbolMap*& map, const char* name, void* address, uint32 symbolIDSize);

    public:

      class Error : public ExVM::Error {
        public:
        enum {
          INVALID_SEGMENT     = -200,
          ILLEGAL_EXPORT_TYPE = -201
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
        return defineSymbol(nativeCodeSymbols, name, (void*)native, VMDefs::NATIVE_SYMBOL_ID_SIZE);
      }

      int defineCode(const char* name, uint16* code) {
        return defineSymbol(codeSymbols, name, code, VMDefs::CODE_SYMBOL_ID_SIZE);
      }

      int defineData(const char* name, void* data) {
        return defineSymbol(dataSymbols, name, data, VMDefs::DATA_SYMBOL_ID_SIZE);
      }

      // Add a RawSegmentData for linking
      int addRawSegment(RawSegmentData* rawSegment);

      // Run the linking Process
      int link();

      // Return an executable ready for passing to the Interpreter class. Once we have this, we can delete
      // the Linker instance, unless we want to keep it for debugging etc.
      Executable* getExecutable();

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
