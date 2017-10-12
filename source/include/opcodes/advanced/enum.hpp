//****************************************************************************//
//**                                                                        **//
//** File:         opcodes/advanced/enum.hpp                                **//
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

#ifndef _VM_DEF_ADVANCED_OPCODES_HPP_
#define _VM_DEF_ADVANCED_OPCODES_HPP_

// Advanced Instruction set. These are invoked by the scalar _ADV prefix. Advanced insructions provide various extra
// functions that otherwise would require the use of native function calls to expose.

typedef enum {

  // Implementation Level 0 : 32-bit integer only //////////////////////////////////////////////////////////////////////

  // register indirect, scale indexed
  // ld.x (rS,rI,#s), rD
  _LD_RII_8, _LD_RII_16, _LD_RII_32,

  // register indirect, scale indexed
  // st.x rS, (rD,rI,#d)
  _ST_RII_8, _ST_RII_16, _ST_RII_32,

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

  MAX_ADV
} AdvancedOp;


// Constants for the load constant operators
typedef enum {
  // Common multiples of PI
  CONST_PI         = 0,
  CONST_2PI        = 1,
  CONST_HALF_PI    = 2,
  CONST_INV_PI     = 3,

  // Golden ratio
  CONST_PHI        = 4,

  // Euler's Number
  CONST_E          = 4,

  // Pythagoras' Constant
  CONST_SQRT_2     = 5,
  CONST_INV_SQRT_2 = 6,

  // Theodorus' Constant
  CONST_SQRT_3     = 7,

  // Root of 5, used in several other definitions
  CONST_SQRT_5     = 8,

  // Binary natural log
  CONST_LN_2       = 9,
  CONST_INV_LN_2   = 10,

  // Misc - Universal Parabolic Constant
  CONST_UNIPB      = 11,
  MAX_CONST        = 16 // for now
} AdvancedOpConstant;

#endif

