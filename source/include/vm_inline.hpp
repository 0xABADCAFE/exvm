//****************************************************************************//
//**                                                                        **//
//** File:         vm_inline.hpp                                            **//
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

namespace ExVM {

///////////////////////////////////////////////////////////////////////////////
//
//  Register access
//
///////////////////////////////////////////////////////////////////////////////

  // obtain pointer to actual register operand
  inline void*    Interpreter::GPR::data8()        { return &_u8[REGOFS_8];    }
  inline void*    Interpreter::GPR::data16()       { return &_u16[REGOFS_16];  }
  inline void*    Interpreter::GPR::data32()       { return &_u32[REGOFS_32];  }
  inline void*    Interpreter::GPR::data64()       { return &_u64;             }
  inline void*    Interpreter::GPR::data(uint32 s) { return &_u8[REGOFS_S(s)]; }

  // obtain pointer interpretation of register operand

  inline char*    &Interpreter::GPR::pCh()         { return PTR_CH;  }
  inline uint8*   &Interpreter::GPR::pU8()         { return PTR_U8;  }
  inline uint16*  &Interpreter::GPR::pU16()        { return PTR_U16; }
  inline uint32*  &Interpreter::GPR::pU32()        { return PTR_U32; }
  inline uint64*  &Interpreter::GPR::pU64()        { return PTR_U64; }
  inline sint8*   &Interpreter::GPR::pS8()         { return PTR_S8;  }
  inline sint16*  &Interpreter::GPR::pS16()        { return PTR_S16; }
  inline sint32*  &Interpreter::GPR::pS32()        { return PTR_S32; }
  inline sint64*  &Interpreter::GPR::pS64()        { return PTR_S64; }
  inline float32* &Interpreter::GPR::pF32()        { return PTR_F32; }
  inline float64* &Interpreter::GPR::pF64()        { return PTR_F64; }

  // obtain reference to actual register operand (for direct reading/writing)

  inline uint8&   Interpreter::GPR::u8()           { return _u8[REGOFS_8];   }
  inline uint16&  Interpreter::GPR::u16()          { return _u16[REGOFS_16]; }
  inline uint32&  Interpreter::GPR::u32()          { return _u32[REGOFS_32]; }
  inline uint64&  Interpreter::GPR::u64()          { return _u64;            }
  inline sint8&   Interpreter::GPR::s8()           { return _s8[REGOFS_8];   }
  inline sint16&  Interpreter::GPR::s16()          { return _s16[REGOFS_16]; }
  inline sint32&  Interpreter::GPR::s32()          { return _s32[REGOFS_32]; }
  inline sint64&  Interpreter::GPR::s64()          { return _s64;            }
  inline float32& Interpreter::GPR::f32()          { return _f32[REGOFS_32]; }
  inline float64& Interpreter::GPR::f64()          { return _f64;            }

  // obtain 32-bit register halves
  inline uint32&  Interpreter::GPR::getMSW()       { return _u32[REG_MSW]; }
  inline uint32&  Interpreter::GPR::getLSW()       { return _u32[REG_LSW]; }

}
#endif
