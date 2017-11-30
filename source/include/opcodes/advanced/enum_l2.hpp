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

  // Logically shift, with mask
  // lslm.32 rS,rB,rM,rD
  _LSLM_64,
  _LSRM_64,

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

  // Fixed 2D vectors : float64[2]
  _SPLAT_V2F64, // splat fill, all elements set to the same value
  _COPY_V2F64,  // copy
  _ADD_V2F64,   // add
  _SUB_V2F64,   // subtract
  _DOT_V2F64,   // dot product
  _SCALE_V2F64, // scale
  _MAGN_V2F64,  // magnitude
  _NORM_V2F64,  // normalise
  _LERP_V2F64,  // interpolate

  _M3X3_V2F64, // transform a set of vec2d using a 4x4 matrix

  // Complex number oberations C2F64, extends the 2D vector operations

  _MUL_C2F64,    // Complex Multiply
  _DIV_C2F64,    // Complex Divide

  // Fixed 3D vectors : float64[3]
  _SPLAT_V3F64, // splat fill, all elements set to the same value
  _COPY_V3F64,  // copy
  _ADD_V3F64,   // add
  _SUB_V3F64,   // subtract
  _CROSS_V3F64, // cross product
  _DOT_V3F64,   // dot product
  _SCALE_V3F64, // scale
  _MAGN_V3F64,  // magnitude
  _NORM_V3F64,  // normalise
  _LERP_V3F64,  // interpolate

  _M4X4_V3F64, // transform a set of vec3d using a 4x4 matrix

#endif

