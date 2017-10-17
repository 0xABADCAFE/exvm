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

#ifndef _VM_DEF_ADVANCED_OPCODES_L1_HPP_
#define _VM_DEF_ADVANCED_OPCODES_L1_HPP_

  // Implementation Level 1 : 32-bit integer / 32-bit floating point ///////////////////////////////////////////////////

  // Load constants
  _LD_CONST_F32,

  // Multiply Add
  _MADD_F32,

  // Roots
  _SQRT_F32,
  _ISQRT_F32,

  // Trig - Arc
  _ACOS_F32,
  _ASIN_F32,
  _ATAN_F32,

  // Trig - Regular
  _COS_F32,
  _SIN_F32,
  _TAN_F32,

  // Trig - Hyperbolic
  _COSH_F32,
  _SINH_F32,
  _TANH_F32,

  // Trig - Simultaneous sine and cosine
  _SINCOS_F32,

  // Exponentiation and powers
  _EXP_F32,
  _POW_F32,

  // Logarithms
  _LOGN_F32,
  _LOG2_F32,
  _LOG10_F32,
  _LOGX_F32,

  // Truncation and rounding
  _CEIL_F32,
  _FLOOR_F32,

  // Interpolaton
  _LERP_F32,

  // Fixed vectors of float32[3]
  _SPLAT_V3F32, // splat fill, all elements set to the same value
  _COPY_V3F32,  // copy
  _ADD_V3F32,   // add
  _SUB_V3F32,   // subtract
  _CROSS_V3F32, // cross product
  _DOT_V3F32,   // dot product
  _SCALE_V3F32, // scale
  _MAGN_V3F32,  // magnitude
  _NORM_V3F32,  // normalise
  _LERP_V3F32,  // interpolate

#endif

