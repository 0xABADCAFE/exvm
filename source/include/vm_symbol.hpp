//****************************************************************************//
//**                                                                        **//
//** File:         vm_symbol.hpp                                            **//
//** Description:  Symbol definitions                                       **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2017-07-12                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

#ifndef _VM_SYMBOL_HPP_
  #define _VM_SYMBOL_HPP_
  #include "vm.hpp"
  #include "machine.hpp"

namespace ExVM {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Symbol
//
// Simple structure representing a symbol
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  struct Symbol {

    // Symbol address. We use a union for simplicity and to avoid cast orgies or the need for templates.
    union Address {

      // VM code address
      uint16* code;

      // VM data section
      uint8*  data;

      // Host functon
      NativeCall    native;

      // raw address
      void*   raw;

    } address;

    // Symbol name
    const char* name;
  };

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// SymbolNameEnumerator
//
// Assigns unique ID values to symbol strings. Symbol strings represent imported or exported identifiers and may only
// contain the following 64 characters 0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz@_
//
// Each ASCII character in the above set is mapped to a value 0-63. Symbols of varying lengths are added to the table
// which stores them in an internal trie structure. The trie uses two levels per mapped character, each with a fan
// out of 8. The nodes are allocated in contiguous blocks.
//
// Each symbol that is added is assigned a unique ID, starting at zero. The maximum number of symbols to accomodate is
// given on construction.
//
// EXVM permits 65536 symbols each for function, data and native function identifiers.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  class SymbolNameEnumerator {

    public:
      class Error : public ExVM::Error {
        public:
          // Error enumerations specific to this component
          enum {
            ILLEGAL_SYMBOL_CHAR = ILLEGAL_ARGUMENT, // A symbol contained an illegal character.
            TABLE_FULL          = -100,             // We have reached the maximum number of allowed symbol ID entries.
            UNKNOWN_SYMBOL      = -101,             // The requested symbol is not in the table.
            DUPLICATE_SYMBOL    = -102,             // An attempt to register the same symbol was made.
          };
      };

      explicit SymbolNameEnumerator(uint32 maxID);
      ~SymbolNameEnumerator();

      // Add a new symbol to the table. Will return the uniquely assigned ID value for the symbol if successful, or
      // one of the enumerated error constants if not.
      int enumerate(const char* name);

      // Get the ID value of a previously registered symbol.
      int getID(const char* name) const;

      // Return the ID of the next symbol
      uint32 getNextID() const {
        return nextSymbolID;
      }

      // Get the maximum allowed Enumerated ID
      uint32 getMaxID() const {
        return maxSymbolID;
      }

      // Check if the enumerated set has been filled
      int isFull() const {
        return nextSymbolID == maxSymbolID;
      }

    private:
      // Trie implementation:
      // Rather than  defining a trie with a wide fan out (64 node pointers per node), instead we use two nodes per mapped
      // cahr, each of which has 8 children. This gives us a range of 8x8=64, sufficient to cover the entire set of valid
      // characters but with a lot less memory wasted on unused pointers.

      // Primary node type
      struct PNode;

      // Secondary node type
      struct SNode;

      // Block of allocated nodes, linked together.
      struct Block;

      // We map the allowed symbol name characters 0-9A-Za-z@_ to the range 0-63 . This function maps a single input
      // character. If the input character is out of range, reuturns ERR_ILLEGAL_SYMBOL_CHAR
      int     mapChar(int c) const;

      // Allocate a new PNode. Allocations will be from the remainder of the current Block or from a new Block if the
      // existing one is full.
      PNode*  allocPNode();

      // Allocate a new SNode. Allocations will be from the remainder of the current Block of from a new Block if the
      // existing one is full.
      SNode*  allocSNode();

      // Check if a Block is available.
      int     checkBlock();

      // Data ////////////////////////////////////////////////////////////////////////////////////////////////////////////

      // Location of the current Block.
      Block* nodeBlock;

      // Root of the trie
      PNode* rootNode;

      // Table size, set on construction
      uint32 maxSymbolID;

      // The next ID we will allocate
      uint32 nextSymbolID;

  };

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// SymbolMap
//
// Extends SymbolNameEnumerator into a utility class that maintains a Symbol::List set of Symbol instances that have
// been uniquely enumerated by the SymbolNameEnumerator.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  class SymbolMap : private SymbolNameEnumerator {
    private:
      // Symbol Array
      Symbol* symbols;

      // Current allocation size for Symbol Array
      uint32  currSize;

      // Increment size for Symbol Array
      uint32  delta;

    public:
      enum {
        DEF_INI_TABLE_SIZE     = 128,
        DEF_INC_TABLE_DELTA    = 128
      };

      // Return the current list of defined Symbols
      const Symbol* getList() const {
        return symbols;
      }

      // Return the length of the current list of defined symbos
      uint32 size() const {
        return SymbolNameEnumerator::getNextID();
      }

      // Lookup a defined symbol by name
      const Symbol* find(const char* name) const {
        int i = SymbolNameEnumerator::getID(name);
        if (i >= 0) {
          return &symbols[i];
        }
        return 0;
      }

      // Define a new Symbol
      int define(const char* name, void* address);

      int getID(const char* name) const {
        return SymbolNameEnumerator::getID(name);
      }

      // obtain a symbol by a previous ID
      const Symbol* get(uint32 symbolID) const {
        if (!symbols || symbolID >= size()) {
          return 0;
        }
        return &symbols[symbolID];
      }

      SymbolMap(uint32 maxSize, uint32 iniSize = DEF_INI_TABLE_SIZE, uint32 delta = DEF_INC_TABLE_DELTA);
      ~SymbolMap();
  };

}

#endif
