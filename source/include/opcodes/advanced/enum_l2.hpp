//****************************************************************************//
//**                                                                        **//
//** File:         opcodes/advanced/enum.hpp                                **//
//** Description:  Virtual Machine definitions                              **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2017-10-14                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

#ifndef _VM_DEF_ADVANCED_OPCODES_L2_HPP_
#define _VM_DEF_ADVANCED_OPCODES_L2_HPP_

  // Implementation Level 2 : 64-bit integer / 64-bit floating point ///////////////////////////////////////////////////

  // register indirect, scale indexed
  // ld.x (rS,rI,#s), rD
  _LD_RII_64,

  // register indirect, scale indexed
  // st.x rS, (rD,rI,#d)
  _ST_RII_64,

  // Load constants
  _LD_CONST_F64,

  // Multiply Add
  _MADD_F64,

  // Roots
  _SQRT_F64,
  _ISQRT_F64,

  // Trig - Arc
  _ACOS_F64,
  _ASIN_F64,
  _ATAN_F64,

  // Trig - Regular
  _COS_F64,
  _SIN_F64,
  _TAN_F64,

  // Trig - Hyperbolic
  _COSH_F64,
  _SINH_F64,
  _TANH_F64,

  // Trig - Simultaneous sine and cosine
  _SINCOS_F64,

  // Exponentiation and powers
  _EXP_F64,
  _POW_F64,

  // Logarithms
  _LOGN_F64,
  _LOG2_F64,
  _LOG10_F64,
  _LOGX_F64,

  // Truncation and rounding
  _CEIL_F64,
  _FLOOR_F64,

  // Interpolaton
  _LERP_F64,

#endif

