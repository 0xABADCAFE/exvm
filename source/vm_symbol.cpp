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
#include <cstring>
#include <cstdlib>
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

struct SymbolNameEnumerator::PNode {
  SymbolNameEnumerator::SNode* children[PNODE_TO_SNODE];
  int symbolID;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Secondary node structure
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct SymbolNameEnumerator::SNode {
  SymbolNameEnumerator::PNode* children[SNODE_TO_PNODE];
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Node block structure
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct SymbolNameEnumerator::Block {
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

SymbolNameEnumerator::SymbolNameEnumerator(uint32 maxID) :
  nodeBlock(0),
  rootNode(0),
  maxSymbolID(maxID),
  nextSymbolID(0)
{
  debuglog(LOG_DEBUG, "Created SymbolNameEnumerator with maxSize %u", maxSymbolID);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Destructor
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

SymbolNameEnumerator::~SymbolNameEnumerator() {
  Block*   pBlock = nodeBlock;

  /* Free the block list */
  while (pBlock) {
    void* ptr = (void*) pBlock;
    pBlock    = pBlock->prevBlock;

    debuglog(LOG_DEBUG, "Freeing Block at %p", ptr);

    std::free(ptr);
  }
  debuglog(LOG_DEBUG, "Destroyed SymbolNameEnumerator");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Convert an ASCII character code from the set 0-9A-Za-z@_ to a mapped code 0-63
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int SymbolNameEnumerator::mapChar(int c) const {
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

int SymbolNameEnumerator::checkBlock() {
  // Check if we need to allocate a new block of nodes
  if (!nodeBlock || nodeBlock->nextFree == NODE_BLOCKSIZE) {
    Block* newBlock = (Block*)std::calloc(1, sizeof(Block));
    if (!newBlock) {
      debuglog(LOG_ERROR, "Unable to allocate Block of %u bytes", (uint32)sizeof(Block));
      return 0;
    }
    debuglog(LOG_DEBUG, "Allocated Block of %u bytes at %p", (uint32)sizeof(Block), newBlock);

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

SymbolNameEnumerator::PNode* SymbolNameEnumerator::allocPNode() {
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

SymbolNameEnumerator::SNode* SymbolNameEnumerator::allocSNode() {
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

int SymbolNameEnumerator::getID(const char* name) const {

  // Protect against null
  if (!name) {
    return Error::ILLEGAL_ARGUMENT;
  }

  // If there is no rootNode, then no symbols have been added. Ipso facto, cannot be known!
  if (!rootNode) {
    return Error::UNKNOWN_SYMBOL;
  }

  PNode* primaryNode;
  SNode* secondaryNode;
  int charCode, indexPrimary, indexSecondary;

  // Walk down the trie, one PNode and one SNode per mapped character
  primaryNode  = rootNode;
  while ( (charCode = *name++) ) {
    int code = mapChar(charCode);
    if (code < 0) {
      debuglog(LOG_ERROR, "Illegal Character \'%c\' in symbol\n", charCode);
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

int SymbolNameEnumerator::enumerate(const char* name) {

  // Protect against null
  if (!name) {
    return Error::ILLEGAL_ARGUMENT;
  }

  // Check we haven't reached the table size limit
  if (isFull()) {
    debuglog(LOG_WARN, "Cannot add symbol %s, table limit of %u entries reached", name, maxSymbolID);
    return Error::TABLE_FULL;
  }

  // If we haven't allocated the root of our trie yet, we better do it.
  if (!rootNode && !(rootNode = allocPNode())) {
    debuglog(LOG_ERROR, "Could not allocate root node for trie");
    return Error::OUT_OF_MEMORY;
  }

  const char* pChar = name;
  PNode* primaryNode;
  SNode* secondaryNode;
  int charCode, indexPrimary, indexSecondary;

  // Walk down the trie, one PNode and one SNode per mapped character
  primaryNode  = rootNode;
  while ( (charCode = *pChar++) ) {

    int code = mapChar(charCode);
    if (code < 0) {
      debuglog(LOG_WARN, "Illegal Character \'%c\' in symbol", charCode);
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
    return primaryNode->symbolID = (int)nextSymbolID++;
  } else {
    return Error::DUPLICATE_SYMBOL;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// SymbolMap constructor
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

SymbolMap::SymbolMap(uint32 maxSize, uint32 iniSize, uint32 delta) :
  SymbolNameEnumerator(maxSize),
  symbols(0),
  currSize(iniSize),
  delta(delta)
{
  debuglog(
    LOG_DEBUG,
    "Created SymbolMap, initial size %u, max size %u, grow size %u",
    currSize, maxSize, delta
  );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

SymbolMap::~SymbolMap() {
  if (symbols) {
    std::free(symbols);
    debuglog(LOG_DEBUG, "Freed SymbolMap::symbolList");
  }
  debuglog(LOG_DEBUG, "Destroyed SymbolMap");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int SymbolMap::define(const char* name, const void* address) {

  // Protect against null
  if (!address) {
    debuglog(LOG_ERROR, "Unable to define Symbol %s at null address", name);
    return Error::ILLEGAL_ARGUMENT;
  }

  int result = SymbolNameEnumerator::enumerate(name);

  // If we enumerated the symbol, we need to store it in our SymbolTable
  if (result >= 0) {

    // First time allocation of Symbol table?
    if (
      !symbols &&
      !(symbols = (Symbol*)std::calloc(currSize, sizeof(Symbol)))
    ) {
      debuglog(LOG_ERROR, "Unable to allocate initial Symbol table for %u entries", currSize);
      return Error::OUT_OF_MEMORY;
    }

    // Time to expand symbol table?
    if ((uint32) result >= currSize) {
      uint32  newSize     = currSize + delta;
      Symbol* growSymbols = (Symbol*)std::realloc(symbols, newSize * sizeof(Symbol));
      if (!growSymbols) {
        debuglog(LOG_ERROR, "Unable to grow Symbol table to %u entries", newSize);
        return Error::OUT_OF_MEMORY;
      }

      symbols  = growSymbols;
      currSize = newSize;
      debuglog(LOG_INFO, "Expanded Symbol table to %u entries", currSize);
    }

    symbols[result].name = name;
    symbols[result].address.raw = address;

    debuglog(LOG_INFO, "Added symbol #%d \'%s\' @ %p", result, name, address);
  } else {
    debuglog(LOG_WARN, "Failed to add \'%s\', result %d", name, result);
  }

  return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


