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

int Linker::defineSymbol(SymbolMap*& map, const char* name, void* address, uint32 symbolIDSize) {
  // Check #1 make sure the SymbolMap exists
  if (
    !map &&
    !(map = new(std::nothrow)SymbolMap(1 << symbolIDSize))
  ) {
    debuglog(LOG_ERROR, "Unable to allocate SymbolMap");
    return Error::OUT_OF_MEMORY;
  }
  return map->define(name, address);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Linker::addRawSegment()
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Linker::addRawSegment(RawSegmentData* rawSegment) {
  if (!rawSegment) {
    debuglog(LOG_ERROR, "Unable to add RawSegmentData at null address");
    return Error::ILLEGAL_ARGUMENT;
  }

  // First time here? We need to allocate the RawSegmentData pointer table
  if (
    !rawSegments &&
    !(rawSegments = (RawSegmentData**)std::calloc(currSize, sizeof(RawSegmentData*)))
  ) {
    debuglog(LOG_ERROR, "Unable to allocate initial RawSegmentData pointer table for %u entries", currSize);
    return Error::OUT_OF_MEMORY;
  }

  // TODO - scan the table and make sure we aren't adding the same RawSegmentData address again

  // If the new segment will overflow the table, grow it now

  uint32 entry = numRawSegments;
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

  rawSegments[entry] = rawSegment;
  debuglog(LOG_INFO, "Added RawSegmentData instance at %p as entry %u", rawSegment, entry);

  return Error::SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Linker::link()
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Linker::link() {

  debuglog(LOG_INFO, "Beginning link process");

  int result = enumerateAllSymbols();
  if (result == Error::SUCCESS) {
    result = resolveToEnumerated();
  }
  return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Linker::enumerateAllSymbols()
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Linker::enumerateAllSymbols() {
  for (uint32 i = 0; i < numRawSegments; i++) {
    RawSegmentData* segment = rawSegments[i];

    debuglog(LOG_INFO, "Processing RawSegmentData[%u] %p Export Symbols", i, segment);
    for (uint32 j = 0; j < segment->exportTableLength; j++) {
      RawSegmentData::SymbolRef* symbolRef  = &segment->exportTable[j];
      const char*                symbolName = symbolRef->getSymbolName(segment->nameSegment);
      int                        result;

      // Process the next symbol
      switch (symbolRef->getSymbolType()) {

        case RawSegmentData::TYPE_CODE:
          {
            uint16* codeAddress = segment->codeSegment + symbolRef->offset;
            debuglog(LOG_INFO, "Processing exported TYPE_CODE symbol '%s' at %p", symbolName, codeAddress);
            result = defineCode(symbolName, codeAddress);
          }
          break;

        case RawSegmentData::TYPE_DATA:
          {
            uint8* dataAddress = (uint8*)segment->dataSegment + symbolRef->offset;
            debuglog(LOG_INFO, "Processing exported TYPE_DATA symbol '%s' at %p", symbolName, dataAddress);
            result = defineData(symbolName, dataAddress);
          }
          break;

        // No other symbol types can be exported, so anything else here is an error
        default:
          debuglog(LOG_ERROR, "Illegal type for exported symbol '%s', must be one of TYPE_CODE or TYPE_DATA", symbolName);
          result = Error::ILLEGAL_EXPORT_TYPE;
          break;
      }

      if (result < Error::SUCCESS) {
        return result;
      }
    }

  }

  return Error::SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Linker::resolveToEnumerated()
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Linker::resolveToEnumerated() {

  #define MODIFY_OPCODE_FOR_CODE(o, s)   (o) &= 0xFF00; (o) |= ((s) & 0xFF0000) >> 16;
  #define MODIFY_OPCODE_FOR_NATIVE(o, s) (o) &= 0xFF00; (o) |= ((s) & 0xFF0000) >> 16;
  #define MODIFY_OPCODE_FOR_DATA(o, s)   (o) &= 0xFF0F; (o) |= ((s) & 0x0F0000) >> 12;

  for (uint32 i = 0; i < numRawSegments; i++) {
    RawSegmentData* segment = rawSegments[i];

    debuglog(LOG_INFO, "Processing RawSegmentData[%u] %p Import Symbols", i, segment);
    for (uint32 j = 0; j < segment->importTableLength; j++) {
      RawSegmentData::SymbolRef* symbolRef  = &segment->importTable[j];
      const char*                symbolName = symbolRef->getSymbolName(segment->nameSegment);
      const Symbol*              symbol     = 0;

      // The offset points to the space immediately after the instruction but we will be modifyin the instruction
      // word too. Perhaps we should change the specification to match this behaviour.
      uint16*                    injectAddr = segment->codeSegment + symbolRef->offset - 1;

      // Capture the opcode word as the upper bits of the symbol ID are part of it.
      uint16                     opcodeWord = *injectAddr;
      int                        symbolID;

      // Process the next symbol
      switch (symbolRef->getSymbolType()) {

        case RawSegmentData::TYPE_CODE:
          {
            debuglog(LOG_INFO, "Processing imported TYPE_CODE symbol '%s'", symbolName);
            if (!codeSymbols) {
              debuglog(LOG_ERROR, "TYPE_CODE symbol table is empty");
              return Error::INVALID_SEGMENT;
            }
            symbolID = codeSymbols->getID(symbolName);
            if (symbolID < 0) {
              debuglog(LOG_ERROR, "TYPE_CODE symbol table '%s' did not resolve", symbolName);
              return symbolID;
            }

            //debuglog(LOG_DEBUG, "\t\tOpcode word before: 0x%04X", opcodeWord);

            MODIFY_OPCODE_FOR_CODE(opcodeWord, symbolID)

            //debuglog(LOG_DEBUG, "\t\tOpcode word after: 0x%04X", opcodeWord);

            symbol = codeSymbols->get(symbolID);
            debuglog(LOG_INFO, "\tResolved symbol '%s' to ID %d at %p", symbolName, symbolID, symbol->address.code);
          }
          break;

        case RawSegmentData::TYPE_DATA:
          {
            debuglog(LOG_INFO, "Processing imported TYPE_DATA symbol '%s'", symbolName);
            if (!dataSymbols) {
              debuglog(LOG_ERROR, "TYPE_DATA symbol table is empty");
              return Error::INVALID_SEGMENT;
            }
            symbolID = dataSymbols->getID(symbolName);
            if (symbolID < 0) {
              debuglog(LOG_ERROR, "TYPE_DATA symbol table '%s' did not resolve", symbolName);
              return symbolID;
            }

            //debuglog(LOG_DEBUG, "\t\tOpcode word before: 0x%04X", opcodeWord);

            MODIFY_OPCODE_FOR_DATA(opcodeWord, symbolID)

            //debuglog(LOG_DEBUG, "\t\tOpcode word after: 0x%04X", opcodeWord);

            symbol = dataSymbols->get(symbolID);
            debuglog(LOG_INFO, "\tResolved symbol '%s' to ID %d at %p", symbolName, symbolID, symbol->address.data);
          }
          break;

        case RawSegmentData::TYPE_NATIVE:
          {
            debuglog(LOG_INFO, "Processing imported TYPE_NATIVE symbol '%s'", symbolName);
            if (!nativeCodeSymbols) {
              debuglog(LOG_ERROR, "TYPE_NATIVE symbol table is empty");
              return Error::INVALID_SEGMENT;
            }
            symbolID = nativeCodeSymbols->getID(symbolName);
            if (symbolID < 0) {
              debuglog(LOG_ERROR, "TYPE_NATIVE symbol table '%s' did not resolve", symbolName);
              return symbolID;
            }

            //debuglog(LOG_DEBUG, "\t\tOpcode word before: 0x%04X", opcodeWord);

            MODIFY_OPCODE_FOR_NATIVE(opcodeWord, symbolID)

            //debuglog(LOG_DEBUG, "\t\tOpcode word after: 0x%04X", opcodeWord);

            symbol = nativeCodeSymbols->get(symbolID);
            debuglog(LOG_INFO, "\tResolved symbol '%s' to ID %d at %p", symbolName, symbolID, symbol->address.raw);
          }
          break;

        // No other symbol types can be exported, so anything else here is an error
        default:
          debuglog(LOG_ERROR, "Illegal type for imported symbol '%s', must be one of TYPE_CODE, TYPE_DATA or TYPE_NATIVE", symbolName);
          return Error::ILLEGAL_EXPORT_TYPE;
          break;
      }

      debuglog(LOG_INFO, "Injecting symbol '%s' ID %d into code segment at offset %u [%p]", symbolName, symbolID, symbolRef->offset, injectAddr);
      *injectAddr++ = opcodeWord;
      *injectAddr   = (uint16)(symbolID & 0xFFFF);
    }

  }

  return Error::SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Linker::getExecutable()
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Executable* Linker::getExecutable() {
  Executable* executable = Executable::allocate(
    nativeCodeSymbols ? nativeCodeSymbols->size() : 0,
    codeSymbols       ? codeSymbols->size()       : 0,
    dataSymbols       ? dataSymbols->size()       : 0
  );

  if (nativeCodeSymbols) {
    const Symbol* native = nativeCodeSymbols->getList();
    for (int i = 0; i < executable->nativeCodeCount; i++) {
      executable->nativeCodeAddresses[i] = native[i].address.native;
    }
  }

  if (codeSymbols) {
    const Symbol* code = codeSymbols->getList();
    for (int i = 0; i < executable->codeCount; i++) {
      executable->codeAddresses[i] = code[i].address.code;
    }

    // Look for a main entry point (TODO this should be something predefined)
    int main = codeSymbols->getID("main");
    if (main >= 0) {
      executable->main = main;
    }
  }

  if (dataSymbols) {
    const Symbol* data = dataSymbols->getList();
    for (int i = 0; i < executable->dataCount; i++) {
      executable->dataAddresses[i] = data[i].address.data;
    }
  }

  return executable;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Executable::allocate()
//
// Allocate a new Executable structure with the space for the symbol lookup tables allocated inline.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Executable* Executable::allocate(uint32 nativeCount, uint32 codeCount, uint32 dataCount) {
  size_t baseAllocSize   = sizeof(Executable);
  size_t nativeTableSize = nativeCount * sizeof(NativeCall);
  size_t codeTableSize   = codeCount   * sizeof(uint16*);
  size_t dataTableSize   = dataCount   * sizeof(void*);

  // Try to allocate enought space for all of the above in a single block
  size_t totalAllocSize  = baseAllocSize + nativeTableSize + codeTableSize + dataTableSize;
  uint8* baseAddress     = (uint8*)std::calloc(totalAllocSize, 1);
  if (!baseAddress) {
    debuglog(LOG_ERROR, "Unable to allocate %u bytes for Executable structure\n", totalAllocSize);
    return 0;
  }

  // Populate the base Executable instance
  Executable* executable      = (Executable*)baseAddress;
  executable->nativeCodeCount = nativeCount;
  executable->codeCount       = codeCount;
  executable->dataCount       = dataCount;

  // Set up the table pointers to
  baseAddress += baseAllocSize;
  executable->nativeCodeAddresses = (NativeCall*)baseAddress;

  baseAddress += nativeTableSize;
  executable->codeAddresses = (uint16**)baseAddress;

  baseAddress += codeTableSize;
  executable->dataAddresses = (void**)baseAddress;

  debuglog(LOG_INFO, "Allocated Executable structure at %p\n", executable);

  return executable;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Executable::release(Executable* executable) {
  if (executable) {
    std::free(executable);
  }
}
