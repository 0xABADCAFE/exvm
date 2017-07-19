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

    public:
      class Error : public ExVM::Error {
        public:
          enum {
            ILLEGAL_SYMBOL_ADDRESS = -200,
            MAX_SYMBOLS_REACHED    = -201
          };
      };

      enum {
        MAX_SYMBOLS_NATIVE = 65536,
        MAX_SYMBOLS_CODE   = 65536,
        MAX_SYMBOLS_DATA   = 65536,
        INI_TABLE_SIZE     = 128,
        INC_TABLE_DELTA    = 128
      };

    int registerNative(const char* symbol, NativeCall func);
    int registerCode(const char* symbol, const uint16* func);
    int registerData(const char* symbol, const void* data);

    Linker();
    ~Linker();

    private:
      struct Resolved;

      template <class T> class SymbolResolver;

      int checkEnumerator(SymbolEnumerator*& symbolEnumerator);

      Resolved* native;
      Resolved* code;
      Resolved* data;

      SymbolEnumerator* nativeEnumerator;
      SymbolEnumerator* codeEnumerator;
      SymbolEnumerator* dataEnumerator;

      uint32 maxNative;
      uint32 maxCode;
      uint32 maxData;
  };

}

#endif
