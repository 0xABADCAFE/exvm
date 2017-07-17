//****************************************************************************//
//**                                                                        **//
//** File:         vm_symbol.cpp                                            **//
//** Description:  VMSynbol class definition                                **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2017-07-12                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

#include <cstdio>

#include "include/vm_symbol.hpp"

using namespace ExVM;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum {
  PNODE_TO_SNODE = 8,
  SNODE_TO_PNODE = 8,
  NODE_BLOCKSIZE = 256
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Primary node structure
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct SymbolEnumerator::PNode {
  SymbolEnumerator::SNode* children[PNODE_TO_SNODE];
  int symbolID;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Secondary node structure
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct SymbolEnumerator::SNode {
  SymbolEnumerator::PNode* children[SNODE_TO_PNODE];
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Node block structure
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct SymbolEnumerator::Block {
  union {
    PNode primary;
    SNode secondary;
  } nodes[NODE_BLOCKSIZE];
  Block* prevBlock;
  int    nextFree;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Constructor
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

SymbolEnumerator::SymbolEnumerator(uint32 maxSize) :
  nodeBlock(0),
  rootNode(0),
  symbolMap(0),
  maxSymbols(maxSize),
  nextSymbolID(0)
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Destructor
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

SymbolEnumerator::~SymbolEnumerator() {
  Block*   pBlock = nodeBlock;

  /* Free the block list */
  while (pBlock) {
    void* ptr = (void*) pBlock;
    pBlock    = pBlock->prevBlock;

#ifdef VM_FULL_DEBUG
    std::fprintf(stderr, "[INF] Freeing Block at %p\n", ptr);
#endif

    std::free(ptr);
  }
  if (symbolMap) {
    std::free(symbolMap);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Convert an ASCII character code from the set 0-9A-Za-z@_ to a mapped code 0-63
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int SymbolEnumerator::mapChar(int c) const {
  if (c >= '0' && c <= '9') {
    return c - '0';
  }
  if (c >= 'A' && c <= 'Z') {
    return 10 + c - 'A';
  }
  if (c >= 'a' && c <= 'z') {
    return 38 + c - 'a';
  }
  if (c == '@') {
    return 62;
  }
  if (c == '_') {
    return 63;
  }

  return Error::ILLEGAL_SYMBOL_CHAR;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Confirm we have a node block and attempt to allocate one if not, or if full
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int SymbolEnumerator::checkBlock() {
  // Check if we need to allocate a new block of nodes
  if (!nodeBlock || nodeBlock->nextFree == NODE_BLOCKSIZE) {
    Block* newBlock = (Block*)std::calloc(1, sizeof(Block));
    if (!newBlock) {

#ifdef VM_FULL_DEBUG
      std::fprintf(stderr, "[ERR] Unable to allocate Block of %u bytes\n", (uint32)sizeof(Block));
#endif

      return 0;
    }

#ifdef VM_FULL_DEBUG
    std::fprintf(stderr, "[INF] Allocate Block of %u bytes at %p\n", (uint32)sizeof(Block), newBlock);
#endif

    // Make the newly allocated block the active one
    newBlock->prevBlock    = nodeBlock;
    nodeBlock = newBlock;
  }
  return 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Allocate the next available PNode
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

SymbolEnumerator::PNode* SymbolEnumerator::allocPNode() {
  if (!checkBlock()) {
    return 0;
  }

  // Get the next free PNode and set it's symbol ID to -1 so that we can properly detect when terminating on this
  // node that it does not mark the end of an existing symbol
  PNode* pNode = &nodeBlock->nodes[nodeBlock->nextFree++].primary;
  pNode->symbolID = -1;
  return pNode;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Allocate the next available SNode
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

SymbolEnumerator::SNode* SymbolEnumerator::allocSNode() {
  if (!checkBlock()) {
    return 0;
  }

  // Get the next free SNode from the block
  return &nodeBlock->nodes[nodeBlock->nextFree++].secondary;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Attempt to find the ID associated with a symbol
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int SymbolEnumerator::get(const char* symbol) const {

  // If there is no rootNode, then no symbols have been added. Ipso facto, cannot be known!
  if (!rootNode) {
    return Error::UNKNOWN_SYMBOL;
  }

  PNode* primaryNode;
  SNode* secondaryNode;
  int charCode, indexPrimary, indexSecondary;

  // Walk down the trie, one PNode and one SNode per mapped character
  primaryNode  = rootNode;
  while ( (charCode = *symbol++) ) {
    int code = mapChar(charCode);
    if (code < 0) {

#ifdef VM_FULL_DEBUG
      std::fprintf(stderr, "[ERR] Illegal Character \'%c\' in symbol\n", charCode);
#endif

      return code;
    }

    // Convert mapped code to index pair for our primary and secondary nodes.
    indexPrimary   = code & 3;
    indexSecondary = code >> 3;
    if (!primaryNode->children[indexPrimary]) {
      return Error::UNKNOWN_SYMBOL;
    }
    secondaryNode = primaryNode->children[indexPrimary];
    if (!secondaryNode->children[indexSecondary]) {
      return Error::UNKNOWN_SYMBOL;
    }
    primaryNode = secondaryNode->children[indexSecondary];
  }

  return primaryNode->symbolID;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Attempt to add a new symbol and obtain the associated ID.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int SymbolEnumerator::add(const char* symbol) {

  // Check we haven't reached the table size limit
  if (nextSymbolID == maxSymbols) {

#ifdef VM_FULL_DEBUG
    std::fprintf(stderr, "[ERR] Cannot add symbol %s, table limit of %u entries reached\n", symbol, maxSymbols);
#endif

    return Error::TABLE_FULL;
  }

  // If we haven't allocated a symbol map yet, we better do it.
  if (!symbolMap && !(symbolMap = (const char**)std::calloc(maxSymbols, sizeof(const char*)))) {

#ifdef VM_FULL_DEBUG
    std::fprintf(stderr, "[ERR] Could not allocate symbol map\n");
#endif

    return Error::OUT_OF_MEMORY;
  }

  // If we haven't allocated the root of our trie yet, we better do it.
  if (!rootNode && !(rootNode = allocPNode())) {

#ifdef VM_FULL_DEBUG
    std::fprintf(stderr, "[ERR] Could not allocate root node\n");
#endif

    return Error::OUT_OF_MEMORY;
  }

  const char* pChar = symbol;
  PNode* primaryNode;
  SNode* secondaryNode;
  int charCode, indexPrimary, indexSecondary;

  // Walk down the trie, one PNode and one SNode per mapped character
  primaryNode  = rootNode;
  while ( (charCode = *pChar++) ) {

    int code = mapChar(charCode);
    if (code < 0) {

#ifdef VM_FULL_DEBUG
      std::fprintf(stderr, "[ERR] Illegal Character \'%c\' in symbol\n", charCode);
#endif

      return code;
    }

    // Convert mapped code to index pair for our primary and secondary nodes
    indexPrimary   = code & 3;
    indexSecondary = code >> 3;

    // Ensure there is a child SNode instance for the PNode
    if (
      !primaryNode->children[indexPrimary] &&
      !(primaryNode->children[indexPrimary] = allocSNode())
    ) {
      return Error::OUT_OF_MEMORY;
    }
    secondaryNode = primaryNode->children[indexPrimary];

    // Ensure there is a child PNode instance fore the SNode
    if (
      !secondaryNode->children[indexSecondary] &&
      !(secondaryNode->children[indexSecondary] = allocPNode())
    ) {
      return Error::OUT_OF_MEMORY;
    }
    primaryNode = secondaryNode->children[indexSecondary];

  }

  // If this is the first time we landed on this particular PNode, it's a new symbol!
  if (primaryNode->symbolID < 0) {
    int symbolID = primaryNode->symbolID = (int)nextSymbolID++;
    symbolMap[symbolID] = symbol;
    return symbolID;
  } else {
    return Error::DUPLICATE_SYMBOL;
  }
}



