//****************************************************************************//
//**                                                                        **//
//** File:         vm_loader.hpp                                            **//
//** Description:  Loader definitions                                       **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2017-07-12                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

#ifndef _VM_LOADER_HPP_
  #define _VM_LOADER_HPP_
  #include "vm_rawsegment.hpp"

namespace ExVM {

  class ObjectFile {

    private:
      // Minimal 8-byte header
      struct FileHeader {
        enum {
          // Level 0 requires 32-bit integer supporting runtime.
          COMPATIBILITY_LEVEL_0  = 0x00,

          // Level 1 requires 32-bit integer and float runtime.
          COMPATIBILITY_LEVEL_1  = 0x01,

          // Level 2 requires 64-bit integer and float runtime.
          COMPATIBILITY_LEVEL_2  = 0x02,

          // Level 3 requires 64-bit integer, flot and memory model.
          COMPATIBILITY_LEVEL_3  = 0x03,

          // Flags

          // Bitfield indicating file contents. A file must contain either a code
          // segment, a data segment or both. It cannot contain neither.
          CONTAINS_CODE_ONLY     = 0x01,
          CONTAINS_DATA_ONLY     = 0x02,
          CONTAINS_CODE_AND_DATA = 0x03,
          MASK_CONTAINS          = 0x03,

          // Set if the code has external dependencies (an import table). A file
          // must contain an export table, but does not have to import anything.
          HAS_DEPENDENCIES       = 0x04,

          // Set if the file contains a segment that indicates where blocks of
          // 16/32/64 bit elements exist that may require swapping to the host
          // representation on loading.
          HAS_BLOCK_SWAP_SEGMENT = 0x08,

          // Set if the file contains a segment that describes embedded data
          // in the form of complex structures that may require member field
          // swapping on loading.
          HAS_STRUCT_DICTIONARY  = 0x10,

          // Set if the multibyte data in the file is stored in big_endian
          // byte order.
          IS_BIG_ENDIAN          = 0x80
        };

        // Magic identifier
        char   magic[4];

        // Version of the file format (8.8)
        uint8  version;
        uint8  revision;

        // Minimum Host Compatibility Level
        uint8  minCompatLevel;

        // Flags
        uint8  flags;

      };

      struct ChunkHeader {
        char  type[4];
        int32 size;
      };

  };

}

#endif
