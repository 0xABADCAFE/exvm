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
// Linker
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  class Linker {
    private:
      class SymbolMap;
      SymbolMap* codeSymbols;
      SymbolMap* nativeCodeSymbols;
      SymbolMap* dataSymbols;

      int add(SymbolMap*& map, const char* symbol);

    public:

      class Error : public ExVM::Error {
        public:
          enum {
            ILLEGAL_SYMBOL_ADDRESS = -200,
            MAX_SYMBOLS_REACHED    = -201
          };
      };

      struct Symbol {
        union {
          const uint16* code;
          const void*   data;
          NativeCall    native;
        };
        const char* name;
        uint32      symbolId;
      };

      struct SymbolList {
        Symbol* symbols;
        uint32  count;
      };

      enum {
        MAX_SYMBOLS        = 65536,
        INI_TABLE_SIZE     = 128,
        INC_TABLE_DELTA    = 128
      };

      int addCode(const char* symbol, const uint16* func);
      int addData(const char* symbol, const void* data);
      int addNative(const char* symbol, NativeCall func);

      SymbolList* getCodeSymbols();
      SymbolList* getDataSymbols();
      SymbolList* getNativeCodeSymbols();

      Linker();
      ~Linker();

  };

}

#endif
