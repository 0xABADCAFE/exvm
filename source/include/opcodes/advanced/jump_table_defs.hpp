//****************************************************************************//
//**                                                                        **//
//** File:         jump_table_defs.hpp                                      **//
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


// Advanced opcodes
_DECLARE_OP(MADD_F32)
_DECLARE_OP(MADD_F64)
_DECLARE_OP(LD_CONST_F32)
_DECLARE_OP(LD_CONST_F64)
_DECLARE_OP(LD_RII_8)
_DECLARE_OP(LD_RII_16)
_DECLARE_OP(LD_RII_32)
_DECLARE_OP(LD_RII_64)
_DECLARE_OP(ST_RII_8)
_DECLARE_OP(ST_RII_16)
_DECLARE_OP(ST_RII_32)
_DECLARE_OP(ST_RII_64)
_DECLARE_OP(SQRT_F32)
_DECLARE_OP(SQRT_F64)
_DECLARE_OP(ISQRT_F32)
_DECLARE_OP(ISQRT_F64)
_DECLARE_OP(ACOS_F32)
_DECLARE_OP(ACOS_F64)
_DECLARE_OP(ASIN_F32)
_DECLARE_OP(ASIN_F64)
_DECLARE_OP(ATAN_F32)
_DECLARE_OP(ATAN_F64)
_DECLARE_OP(COS_F32)
_DECLARE_OP(COS_F64)
_DECLARE_OP(SIN_F32)
_DECLARE_OP(SIN_F64)
_DECLARE_OP(TAN_F32)
_DECLARE_OP(TAN_F64)
_DECLARE_OP(COSH_F32)
_DECLARE_OP(COSH_F64)
_DECLARE_OP(SINH_F32)
_DECLARE_OP(SINH_F64)
_DECLARE_OP(TANH_F32)
_DECLARE_OP(TANH_F64)
_DECLARE_OP(SINCOS_F32)
_DECLARE_OP(SINCOS_F64)
_DECLARE_OP(EXP_F32)
_DECLARE_OP(EXP_F64)
_DECLARE_OP(POW_F32)
_DECLARE_OP(POW_F64)
_DECLARE_OP(LOGN_F32)
_DECLARE_OP(LOGN_F64)
_DECLARE_OP(LOG2_F32)
_DECLARE_OP(LOG2_F64)
_DECLARE_OP(LOG10_F32)
_DECLARE_OP(LOG10_F64)
_DECLARE_OP(LOGX_F32)
_DECLARE_OP(LOGX_F64)
_DECLARE_OP(CEIL_F32)
_DECLARE_OP(CEIL_F64)
_DECLARE_OP(FLOOR_F32)
_DECLARE_OP(FLOOR_F64)
_DECLARE_OP(LERP_F32)
_DECLARE_OP(LERP_F64)

_DECLARE_OP(SPLAT_V2F32) // splat fill
_DECLARE_OP(COPY_V2F32)  // copy
_DECLARE_OP(ADD_V2F32)   // add
_DECLARE_OP(SUB_V2F32)   // subtract
_DECLARE_OP(DOT_V2F32)   // dot product
_DECLARE_OP(SCALE_V2F32) // scale
_DECLARE_OP(MAGN_V2F32)  // magnitude
_DECLARE_OP(NORM_V2F32)  // normalise
_DECLARE_OP(LERP_V2F32)  // interpolate
_DECLARE_OP(M3X3_V2F32)  // transform by 3x3 matrix

_DECLARE_OP(MUL_C2F32)   // Complex Multiply
_DELCARE_OP(DIV_C2F32)   // Complex Divide

_DECLARE_OP(SPLAT_V3F32) // splat fill
_DECLARE_OP(COPY_V3F32)  // copy
_DECLARE_OP(ADD_V3F32)   // add
_DECLARE_OP(SUB_V3F32)   // subtract
_DECLARE_OP(CROSS_V3F32) // cross product
_DECLARE_OP(DOT_V3F32)   // dot product
_DECLARE_OP(SCALE_V3F32) // scale
_DECLARE_OP(MAGN_V3F32)  // magnitude
_DECLARE_OP(NORM_V3F32)  // normalise
_DECLARE_OP(LERP_V3F32)  // interpolate
_DECLARE_OP(M4X4_V3F32)  // transform by 4x4 matrix

_DECLARE_OP(LSLM_32)
_DECLARE_OP(LSLR_32)
_DECLARE_OP(LSLM_64)
_DECLARE_OP(LSLR_64)

_DECLARE_OP(SPLAT_V2F64) // splat fill
_DECLARE_OP(COPY_V2F64)  // copy
_DECLARE_OP(ADD_V2F64)   // add
_DECLARE_OP(SUB_V2F64)   // subtract
_DECLARE_OP(DOT_V2F64)   // dot product
_DECLARE_OP(SCALE_V2F64) // scale
_DECLARE_OP(MAGN_V2F64)  // magnitude
_DECLARE_OP(NORM_V2F64)  // normalise
_DECLARE_OP(LERP_V2F64)  // interpolate
_DECLARE_OP(M3X3_V2F64)  // transform by 3x3 matrix

_DECLARE_OP(MUL_C2F64)   // Complex Multiply
_DELCARE_OP(DIV_C2F64)   // Complex Divide

_DECLARE_OP(SPLAT_V3F64) // splat fill
_DECLARE_OP(COPY_V3F64)  // copy
_DECLARE_OP(ADD_V3F64)   // add
_DECLARE_OP(SUB_V3F64)   // subtract
_DECLARE_OP(CROSS_V3F64) // cross product
_DECLARE_OP(DOT_V3F64)   // dot product
_DECLARE_OP(SCALE_V3F64) // scale
_DECLARE_OP(MAGN_V3F64)  // magnitude
_DECLARE_OP(NORM_V3F64)  // normalise
_DECLARE_OP(LERP_V3F64)  // interpolate
_DECLARE_OP(M4X4_V3F64)  // transform by 4x4 matrix

static const Handler advancedHandlers[256]; // advanced handlers

