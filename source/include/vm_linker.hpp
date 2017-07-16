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
  #include "vm_symbol.hpp"

namespace ExVM {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// VMLinker
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class VMLinker {

  public:
    enum {
      MAX_SYMBOLS_NATIVE = 65536,
      MAX_SYMBOLS_CODE   = 65536,
      MAX_SYMBOLS_DATA   = 65536,
    };

  int registerNative(const char* symbol, NativeCall func);
  int registerCode(const char* symbol, const uint16* func);
  int registerData(const char* symbol, const void* data);

  VMLinker();
  ~VMLinker();

  private:
    struct Resolved;

    SymbolEnumerator* native;
    SymbolEnumerator* code;
    SymbolEnumerator* data;
};
}
#endif
