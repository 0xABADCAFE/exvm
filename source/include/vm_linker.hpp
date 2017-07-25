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
