//****************************************************************************//
//**                                                                        **//
//** File:         opcodes/advanced/codemacros.hpp                          **//
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

#ifndef _VM_ADVANCED_CODEMACROS_HPP_
#define _VM_ADVANCED_CODEMACROS_HPP_

#define _MKAOP(x) (VMDefs::_ADV  << 8 | (VMDefs::_##x))

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Multiply Add
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define _madd_f32(a,b,c,d)    _MKAOP(MADD_F32),     (a) << 12 | (b) << 8 | (c) << 4 | (d),
#define _madd_f64(a,b,c,d)    _MKAOP(MADD_F64),     (a) << 12 | (b) << 8 | (c) << 4 | (d),

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Load Constant
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define _ld_const_f32(c,d)    _MKAOP(LD_CONST_F32), (c) << 4 | (d),
#define _ld_const_f64(c,d)    _MKAOP(LD_CONST_F64), (c) << 4 | (d),

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Load indexed, with scale
//
//  d = b[i << f]
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define _ld_rii_8(b,i,f,d)    _MKAOP(LD_RII_8),     (f) << 12 | (i) << 8 | ((b) << 4) | (d),
#define _ld_rii_16(b,i,f,d)   _MKAOP(LD_RII_16),    (f) << 12 | (i) << 8 | ((b) << 4) | (d),
#define _ld_rii_32(b,i,f,d)   _MKAOP(LD_RII_32),    (f) << 12 | (i) << 8 | ((b) << 4) | (d),
#define _ld_rii_64(b,i,f,d)   _MKAOP(LD_RII_64),    (f) << 12 | (i) << 8 | ((b) << 4) | (d),

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Store indexed, with scale
//
//  b[i << f] = s
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define _st_rii_8(s,b,i,f)    _MKAOP(ST_RII_8),     (f) << 12 | (i) << 8 | ((b) << 4) | (s),
#define _st_rii_16(s,b,i,f)   _MKAOP(ST_RII_16),    (f) << 12 | (i) << 8 | ((b) << 4) | (s),
#define _st_rii_32(s,b,i,f)   _MKAOP(ST_RII_32),    (f) << 12 | (i) << 8 | ((b) << 4) | (s),
#define _st_rii_64(s,b,i,f)   _MKAOP(ST_RII_64),    (f) << 12 | (i) << 8 | ((b) << 4) | (s),

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Roots
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define _sqrt_f32(s,d)        _MKAOP(SQRT_F32),     (s) << 4 | (d),
#define _sqrt_f64(s,d)        _MKAOP(SQRT_F64),     (s) << 4 | (d),
#define _isqrt_f32(s,d)       _MKAOP(ISQRT_F32),    (s) << 4 | (d),
#define _isqrt_f64(s,d)       _MKAOP(ISQRT_F64),    (s) << 4 | (d),

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Trig
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define _acos_f32(s,d)        _MKAOP(ACOS_F32),     (s) << 4 | (d),
#define _acos_f64(s,d)        _MKAOP(ACOS_F64),     (s) << 4 | (d),
#define _asin_f32(s,d)        _MKAOP(ASIN_F32),     (s) << 4 | (d),
#define _asin_f64(s,d)        _MKAOP(ASIN_F64),     (s) << 4 | (d),
#define _atan_f32(s,d)        _MKAOP(ATAN_F32),     (s) << 4 | (d),
#define _atan_f64(s,d)        _MKAOP(ATAN_F64),     (s) << 4 | (d),
#define _cos_f32(s,d)         _MKAOP(COS_F32),      (s) << 4 | (d),
#define _cos_f64(s,d)         _MKAOP(COS_F64),      (s) << 4 | (d),
#define _sin_f32(s,d)         _MKAOP(SIN_F32),      (s) << 4 | (d),
#define _sin_f64(s,d)         _MKAOP(SIN_F64),      (s) << 4 | (d),
#define _tan_f32(s,d)         _MKAOP(TAN_F32),      (s) << 4 | (d),
#define _tan_f64(s,d)         _MKAOP(TAN_F64),      (s) << 4 | (d),
#define _cosh_f32(s,d)        _MKAOP(COSH_F32),     (s) << 4 | (d),
#define _cosh_f64(s,d)        _MKAOP(COSH_F64),     (s) << 4 | (d),
#define _sinh_f32(s,d)        _MKAOP(SINH_F32),     (s) << 4 | (d),
#define _sinh_f64(s,d)        _MKAOP(SINH_F64),     (s) << 4 | (d),
#define _tanh_f32(s,d)        _MKAOP(TANH_F32),     (s) << 4 | (d),
#define _tanh_f64(s,d)        _MKAOP(TANH_F64),     (s) << 4 | (d),
#define _sincos_f32(x,ds,dc)  _MKAOP(SINCOS_F32),   (x) << 8 | (dc) << 4 | (ds),
#define _sincos_f64(x,ds,dc)  _MKAOP(SINCOS_F64),   (x) << 8 | (dc) << 4 | (ds),

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Exponentiation and Powers
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define _exp_f32(s,d)         _MKAOP(EXP_F32),      (s) << 4 | (d),
#define _exp_f64(s,d)         _MKAOP(EXP_F64),      (s) << 4 | (d),
#define _pow_f32(s,p,d)       _MKAOP(POW_F32),      (p) << 8 | (s) << 4 | (d),
#define _pow_f64(s,p,d)       _MKAOP(POW_F64),      (p) << 8 | (s) << 4 | (d),

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Logs
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define _logn_f32(s,d)        _MKAOP(LOGN_F32),     (s) << 4 | (d),
#define _logn_f64(s,d)        _MKAOP(LOGN_F64),     (s) << 4 | (d),
#define _log2_f32(s,d)        _MKAOP(LOG2_F32),     (s) << 4 | (d),
#define _log2_f64(s,d)        _MKAOP(LOG2_F64),     (s) << 4 | (d),
#define _log10_f32(s,d)       _MKAOP(LOG10_F32),    (s) << 4 | (d),
#define _log10_f64(s,d)       _MKAOP(LOG10_F64),    (s) << 4 | (d),
#define _logx_f32(s,l,d)      _MKAOP(LOGX_F32),     (l) << 8 | (s) << 4 | (d),
#define _logx_f64(s,l,d)      _MKAOP(LOGX_F64),     (l) << 8 | (s) << 4 | (d),

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Truncation and Roudning
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#define _ceil_f32(s,d)        _MKAOP(CEIL_F32),     (s) <<  4 | (d),
#define _ceil_f64(s,d)        _MKAOP(CEIL_F64),     (s) <<  4 | (d),
#define _floor_f32(s,d)       _MKAOP(FLOOR_F32),    (s) <<  4 | (d),
#define _floor_f64(s,d)       _MKAOP(FLOOR_F64),    (s) <<  4 | (d),
#define _lerp_f32(x,y,l,d)    _MKAOP(LERP_F32),     (x) << 12 | (y) << 8 | (l) << 4 | (d),
#define _lerp_f64(x,y,l,d)    _MKAOP(LERP_F64),     (x) << 12 | (y) << 8 | (l) << 4 | (d),

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Masked shifting
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define _lslm_32(s,m,b,d)     _MKAOP(LSLM_32),      (s) << 12 | (m) << 8 | (b) << 4 | (d),
#define _lsrm_32(s,m,b,d)     _MKAOP(LSRM_32),      (s) << 12 | (m) << 8 | (b) << 4 | (d),
#define _lslm_64(s,m,b,d)     _MKAOP(LSLM_64),      (s) << 12 | (m) << 8 | (b) << 4 | (d),
#define _lsrm_64(s,m,b,d)     _MKAOP(LSRM_64),      (s) << 12 | (m) << 8 | (b) << 4 | (d),

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Complex { float32 real; float32 imaginary; }
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Specifically complex number operations
#define _mul_c2f32(a,b,d) _MKAOP(MUL_C2F32),  (a) << 8 | (b) << 4 | (d),
#define _div_c2f32(a,b,d) _MKAOP(DIV_C2F32),  (a) << 8 | (b) << 4 | (d),

