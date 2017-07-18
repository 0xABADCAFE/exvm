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
// SymbolEnumerator
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

  class SymbolEnumerator {

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

      explicit SymbolEnumerator(uint32 maxSize);
      ~SymbolEnumerator();

      int raiseLimit(uint32 limit);

      // Add a new symbol to the table. Will return the uniquely assigned ID value for the symbol if successful, or
      // one of the enumerated error constants if not.
      int add(const char* symbol);

      // Get the ID value of a previously registered symbol.
      int get(const char* symbol) const;

      uint32 length() const {
        return nextSymbolID;
      }

      const char** getMap() const {
        return symbolMap;
      }

      int operator[](const char* symbol) const {
        return get(symbol);
      }

      int isFull() const {
        return nextSymbolID == maxSymbols;
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
      Block*       nodeBlock;

      // Root of the trie
      PNode*       rootNode;

      // Array of symbols
      const char** symbolMap;

      // Table size, set on construction
      uint32 maxSymbols;

      // The next ID we will allocate
      uint32 nextSymbolID;

  };
}

#endif
