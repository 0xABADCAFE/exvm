//****************************************************************************//
//**                                                                        **//
//** File:         opcodes/scalar/enum.hpp                                  **//
//** Description:  Virtual Machine definitions                              **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2001-08-14                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

#ifndef _VM_DEF_SCALAR_OPCODES_L1_HPP_
#define _VM_DEF_SCALAR_OPCODES_L1_HPP_

  // beq.x rS,rD,label
  // branch taken if rS == rD
  _BEQ_F32,

  // bgreq.x rS,rD,label
  // branch taken if rS => rD
  _BGREQ_F32,

  // bgr.x rS,rD,label
  // branch taken if rS > rD
  _BGR_F32,

  // cast group /////////////////////////////////////////

  // widening

  // signed extension, signed to float
  _S8_2_F32,
  _S16_2_F32,
  _S32_2_F32,

  // unsigned to float
  // unsigned extension must be implemented in virtual code
  _U8_2_F32,
  _U16_2_F32,
  _U32_2_F32,

  // narrowing, double to float / float to signed
  // double/float to unsigned must be implemented in virtual code
  _F32_2_S32,
  _F32_2_S16,
  _F32_2_S8,

  // Arithmetic commands, data treat as signed integer / float
  // add.x rS,rD (rD += rS)
  _ADD_F32,

  // sub.x rS,rD (rD -= rS)
  _SUB_F32,

  // mul.x rS,rD (rD *= rS)
  _MUL_F32,

  // div.x rS,rD (rD /= rS)
  _DIV_F32,

  // mod.x rS,rD (rD %= rS)
  _MOD_F32,

  // neg.x rS,rD (rD = -rS)
  _NEG_F32,

  // min.x rS,RD
  _MIN_F32,

  // max.x rS,RD
  _MAX_F32,

#endif