// Complex and vector 2D equivalents
#define _copy_c2f32(s, d) _MKAOP(COPY_V2F32), (s) << 4 | (d)
#define _add_c2f32(a,b,d) _MKAOP(ADD_V2F32),  (a) << 8 | (b) << 4 | (d),
#define _sub_c2f32(a,b,d) _MKAOP(SUB_V2F32),  (a) << 8 | (b) << 4 | (d),

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Vector 2D float32[2]
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define _splat_v2f32(s, d)    _MKAOP(SPLAT_V2F32),  (s) <<  4 | (d),
#define _copy_v2f32(s, d)     _MKAOP(COPY_V2F32),   (s) <<  4 | (d),
#define _add_v2f32(a,b,d)     _MKAOP(ADD_V2F32),    (a) <<  8 | (b) << 4 | (d),
#define _sub_v2f32(a,b,d)     _MKAOP(SUB_V2F32),    (a) <<  8 | (b) << 4 | (d),
#define _dot_v2f32(a, b, d)   _MKAOP(DOT_V2F32),    (a) <<  8 | (b) << 4 | (d),
#define _scale_v2f32(f, s, d) _MKAOP(SCALE_V2F32),  (f) <<  8 | (s) << 4 | (d),
#define _magn_v2f32(s, d)     _MKAOP(MAGN_V2F32),   (s) <<  4 | (d),
#define _norm_v2f32(s, d)     _MKAOP(NORM_V2F32),   (s) <<  4 | (d),
#define _lerp_v2f32(x,y,f,d)  _MKAOP(LERP_V2F32),   (x) << 12 | (y) << 8 | (f) << 4 | (d),
#define _xform_v2f32(s,m,d,n) _MKAOP(M3X3_V2F32),   (s) << 12 | (m) << 8 | (d) << 4 | (n),

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Vector 3D float32[3]
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define _splat_v3f32(s,d)     _MKAOP(SPLAT_V3F32),  (s) <<  4 | (d),
#define _copy_v3f32(s,d)      _MKAOP(COPY_V3F32),   (s) <<  4 | (d),
#define _add_v3f32(x,y,d)     _MKAOP(ADD_V3F32),    (x) <<  8 | (y) << 4 | (d),
#define _sub_v3f32(x,y,d)     _MKAOP(SUB_V3F32),    (x) <<  8 | (y) << 4 | (d),
#define _cross_v3f32(x,y,d)   _MKAOP(CROSS_V3F32),  (x) <<  8 | (y) << 4 | (d),
#define _dot_v3f32(x,y,d)     _MKAOP(DOT_V3F32),    (x) <<  8 | (y) << 4 | (d),
#define _scale_v3f32(f,s,d)   _MKAOP(SCALE_V3F32),  (f) <<  8 | (s) << 4 | (d),
#define _magn_v3f32(s,d)      _MKAOP(MAGN_V3F32),   (s) <<  4 | (d),
#define _norm_v3f32(s,d)      _MKAOP(NORM_V3F32),   (s) <<  4 | (d),
#define _lerp_v3f32(x,y,f,d)  _MKAOP(LERP_V3F32),   (x) << 12 | (y) << 8 | (f) << 4 | (d),
#define _xform_v3f32(s,m,d,n) _MKAOP(M4X4_V3F32),   (s) << 12 | (m) << 8 | (d) << 4 | (n),


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Complex { float64 real; float64 imaginary; }
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Specifically complex number operations
#define _mul_c2f64(a,b,d) _MKAOP(MUL_C2F64),  (a) << 8 | (b) << 4 | (d),
#define _div_c2f64(a,b,d) _MKAOP(DIV_C2F64),  (a) << 8 | (b) << 4 | (d),

