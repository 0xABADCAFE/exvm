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
  #include "machine.hpp"

class VMSymbolTable {

  private:

    // Trie implementation:
    // Rather than  defining a trie with a wide fan out (63 node pointers per node), instead we use two nodes per mapped
    // cahr, each of which has 8 children. This gives us a range of 8x8=64, sufficient to cover the entire set of valid
    // characters but with a lot less memory wasted on unused pointers.

    struct SNode;
    struct PNode;
    struct Block;

    enum {
      PNODE_TO_SNODE = 8,
      SNODE_TO_PNODE = 8
    };

    // Primary node structure
    struct PNode {
      VMSymbolTable::SNode* children[VMSymbolTable::PNODE_TO_SNODE];
      const char* symbol;
      int symbolID;
    };

    // Secondary node structure
    struct SNode {
      VMSymbolTable::PNode* children[VMSymbolTable::SNODE_TO_PNODE];
    };

    int maxSymbolID;
    int nextSymbolID;
  
  public:
    // Error enumerations
    enum {
      ERR_TABLE_FULL           = -1, // We have reached the maximum number of allowed symbol ID entries.
      ERR_UNKNOWN_SYMBOL       = -2, // The requested symbol is not in the table.
      ERR_DUPLICATE_SYMBOL     = -3, // An attempt to register the same symbol was made.
      ERR_ILLEGAL_SYMBOL_CHAR  = -4, // A symbol contained an illegal character.
      ERR_OUT_OF_MEMORY        = -5, // There was insufficient memory to allocate storage for symbol data.
    };

    explicit VMSymbolTable(int maxSymbolID);
    ~VMSymbolTable();

    // Add a new symbol to the table. Will return the uniquely assigned ID value for the symbol if successful, or
    // one of the enumerated error constants if not.

    int add(const char* symbol);

    // Get the ID value of a previously registered symbol.
    int get(const char* symbol);

  private:
    // We map the allowed symbol name characters 0-9A-Za-z_ to the range 0-62. This function maps a single input
    // character. If the input character is out of range, reuturns ERR_ILLEGAL_SYMBOL_CHAR
    int mapChar(int c);
};

#endif
