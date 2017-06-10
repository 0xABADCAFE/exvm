//****************************************************************************//
//**                                                                        **//
//** File:         vminline.hpp                                             **//
//** Description:  Virtual Machine Core definitions                         **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2001-08-29                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

#ifndef _VM_INLINE_HPP_
#define _VM_INLINE_HPP_

///////////////////////////////////////////////////////////////////////////////
//
//  Register access
//
///////////////////////////////////////////////////////////////////////////////

// obtain pointer to actual register operand
inline void*    VMCore::GPR::data8()        { return &_u8[REGOFS_8];    }
inline void*    VMCore::GPR::data16()       { return &_u16[REGOFS_16];  }
inline void*    VMCore::GPR::data32()       { return &_u32[REGOFS_32];  }
inline void*    VMCore::GPR::data64()       { return &_u64;             }
inline void*    VMCore::GPR::data(uint32 s) { return &_u8[REGOFS_S(s)]; }

// obtain pointer interpretation of register operand

inline char*    &VMCore::GPR::pCh()         { return PTR_CH;  }
inline uint8*   &VMCore::GPR::pU8()         { return PTR_U8;  }
inline uint16*  &VMCore::GPR::pU16()        { return PTR_U16; }
inline uint32*  &VMCore::GPR::pU32()        { return PTR_U32; }
inline uint64*  &VMCore::GPR::pU64()        { return PTR_U64; }
inline sint8*   &VMCore::GPR::pS8()         { return PTR_S8;  }
inline sint16*  &VMCore::GPR::pS16()        { return PTR_S16; }
inline sint32*  &VMCore::GPR::pS32()        { return PTR_S32; }
inline sint64*  &VMCore::GPR::pS64()        { return PTR_S64; }
inline float32* &VMCore::GPR::pF32()        { return PTR_F32; }
inline float64* &VMCore::GPR::pF64()        { return PTR_F64; }

// obtain reference to actual register operand (for direct reading/writing)

inline uint8&   VMCore::GPR::u8()           { return _u8[REGOFS_8];   }
inline uint16&  VMCore::GPR::u16()          { return _u16[REGOFS_16]; }
inline uint32&  VMCore::GPR::u32()          { return _u32[REGOFS_32]; }
inline uint64&  VMCore::GPR::u64()          { return _u64;            }
inline sint8&   VMCore::GPR::s8()           { return _s8[REGOFS_8];   }
inline sint16&  VMCore::GPR::s16()          { return _s16[REGOFS_16]; }
inline sint32&  VMCore::GPR::s32()          { return _s32[REGOFS_32]; }
inline sint64&  VMCore::GPR::s64()          { return _s64;            }
inline float32& VMCore::GPR::f32()          { return _f32[REGOFS_32]; }
inline float64& VMCore::GPR::f64()          { return _f64;            }

// obtain 32-bit register halves
inline uint32&  VMCore::GPR::getMSW()       { return _u32[REG_MSW]; }
inline uint32&  VMCore::GPR::getLSW()       { return _u32[REG_LSW]; }

#endif
