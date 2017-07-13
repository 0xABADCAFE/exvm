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

enum {
  PNODE_TO_SNODE = 8,
  SNODE_TO_PNODE = 8,
  NODE_BLOCKSIZE = 8192
};

// Primary node structure
struct VMSymbolTable::PNode {
  VMSymbolTable::SNode* children[PNODE_TO_SNODE];
  PNode* parentNode;
  int code;
  int count;
};

// Secondary node structure
struct VMSymbolTable::SNode {
  VMSymbolTable::PNode* children[SNODE_TO_PNODE];
};


struct VMSymbolTable::Block {
  union {
    PNode primary;
    SNode secondary;
  } nodes[NODE_BLOCKSIZE];
  Block* prevBlock;
  int    nextFree;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

VMSymbolTable::VMSymbolTable(int maxSymbolID) :
  nodeBlock(0),
  rootNode(0),
  maxSymbolLength(0),
  maxSymbolID(maxSymbolID),
  nextSymbolID(0)
{
  rootNode  = allocPNode(0, 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

VMSymbolTable::~VMSymbolTable() {
  Block*   pBlock = nodeBlock;

  /* Free the block list */
  while (pBlock) {
    void* ptr = (void*) pBlock;
    pBlock    = pBlock->prevBlock;
    std::free(ptr);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Convert an ASCII character code from the set 0-9A-Za-z_ to a mapped code 0-62

int VMSymbolTable::mapChar(int c) {
  if (c >= '0' && c <= '9') {
    return c - '0';
  }
  if (c >= 'A' && c <= 'Z') {
    return 10 + c - 'A';
  }
  if (c >= 'a' && c <= 'z') {
    return 38 + c - 'a';
  }
  if (c == '_') {
    return 62;
  }
  return ERR_ILLEGAL_SYMBOL_CHAR;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//  Allocate a new PNode. This performs several tasks. It tries to allocate the next free PNode from the
//  currently active Block, If the block is not yet allocated or is full, it tries to allocate a new one. If
//  successful the newly allocated Block is made active and the first node taken. The Blocks are chained
//  such that they can all be freed later.
//  Once a Block is obtained, it is filled in with the parentNode and code values supplied.

VMSymbolTable::PNode* VMSymbolTable::allocPNode(VMSymbolTable::PNode* parent, int code) {

  PNode* primaryNode = 0;

  /* Check if we need to allocate a new block of nodes */
  if (!nodeBlock || nodeBlock->nextFree == NODE_BLOCKSIZE) {
    Block* newBlock = (Block*)std::calloc(1, sizeof(Block));
    if (!newBlock) {
      std::fprintf(stderr, "Unable to allocate Block of %lu bytes\n", (unsigned long)sizeof(Block));
      return 0;
    }

    /* Make the newly allocated block the active one */
    newBlock->prevBlock    = nodeBlock;
    nodeBlock = newBlock;
  }

  /* get the next Primary node from the block and populate it */
  primaryNode = &nodeBlock->nodes[nodeBlock->nextFree++].primary;
  primaryNode->parentNode = parent;
  primaryNode->code       = code;

  return primaryNode;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//  Allocate a new SNode. This performs several tasks. It tries to allocate the next free SNode from the
//  currently active NodeBlock, If the block is not yet allocated or is full, it tries to allocate a new one. If
//  successful the newly allocated NodeBlock is made active and the first node taken. The NodeBlocks are chained
//  such that they can all be freed later.

VMSymbolTable::SNode* VMSymbolTable::allocSNode() {

  SNode* secondaryNode = 0;

  /* Check if we need to allocate a new block of nodes */
  if (!nodeBlock || nodeBlock->nextFree == NODE_BLOCKSIZE) {
    Block* newBlock = (Block*)calloc(1, sizeof(Block));
    if (!newBlock) {
      std::fprintf(stderr, "Unable to allocate Block of %lu bytes\n", (unsigned long)sizeof(Block));
      return 0;
    }

    /* Make the newly allocated block the active one */
    newBlock->prevBlock    = nodeBlock;
    nodeBlock = newBlock;
  }

  /* get the next Primary node from the block and populate it */
  secondaryNode = &nodeBlock->nodes[nodeBlock->nextFree++].secondary;

  return secondaryNode;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int VMSymbolTable::add(const char* symbol) {

  if (nextSymbolID == maxSymbolID) {
    return ERR_TABLE_FULL;
  }

  PNode* primaryNode;
  SNode* secondaryNode;
  int charCode, indexPrimary, indexSecondary, symbolLength;

  symbolLength = 0;
  primaryNode  = rootNode;
  while ( (charCode = *symbol++) ) {

    int code = mapChar(charCode);
    if (code < 0) {
      return code;
    }

    /* convert mapped code to index pair for our primary and secondary nodes */
    indexPrimary   = code & 3;
    indexSecondary = code >> 3;

    if (!primaryNode->children[indexPrimary]) {
      if (!(primaryNode->children[indexPrimary] = allocSNode())) {
        return ERR_OUT_OF_MEMORY;
      }
    }

    secondaryNode = primaryNode->children[indexPrimary];

    if (!secondaryNode->children[indexSecondary]) {
      if (!(secondaryNode->children[indexSecondary] = allocPNode(primaryNode, charCode))) {
        return ERR_OUT_OF_MEMORY;
      }
    }
    primaryNode = secondaryNode->children[indexSecondary];
    symbolLength++;
  }


  if (symbolLength > maxSymbolLength) {
    maxSymbolLength = symbolLength;
  }

  // If this is the first time we landed on this particular PNode, it's a new symbol
  if (!primaryNode->count++) {
    return nextSymbolID++;
  } else {
    return ERR_DUPLICATE_SYMBOL;
  }
}


