//****************************************************************************//
//**                                                                        **//
//** File:         vm_gpr.hpp                                               **//
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

#ifndef _VM_CORE_HPP_
# error vm_gpr.hpp must not be included manually!
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// VMCore::GPR
//
// Represents the 64-bit General Purpose Register type for the virtual machine interpreter. The register is realised
// as a set of unions for each supported scalar type.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

union GPR { // General Purpose 64-bit register type
  friend class VMCore;
  private:  // Data arrangement
    union {
      uint8   _u8[8];
      sint8   _s8[8];
    };
    union {
      uint16  _u16[4];
      sint16  _s16[4];
    };
    union {
      uint32  _u32[2];
      sint32  _s32[2];
      float32 _f32[2];
    };
    union {
      uint64  _u64;
      sint64  _s64; 
      float64 _f64;
    };
#if X_PTRSIZE == XA_PTRSIZE64
    // 64-bit pointers use the full width of the register
    union {
      uint8*  _pu8;
      uint16* _pu16;
      uint32* _pu32;
      uint64* _pu64;
    };
    union {
      sint8*  _ps8;
      sint16* _ps16;
      sint32* _ps32;
      sint64* _ps64;
    };
    union {
      float32* _pf32;
      float64* _pf64;
    };
    union {
      char*    _pch; 
      wchar_t* _pwch;
    };
#else
    // 32-bit pointers use only half of the width of the register, but we require that the other half is not used.
    union {
      uint8*  _pu8[2];
      uint16* _pu16[2];
      uint32* _pu32[2];
      uint64* _pu64[2];
    };
    union {
      sint8*  _ps8[2];
      sint16* _ps16[2];
      sint32* _ps32[2];
      sint64* _ps64[2];
    };
    union {
      float32* _pf32[2];
      float64* _pf64[2];
    };
    union {
      char*    _pch[2];
      wchar_t* _pwch[2];
    };
#endif

  public:
    // obtain pointer to actual register operand
    void*     data8();
    void*     data16();
    void*     data32();
    void*     data64();
    void*     data(uint32 s);

    // obtain pointer interpretation of register operand
    char*     &pCh();
    uint8*    &pU8();
    uint16*   &pU16();
    uint32*   &pU32();
    uint64*   &pU64();
    sint8*    &pS8();
    sint16*   &pS16();
    sint32*   &pS32();
    sint64*   &pS64();
    float32*  &pF32();
    float64*  &pF64();

    // obtain reference to actual register operand (for direct reading/writing)
    uint8&    u8();
    uint16&   u16();
    uint32&   u32();
    uint64&   u64();
    sint8&    s8();
    sint16&   s16();
    sint32&   s32();
    sint64&   s64();
    float32&  f32();
    float64&  f64();

    // obtain 32-bit register halves
    uint32&   getMSW();
    uint32&   getLSW();
};
