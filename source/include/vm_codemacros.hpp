//****************************************************************************//
//**                                                                        **//
//** File:         vm_codemacros.hpp                                        **//
//** Description:  Virtual Machine static code macro definitions            **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2001-08-29                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//


#ifndef _VM_CODEMACROS_HPP_
#define _VM_CODEMACROS_HPP_
#include "vm.hpp"

#if (X_ENDIAN == XA_BIGENDIAN)

inline uint16 _float32MSW(float32 f) {
  // returns the most significant 16-bits of a 32-bit floating point value
  union {
    float32 f;
    uint16 u[2];
  } u;
  u.f = f;
  return u.u[0];
}

inline uint16 _float32LSW(float32 f) {
  // returns the most significant 16-bits of a 32-bit floating point value
  union {
    float32 f;
    uint16 u[2];
  } u;
  u.f = f;
  return u.u[1];
}

// covnert a 32-bit integer immediate into 16-bit words
#define _INLINE32(x) (uint16)(( (uint32)(x) ) >> 16), \
                     (uint16)(( (uint32)(x) ) & 0xFFFF)

#if X_PTRSIZE == XA_PTRSIZE64
#define _INLINEPTR(x) (uint16)(( (uint64)(x) ) >> 48), \
                      (uint16)((( (uint64)(x) ) >> 32) & 0xFFFF), \
                      (uint16)((( (uint64)(x) ) >> 16) & 0xFFFF), \
                      (uint16)(( (uint64)(x) ) & 0xFFFF)
#else
#define _INLINEPTR(x) (uint16)0, \
                      (uint16)0, \
                      (uint16)((( (uint32)(x) ) >> 16) & 0xFFFF), \
                      (uint16)(((uint32)(x)) & 0xFFFF)
#endif

// convert a 32-bit float immediate into 16-bit words
#define _INLINEF32(x) (_float32MSW((x))), \
                      (_float32LSW((x)))

#else

inline uint16 _float32MSW(float32 f) {
  // returns the most significant 16-bits of a 32-bit floating point value
  union { float32 f; uint16 u[2]; } u;
  u.f = f;
  return u.u[1];
}

inline uint16 _float32LSW(float32 f) {
  // returns the most significant 16-bits of a 32-bit floating point value
  union { float32 f; uint16 u[2]; } u;
  u.f = f;
  return u.u[0];
}

// covnert a 32-bit integer immediate into 16-bit words
#define _INLINE32(x) (( (uint32)(x) ) & 0xFFFF), \
                     (( (uint32)(x) ) >> 16)

#if X_PTRSIZE == XA_PTRSIZE64
  #define _INLINEPTR(x) (uint16)(( (uint64)(x) ) & 0xFFFF), \
                        (uint16)((( (uint64)(x) ) >> 16) & 0xFFFF), \
                        (uint16)((( (uint64)(x) ) >> 32) & 0xFFFF), \
                        (uint16)(( (uint64)(x) ) >> 48)
#else
  #define _INLINEPTR(x) (uint16)(( (uint32)(x) ) & 0xFFFF), \
                        (uint16)(( (uint32)(x) ) >> 16), \
                        (uint16)0, \
                        (uint16)0
#endif

// convert a 32-bit float immediate into 16-bit words
#define _INLINEF32(x)  (_float32LSW((x))), \
                       (_float32MSW((x)))

#endif


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// register names
#define _r0 0
#define _r1 1
#define _r2 2
#define _r3 3
#define _r4 4
#define _r5 5
#define _r6 6
#define _r7 7
#define _r8 8
#define _r9 9
#define _r10 10
#define _r11 11
#define _r12 12
#define _r13 13
#define _r14 14
#define _r15 15

// register masks (for save/restore/push/pop)
#define _mr0 1
#define _mr1 2
#define _mr2 4
#define _mr3 8
#define _mr4 16
#define _mr5 32
#define _mr6 64
#define _mr7 128
#define _mr8 256
#define _mr9  512
#define _mr10 1024
#define _mr11 2048
#define _mr12 4096
#define _mr13 8192
#define _mr14 16384
#define _mr15 32768

// Macros that define how to spread the bits of an enumerated Symbol ID between the Opcode and Extension word.
#define _SYM_ID_LOWER(x) (uint16)(sym_id_##x & 0xFFFF)
#define _SYM_ID_UPPER(x) (uint16)((sym_id_##x & 0xF0000) >> 16)

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  begin a named array of 16 bit words representing a code block:
//
//  _VM_CODE(myFunction) {
//
//
//  }; <- don't forget the trailing semicolon!
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#define _VM_CODE(x) uint16 _vmCode##x[] =


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  refer to a named code block:
//
//  uint16* code = _VM_ENTRY(myFunction);
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define _VM_ENTRY(x) (_vmCode##x)

#define _VM_EXTERN(x) extern uint16 _vmCode##x[]

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  obtain the size (in words) of a named code block:
//
//  size_t size = _VM_CODE_SIZE(myFunction);
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define _VM_CODE_SIZE(x) (sizeof(_vmCode##x) / sizeof(uint16))

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  create an opcode word:
//
//  _MKOP(<name>)
//
//  generates the 16-bit word for the named opcode, ie (VMDefs::_<name>) << 8
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#define _MKVOP(x) (VMDefs::_VEC1 << 8 | (VMDefs::_V##x))

#include "opcodes/scalar/codemacros.hpp"
#include "opcodes/advanced/codemacros.hpp"
#include "opcodes/vector/codemacros.hpp"

#endif