// Complex and vector 2D equivalents
#define _copy_c2f64(s, d) _MKAOP(COPY_V2F64), (s) << 4 | (d),
#define _add_c2f64(a,b,d) _MKAOP(ADD_V2F64),  (a) << 8 | (b) << 4 | (d),
#define _sub_c2f64(a,b,d) _MKAOP(SUB_V2F64),  (a) << 8 | (b) << 4 | (d),

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Vector 2D float64[2]
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define _splat_v2f64(s, d)    _MKAOP(SPLAT_V2F64),  (s) <<  4 | (d),
#define _copy_v2f64(s, d)     _MKAOP(COPY_V2F64),   (s) <<  4 | (d),
#define _add_v2f64(a,b,d)     _MKAOP(ADD_V2F64),    (a) <<  8 | (b) << 4 | (d),
#define _sub_v2f64(a,b,d)     _MKAOP(SUB_V2F64),    (a) <<  8 | (b) << 4 | (d),
#define _dot_v2f64(a, b, d)   _MKAOP(DOT_V2F64),    (a) <<  8 | (b) << 4 | (d),
#define _scale_v2f64(f, s, d) _MKAOP(SCALE_V2F64),  (f) <<  8 | (s) << 4 | (d),
#define _magn_v2f64(s, d)     _MKAOP(MAGN_V2F64),   (s) <<  4 | (d),
#define _norm_v2f64(s, d)     _MKAOP(NORM_V2F64),   (s) <<  4 | (d),
#define _lerp_v2f64(x,y,f,d)  _MKAOP(LERP_V2F64),   (x) << 12 | (y) << 8 | (f) << 4 | (d),
#define _xform_v2f64(s,m,d,n) _MKAOP(M3X3_V2F64),   (s) << 12 | (m) << 8 | (d) << 4 | (n),

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Vector 3D float64[3]
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define _splat_v3f64(s,d)     _MKAOP(SPLAT_V3F64),  (s) <<  4 | (d),
#define _copy_v3f64(s,d)      _MKAOP(COPY_V3F64),   (s) <<  4 | (d),
#define _add_v3f64(x,y,d)     _MKAOP(ADD_V3F64),    (x) <<  8 | (y) << 4 | (d),
#define _sub_v3f64(x,y,d)     _MKAOP(SUB_V3F64),    (x) <<  8 | (y) << 4 | (d),
#define _cross_v3f64(x,y,d)   _MKAOP(CROSS_V3F64),  (x) <<  8 | (y) << 4 | (d),
#define _dot_v3f64(x,y,d)     _MKAOP(DOT_V3F64),    (x) <<  8 | (y) << 4 | (d),
#define _scale_v3f64(f,s,d)   _MKAOP(SCALE_V3F64),  (f) <<  8 | (s) << 4 | (d),
#define _magn_v3f64(s,d)      _MKAOP(MAGN_V3F64),   (s) <<  4 | (d),
#define _norm_v3f64(s,d)      _MKAOP(NORM_V3F64),   (s) <<  4 | (d),
#define _lerp_v3f64(x,y,f,d)  _MKAOP(LERP_V3F64),   (x) << 12 | (y) << 8 | (f) << 4 | (d),
#define _xform_v3f64(s,m,d,n) _MKAOP(M4X4_V3F64),   (s) << 12 | (m) << 8 | (d) << 4 | (n),

#endif

