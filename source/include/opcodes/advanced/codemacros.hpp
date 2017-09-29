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


#define _ceil_f32(s,d)        _MKAOP(CEIL_F32),     (s) << 4 | (d),
#define _ceil_f64(s,d)        _MKAOP(CEIL_F64),     (s) << 4 | (d),
#define _floor_f32(s,d)       _MKAOP(FLOOR_F32),    (s) << 4 | (d),
#define _floor_f64(s,d)       _MKAOP(FLOOR_F64),    (s) << 4 | (d),
#define _lerp_f32(x,y,l,d)    _MKAOP(LERP_F32),     (x) << 12 | (y) << 8 | (l) << 4 | (d),
#define _lerp_f64(x,y,l,d)    _MKAOP(LERP_F64),     (x) << 12 | (y) << 8 | (l) << 4 | (d),

#define _spl_v3f32(s,d)       _MKAOP(SPLV3_F32),    (s) << 4 | (d),
#define _mov_v3f32(s,d)       _MKAOP(MOVV3_F32),    (s) << 4 | (d),
#define _add_v3f32(x,y,d)     _MKAOP(ADDV3_F32),    (x) << 8 | (y) << 4 | (d),
#define _sub_v3f32(x,y,d)     _MKAOP(SUVV3_F32),    (x) << 8 | (y) << 4 | (d),
#define _cross_v3f32(x,y,d)   _MKAOP(CRSV3_F32),    (x) << 8 | (y) << 4 | (d),
#define _dot_v3f32(x,y,d)     _MKAOP(DOTV3_F32),    (x) << 8 | (y) << 4 | (d),
#define _scale_v3f32(f,s,d)   _MKAOP(SCLV3_F32),    (f) << 8 | (s) << 4 | (d),
#define _mag_v3f32(s,d)       _MKAOP(MAGV3_F32),    (s) << 4 | (d),
#define _norm_v3f32(s,d)      _MKAOP(NRMV3_F32),    (s) << 4 | (d),

#endif

