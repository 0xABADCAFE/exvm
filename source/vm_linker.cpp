//****************************************************************************//
//**                                                                        **//
//** File:         vm_linker.cpp                                            **//
//** Description:  VMSLinker class definition                               **//
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

#include "include/vm_linker.hpp"

#include <new>

using namespace ExVM;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Linker Constructor
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Linker::Linker(uint32 defSegmentSize, uint32 defSegmentDelta) :
  codeSymbols(0),
  nativeCodeSymbols(0),
  dataSymbols(0),
  rawSegments(0),
  numRawSegments(0),
  currSize(defSegmentSize),
  delta(defSegmentDelta)
{
  debuglog(LOG_DEBUG, "Created Linker");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Linker Destructor
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Linker::~Linker() {
  if (codeSymbols) {
    delete codeSymbols;
  }
  if (nativeCodeSymbols) {
    delete nativeCodeSymbols;
  }
  if (dataSymbols) {
    delete dataSymbols;
  }
  if (rawSegments) {
    std::free(rawSegments);
  }
  debuglog(LOG_DEBUG, "Destroyed Linker");
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Linker::defineSymbol()
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Linker::defineSymbol(SymbolMap*& map, const char* name, const void* address) {
  // Check #1 make sure the SymbolMap exists
  if (
    !map &&
    !(map = new(std::nothrow)SymbolMap())
  ) {
    debuglog(LOG_ERROR, "Unable to allocate SymbolMap");
    return Error::OUT_OF_MEMORY;
  }
  return map->define(name, address);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Linker::addRawSegment
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Linker::addRawSegment(RawSegmentData* rawSegment) {
  if (!rawSegment) {
    debuglog(LOG_ERROR, "Unable to add RawSegmentData at null address");
    return Error::ILLEGAL_ARGUMENT;
  }

  // First time here? We need to allocate the RawSegmentData pointer table
  if (
    !rawSegments ||
    !(rawSegments = (RawSegmentData**)std::calloc(currSize, sizeof(RawSegmentData*)))
  ) {
    debuglog(LOG_ERROR, "Unable to allocate initial RawSegmentData pointer table for %u entries", currSize);
    return Error::OUT_OF_MEMORY;
  }

  // TODO - scan the table and make sure we aren't adding the same RawSegmentData address again

  // If the new segment will overflow the table, grow it now
  if (++numRawSegments >= currSize) {
    uint32 newSize = currSize + delta;
    RawSegmentData** growSegments = (RawSegmentData**)std::realloc(rawSegments, newSize * sizeof(RawSegmentData*));
    if (!growSegments) {
      debuglog(LOG_ERROR, "Unable to grow RawSegmentData pointer table to %u entries", newSize);
      return Error::OUT_OF_MEMORY;
    }

    rawSegments = growSegments;
    currSize    = newSize;
    debuglog(LOG_INFO, "Expanded Symbol table to %u entries", currSize);
  }
}

