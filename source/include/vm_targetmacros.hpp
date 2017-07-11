//****************************************************************************//
//**                                                                        **//
//** File:         vm_targetmacros.hpp                                      **//
//** Description:  Virtual Machine host specific macro definitions          **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2001-08-14                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

#ifndef _VM_TARGETMACROS_HPP_
#define _VM_TARGETMACROS_HPP_

#if (X_ENDIAN == XA_BIGENDIAN)
  // Big endian (680x0/Coldfire/PowerPC/Alpha/Delta/MIPS/ARM/SPARC/Radix...etc)
  // Instruction word layout [opcode byte][operand byte]
  #define  OPCD_BYTE 0
  #define  OPRD_BYTE 1
  #define  REGOFS_8 7
  #define  REGOFS_16 3
  #define  REGOFS_32 1
  #define  REGOFS_S(x) (8-(x))
  #define  REGOFS_P 1
  #define  REG_MSW 0
  #define  REG_LSW 1
  #define  EX_ADDR_32 1
  #define  _EX_U8_1 ((vm->pc.extU8)[0])
  #define  _EX_U8_2 ((vm->pc.extU8)[1])
#else
  // Little endian (x86)
  // Instruction word layout [operand byte][opcode byte]
  #define  OPCD_BYTE 1
  #define  OPRD_BYTE 0
  #define  REGOFS_8 0
  #define  REGOFS_16 0
  #define  REGOFS_32 0
  #define  REGOFS_S(x) 0
  #define  REGOFS_P 0
  #define  REG_MSW 1
  #define  REG_LSW 0
  #define  EX_ADDR_32 0
  #define  _EX_U8_1 ((vm->pc.extU8)[1])
  #define  _EX_U8_2 ((vm->pc.extU8)[0])
#endif

#define _SI(x)  (((x)&0x00F0)>>4)       // small immediate
#define _RS(x)  (((x)&0x00F0)>>4)       // source register in 2 operand
#define _RD(x)  ((x)&0x000F)            // dest register in 2 operand
#define _RX(x)  ((x)&0x000F)            // source/dest register in 1 operand
#define _SC(x)  ((x)>>8)                // scale
#define _RI(x)  ((x)&0xF)               // index register
#define _B8(x)  ((sint8)((x)&0xFF))     // 8-bit branch (is operand byte)
#define _EX_U16 (*vm->pc.extU16++)
#define _EX_U32 (*vm->pc.extU32++)
#define _EX_U64 (*vm->pc.extU64++)
#define _EX_S16 (*vm->pc.extS16++)
#define _EX_S32 (*vm->pc.extS32++)
#define _EX_S64 (*vm->pc.extS64++)

#if X_PTRSIZE == XA_PTRSIZE64
  #define PTR_CH   _pch
  #define PTR_U8   _pu8
  #define PTR_U16  _pu16
  #define PTR_U32  _pu32
  #define PTR_U64  _pu64
  #define PTR_S8   _ps8
  #define PTR_S16  _ps16
  #define PTR_S32  _ps32
  #define PTR_S64  _ps64
  #define PTR_F32  _pf32
  #define PTR_F64  _pf64

#else
  #define PTR_CH   _pch[REGOFS_P]
  #define PTR_U8   _pu8[REGOFS_P]
  #define PTR_U16  _pu16[REGOFS_P]
  #define PTR_U32  _pu32[REGOFS_P]
  #define PTR_U64  _pu64[REGOFS_P]
  #define PTR_S8   _ps8[REGOFS_P]
  #define PTR_S16  _ps16[REGOFS_P]
  #define PTR_S32  _ps32[REGOFS_P]
  #define PTR_S64  _ps64[REGOFS_P]
  #define PTR_F32  _pf32[REGOFS_P]
  #define PTR_F64  _pf64[REGOFS_P]

#endif

#ifdef VM_FULL_DEBUG
  #define _DECLARE_DATA_SYMBOL(x)               \
  uint16 x = _EX_U16;                         \
  if (x >= vm->dataSymbolCount) {             \
    vm->status = VMDefs::UNKNOWN_DATA_SYMBOL; \
    printf("Runtime error: Unknown data symbol : %d\n", (int)x); \
    vm->dump();                               \
    _THROW(-1)                                \
  }
#else
  #define _DECLARE_DATA_SYMBOL(x)               \
  uint16 x = _EX_U16;                         \
  if (x >= vm->dataSymbolCount) {             \
    vm->status = VMDefs::UNKNOWN_DATA_SYMBOL; \                             \
    _THROW(-1)                                \
  }
#endif

#endif
