//****************************************************************************//
//**                                                                        **//
//** File:         vm_objectfile.hpp                                        **//
//** Description:  Symbol definitions                                       **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2017-08-14                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

#ifndef _VM_OBJECTFILE_HPP_
  #define _VM_OBJECTFILE_HPP_
  #include "vm.hpp"
  #include "machine.hpp"

namespace ExVM {



  enum {
    OF_MASK_ENDIANNESS    = 0x01,
    OF_MASK_SECTIONS      = 0x06,

    OF_FLAG_BIG_ENDIAN    = 0x00,
    OF_FLAG_LITTLE_ENDIAN = 0x00,

    OF_FLAG_CODE_SECTION  = 0x02, // File contains code section
    OF_FLAG_DATA_SECTION  = 0x04, // File contains data section
  };

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Main ExVN Object File header
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  struct BaseFileHeader {

    // The first 8 bytes of the file are interpreted the same way regardless of machine word size or endianness.

    //  0 : Magic
    char  fileId[4];

    //  4 : Indicates the minimum VM Capability Level
    uint8 reqiredCapabilityLevel;

    //  5 : File flags, indicate the endianness of the data in the file.
    uint8 flags;

    //  6 : reserved
    uint8 reserved[2];

    // From now on, we have data that must be potentially byteswapped on loadoing.

    //  8 : Version of the code in the object file
    uint16 version;

    // 10 : Revision of the code in the object file
    uint16 revision;

    // 12 : Total size of the object data, in bytes.
    uint32 totalSize;

    // 16 : Number of export symbols. Each record corresponds to a SymbolRef containing 2 32-bit values. An empty export
    //      table is impossible because a file that exports nothing can have no action taken on it
    uint32 exportSymbolTableLength;
  };

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Code Header, only present when mainHeader.flags & OF_FLAG_CODE_SECTION
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  struct CodeHeader {

    // Total size of the code segment, in bytes, excluding tail padding (always to 8 bytes).
    uint32 codeSegmentSize;

    // Number of literals in the code segment to swap. Each record is a single 32-bit word that represents the
    // offset from the start of the code segment where a 32-bit literal exists.
    uint32 codeSwapTableLength;

    // Number of import symbols
    uint32 importSymbolTableLength;
  };

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Data Header, only present when mainHeader.flags & OF_FLAG_DATA_SECTION
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  struct DataHeader {

    // Total size of the data segment, in bytes, excluding tail padding (always to 8 bytes).
    uint32 dataSegmentSize;

    // Total size of the name segment, in bytes, excluding tail padding (always to 8 bytes).
    uint32 nameSegmentSize;
    uint32 complexTypesSegmentSize;

    // Number of literals in the code segment to swap. Each record is a single 32-bit word that represents the
    // offset from the start of the code segment where a 32-bit literal exists.
    uint32 codeSwapTableLength;

    // Number of blocks of 16-bit words in the data segment to swap. Each record is a pair of 32-bit values, one for
    // the offset from the start of the data segment where a 16-bit block exists and one for the count of the 16-bit
    // words in the block.
    uint32 data16BitSwapTableLength;

    // Number of blocks of 32-bit words in the data segment to swap. Each record is a pair of 32-bit values, one for
    // the offset from the start of the data segment where a 32-bit block exists and one for the count of the 32-bit
    // words in the block.
    uint32 data32BitSwapTableLength;

    // Number of blocks of 64-bit words in the data segment to swap. Each record is a pair of 32-bit values, one for
    // the offset from the start of the data segment where a 64-bit block exists and one for the count of the 64-bit
    // words in the block.
    uint32 data64BitSwapTableLength;

    // Number of blocks of complex types in the data segment to swap. Each record is a triplet of 32-bit values, one for
    // the offset from the start of the data segment where a complex type block exists, one for the count of the elements
    // in the block and one for the complex type lookup that gives the member count and offset in to the complex types
    // segment data.
    uint32 dataComplexTypeSwapTableLength;

    // Number of complex types in the complex types table. Each record is a pair of 32-bit values, one for the offset
    // from the start of the complex types segment for the structure definition and one for the member count.
    uint32 complexTypesTableLength;
  };

  // Simple datatype used wherever there is a 32-bit offset/count pair such as the various swap tables
  struct OffsetCountPair {
    uint32 offset;
    uint32 count;
  };

  // Simple structure that defines a record in the dataComplexTypeSwapTable
  struct ComplexDataSwapTableEntry : public OffsetCountPair {
    // Additional field for the type lookup
    uint32 type;
  };

  // Enumerations of Complex Type members
  enum {
    CT_ELEMENT_8   = 0,
    CT_ELEMENT_16  = 1,
    CT_ELEMENT_32  = 2,
    CT_ELEMENT_64  = 3,
  };

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Standard Header, when both code and data are present, code is first, data second.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  struct StandardHeader {
    CodeHeader codeHeader;
    DataHeader dataHeader;
  };

#endif
