//****************************************************************************//
//**                                                                        **//
//** File:         opcodes/vector/codemacros.hpp                            **//
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

#ifndef _VM_VECTOR_CODEMACROS_HPP_
#define _VM_VECTOR_CODEMACROS_HPP_

#define _MKOP(x)  ((VMDefs::_##x) << 8)


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Vector fill
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// d[0..n-1] = s
#define _vfill_8(s,d,n)         _MKVOP(FILL_8),     (s) << 8 | (d) << 4 | (n),
#define _vfill_16(s,d,n)        _MKVOP(FILL_16),    (s) << 8 | (d) << 4 | (n),
#define _vfill_32(s,d,n)        _MKVOP(FILL_32),    (s) << 8 | (d) << 4 | (n),
#define _vfill_64(s,d,n)        _MKVOP(FILL_64),    (s) << 8 | (d) << 4 | (n),

#define _vsmin_u8(s,d,n)        _MKVOP(SMIN_U8),    (s) << 8 | (d) << 4 | (n),
#define _vsmin_u16(s,d,n)       _MKVOP(SMIN_U16),   (s) << 8 | (d) << 4 | (n),
#define _vsmin_u32(s,d,n)       _MKVOP(SMIN_U32),   (s) << 8 | (d) << 4 | (n),
#define _vsmin_u64(s,d,n)       _MKVOP(SMIN_U64),   (s) << 8 | (d) << 4 | (n),
#define _vsmin_s8(s,d,n)        _MKVOP(SMIN_S8),    (s) << 8 | (d) << 4 | (n),
#define _vsmin_s16(s,d,n)       _MKVOP(SMIN_S16),   (s) << 8 | (d) << 4 | (n),
#define _vsmin_s32(s,d,n)       _MKVOP(SMIN_S32),   (s) << 8 | (d) << 4 | (n),
#define _vsmin_s64(s,d,n)       _MKVOP(SMIN_S64),   (s) << 8 | (d) << 4 | (n),
#define _vsmin_f32(s,d,n)       _MKVOP(SMIN_F32),   (s) << 8 | (d) << 4 | (n),
#define _vsmin_f64(s,d,n)       _MKVOP(SMIN_F64),   (s) << 8 | (d) << 4 | (n),

#define _vsmax_u8(s,d,n)        _MKVOP(SMAX_U8),    (s) << 8 | (d) << 4 | (n),
#define _vsmax_u16(s,d,n)       _MKVOP(SMAX_U16),   (s) << 8 | (d) << 4 | (n),
#define _vsmax_u32(s,d,n)       _MKVOP(SMAX_U32),   (s) << 8 | (d) << 4 | (n),
#define _vsmax_u64(s,d,n)       _MKVOP(SMAX_U64),   (s) << 8 | (d) << 4 | (n),
#define _vsmax_s8(s,d,n)        _MKVOP(SMAX_S8),    (s) << 8 | (d) << 4 | (n),
#define _vsmax_s16(s,d,n)       _MKVOP(SMAX_S16),   (s) << 8 | (d) << 4 | (n),
#define _vsmax_s32(s,d,n)       _MKVOP(SMAX_S32),   (s) << 8 | (d) << 4 | (n),
#define _vsmax_s64(s,d,n)       _MKVOP(SMAX_S64),   (s) << 8 | (d) << 4 | (n),
#define _vsmax_f32(s,d,n)       _MKVOP(SMAX_F32),   (s) << 8 | (d) << 4 | (n),
#define _vsmax_f64(s,d,n)       _MKVOP(SMAX_F64),   (s) << 8 | (d) << 4 | (n),

#define _vssum_u8(s,d,n)        _MKVOP(SSUM_U8),    (s) << 8 | (d) << 4 | (n),
#define _vssum_u16(s,d,n)       _MKVOP(SSUM_U16),   (s) << 8 | (d) << 4 | (n),
#define _vssum_u32(s,d,n)       _MKVOP(SSUM_U32),   (s) << 8 | (d) << 4 | (n),
#define _vssum_u64(s,d,n)       _MKVOP(SSUM_U64),   (s) << 8 | (d) << 4 | (n),
#define _vssum_s8(s,d,n)        _MKVOP(SSUM_S8),    (s) << 8 | (d) << 4 | (n),
#define _vssum_s16(s,d,n)       _MKVOP(SSUM_S16),   (s) << 8 | (d) << 4 | (n),
#define _vssum_s32(s,d,n)       _MKVOP(SSUM_S32),   (s) << 8 | (d) << 4 | (n),
#define _vssum_s64(s,d,n)       _MKVOP(SSUM_S64),   (s) << 8 | (d) << 4 | (n),
#define _vssum_f32(s,d,n)       _MKVOP(SSUM_F32),   (s) << 8 | (d) << 4 | (n),
#define _vssum_f64(s,d,n)       _MKVOP(SSUM_F64),   (s) << 8 | (d) << 4 | (n),

// d[0..n-1] = -s[0..n-1]
#define _vneg_s8(s,d,n)         _MKVOP(NEG_S8),     (s) << 8 | (d) << 4 | (n),
#define _vneg_s16(s,d,n)        _MKVOP(NEG_S16),    (s) << 8 | (d) << 4 | (n),
#define _vneg_s32(s,d,n)        _MKVOP(NEG_S32),    (s) << 8 | (d) << 4 | (n),
#define _vneg_s64(s,d,n)        _MKVOP(NEG_S64),    (s) << 8 | (d) << 4 | (n),
#define _vneg_f32(s,d,n)        _MKVOP(NEG_F32),    (s) << 8 | (d) << 4 | (n),
#define _vneg_f64(s,d,n)        _MKVOP(NEG_F64),    (s) << 8 | (d) << 4 | (n),

// d[0..n-1] = abs(s[0..n-1])
#define _vabs_s8(s,d,n)         _MKVOP(ABS_S8),     (s) << 8 | (d) << 4 | (n),
#define _vabs_s16(s,d,n)        _MKVOP(ABS_S16),    (s) << 8 | (d) << 4 | (n),
#define _vabs_s32(s,d,n)        _MKVOP(ABS_S32),    (s) << 8 | (d) << 4 | (n),
#define _vabs_s64(s,d,n)        _MKVOP(ABS_S64),    (s) << 8 | (d) << 4 | (n),
#define _vabs_f32(s,d,n)        _MKVOP(ABS_F32),    (s) << 8 | (d) << 4 | (n),
#define _vabs_f64(s,d,n)        _MKVOP(ABS_F64),    (s) << 8 | (d) << 4 | (n),

// d[0..n-1] = ~s[0..n-1]
#define _vinv_8(s,d,n)          _MKVOP(INV_8),      (s) << 8 | (d) << 4 | (n),

// d[0..n-1] = s[0..n-1] + v
#define _vsadd_8(v,s,d,n)       _MKVOP(SADD_I8),    (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsadd_16(v,s,d,n)      _MKVOP(SADD_I16),   (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsadd_32(v,s,d,n)      _MKVOP(SADD_I32),   (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsadd_64(v,s,d,n)      _MKVOP(SADD_I64),   (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsadd_f32(v,s,d,n)     _MKVOP(SADD_F32),   (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsadd_f64(v,s,d,n)     _MKVOP(SADD_F64),   (v) << 12 | (s) << 8 | (d) << 4 | (n),

// Saturating versions
#define _vsadds_u8(v,s,d,n)     _MKVOP(SADDS_U8),   (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsadds_u16(v,s,d,n)    _MKVOP(SADDS_U16),  (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsadds_u32(v,s,d,n)    _MKVOP(SADDS_U32),  (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsadds_u64(v,s,d,n)    _MKVOP(SADDS_U64),  (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsadds_s8(v,s,d,n)     _MKVOP(SADDS_S8),   (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsadds_s16(v,s,d,n)    _MKVOP(SADDS_S16),  (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsadds_s32(v,s,d,n)    _MKVOP(SADDS_S32),  (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsadds_s64(v,s,d,n)    _MKVOP(SADDS_S64),  (v) << 12 | (s) << 8 | (d) << 4 | (n),

// d[0..n-1] = s[0..n-1] - v
#define _vssub_8(v,s,d,n)       _MKVOP(SSUB_I8),    (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vssub_16(v,s,d,n)      _MKVOP(SSUB_I16),   (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vssub_32(v,s,d,n)      _MKVOP(SSUB_I32),   (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vssub_64(v,s,d,n)      _MKVOP(SSUB_I64),   (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vssub_f32(v,s,d,n)     _MKVOP(SSUB_F32),   (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vssub_f64(v,s,d,n)     _MKVOP(SSUB_F64),   (v) << 12 | (s) << 8 | (d) << 4 | (n),

// Saturating versions
#define _vssubs_u8(v,s,d,n)     _MKVOP(SSUBS_U8),   (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vssubs_u16(v,s,d,n)    _MKVOP(SSUBS_U16),  (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vssubs_u32(v,s,d,n)    _MKVOP(SSUBS_U32),  (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vssubs_u64(v,s,d,n)    _MKVOP(SSUBS_U64),  (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vssubs_s8(v,s,d,n)     _MKVOP(SSUBS_S8),   (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vssubs_s16(v,s,d,n)    _MKVOP(SSUBS_S16),  (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vssubs_s32(v,s,d,n)    _MKVOP(SSUBS_S32),  (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vssubs_s64(v,s,d,n)    _MKVOP(SSUBS_S64),  (v) << 12 | (s) << 8 | (d) << 4 | (n),

// d[0..n-1] = s[0..n-1] * v
#define _vsmul_u8(v,s,d,n)      _MKVOP(SMUL_U8),    (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsmul_u16(v,s,d,n)     _MKVOP(SMUL_U16),   (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsmul_u32(v,s,d,n)     _MKVOP(SMUL_U32),   (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsmul_u64(v,s,d,n)     _MKVOP(SMUL_U64),   (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsmul_s8(v,s,d,n)      _MKVOP(SMUL_S8),    (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsmul_s16(v,s,d,n)     _MKVOP(SMUL_S16),   (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsmul_s32(v,s,d,n)     _MKVOP(SMUL_S32),   (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsmul_s64(v,s,d,n)     _MKVOP(SMUL_S64),   (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsmul_f32(v,s,d,n)     _MKVOP(SMUL_F32),   (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsmul_f64(v,s,d,n)     _MKVOP(SMUL_F64),   (v) << 12 | (s) << 8 | (d) << 4 | (n),

// Saturating versions
#define _vsmuls_u8(v,s,d,n)     _MKVOP(SMULS_U8),   (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsmuls_u16(v,s,d,n)    _MKVOP(SMULS_U16),  (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsmuls_u32(v,s,d,n)    _MKVOP(SMULS_U32),  (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsmuls_u64(v,s,d,n)    _MKVOP(SMULS_U64),  (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsmuls_s8(v,s,d,n)     _MKVOP(SMULS_S8),   (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsmuls_s16(v,s,d,n)    _MKVOP(SMULS_S16),  (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsmuls_s32(v,s,d,n)    _MKVOP(SMULS_S32),  (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsmuls_s64(v,s,d,n)    _MKVOP(SMULS_S64),  (v) << 12 | (s) << 8 | (d) << 4 | (n),

// d[0..n-1] = s[0..n-1] / v
#define _vsdiv_u8(v,s,d,n)      _MKVOP(SDIV_U8),    (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsdiv_u16(v,s,d,n)     _MKVOP(SDIV_U16),   (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsdiv_u32(v,s,d,n)     _MKVOP(SDIV_U32),   (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsdiv_u64(v,s,d,n)     _MKVOP(SDIV_U64),   (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsdiv_s8(v,s,d,n)      _MKVOP(SDIV_S8),    (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsdiv_s16(v,s,d,n)     _MKVOP(SDIV_S16),   (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsdiv_s32(v,s,d,n)     _MKVOP(SDIV_S32),   (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsdiv_s64(v,s,d,n)     _MKVOP(SDIV_S64),   (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsdiv_f32(v,s,d,n)     _MKVOP(SDIV_F32),   (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsdiv_f64(v,s,d,n)     _MKVOP(SDIV_F64),   (v) << 12 | (s) << 8 | (d) << 4 | (n),

// Saturating versions
#define _vsdivs_s8(v,s,d,n)     _MKVOP(SDIVS_S8),   (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsdivs_s16(v,s,d,n)    _MKVOP(SDIVS_S16),  (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsdivs_s32(v,s,d,n)    _MKVOP(SDIVS_S32),  (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsdivs_s64(v,s,d,n)    _MKVOP(SDIVS_S64),  (v) << 12 | (s) << 8 | (d) << 4 | (n),

// d[0..n-1] = s[0..n-1] % v
#define _vsmod_u8(v,s,d,n)      _MKVOP(SMOD_U8),    (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsmod_u16(v,s,d,n)     _MKVOP(SMOD_U16),   (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsmod_u32(v,s,d,n)     _MKVOP(SMOD_U32),   (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsmod_u64(v,s,d,n)     _MKVOP(SMOD_U64),   (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsmod_s8(v,s,d,n)      _MKVOP(SMOD_S8),    (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsmod_s16(v,s,d,n)     _MKVOP(SMOD_S16),   (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsmod_s32(v,s,d,n)     _MKVOP(SMOD_S32),   (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsmod_s64(v,s,d,n)     _MKVOP(SMOD_S64),   (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsmod_f32(v,s,d,n)     _MKVOP(SMOD_F32),   (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsmod_f64(v,s,d,n)     _MKVOP(SMOD_F64),   (v) << 12 | (s) << 8 | (d) << 4 | (n),

// d[0..n-1] = s[0..n-1] & v
#define _vsand_8(v,s,d,n)       _MKVOP(SAND_8),     (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsand_16(v,s,d,n)      _MKVOP(SAND_16),    (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsand_32(v,s,d,n)      _MKVOP(SAND_32),    (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsand_64(v,s,d,n)      _MKVOP(SAND_64),    (v) << 12 | (s) << 8 | (d) << 4 | (n),

// d[0..n-1] = s[0..n-1] | v
#define _vsor_8(v,s,d,n)        _MKVOP(SOR_8),      (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsor_16(v,s,d,n)       _MKVOP(SOR_16),     (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsor_32(v,s,d,n)       _MKVOP(SOR_32),     (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsor_64(v,s,d,n)       _MKVOP(SOR_64),     (v) << 12 | (s) << 8 | (d) << 4 | (n),

// d[0..n-1] = s[0..n-1] ^ v
#define _vsxor_8(v,s,d,n)       _MKVOP(SXOR_8),     (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsxor_16(v,s,d,n)      _MKVOP(SXOR_16),    (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsxor_32(v,s,d,n)      _MKVOP(SXOR_32),    (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsxor_64(v,s,d,n)      _MKVOP(SXOR_64),    (v) << 12 | (s) << 8 | (d) << 4 | (n),

// d[0..n-1] = s[0..n-1] << v
#define _vslsl_8(v,s,d,n)       _MKVOP(SLSL_8),     (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vslsl_16(v,s,d,n)      _MKVOP(SLSL_16),    (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vslsl_32(v,s,d,n)      _MKVOP(SLSL_32),    (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vslsl_64(v,s,d,n)      _MKVOP(SLSL_64),    (v) << 12 | (s) << 8 | (d) << 4 | (n),

// d[0..n-1] = s[0..n-1] >> v
#define _vslsr_8(v,s,d,n)       _MKVOP(SLSR_8),     (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vslsr_16(v,s,d,n)      _MKVOP(SLSR_16),    (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vslsr_32(v,s,d,n)      _MKVOP(SLSR_32),    (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vslsr_64(v,s,d,n)      _MKVOP(SLSR_64),    (v) << 12 | (s) << 8 | (d) << 4 | (n),

// d[0..n-1] = s[0..n-1] << v
#define _vsasl_s8(v,s,d,n)      _MKVOP(SASL_8),     (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsasl_s16(v,s,d,n)     _MKVOP(SASL_16),    (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsasl_s32(v,s,d,n)     _MKVOP(SASL_32),    (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsasl_s64(v,s,d,n)     _MKVOP(SASL_64),    (v) << 12 | (s) << 8 | (d) << 4 | (n),

// d[0..n-1] = s[0..n-1] >> v
#define _vsasr_s8(v,s,d,n)      _MKVOP(SASR_8),     (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsasr_s16(v,s,d,n)     _MKVOP(SASR_16),    (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsasr_s32(v,s,d,n)     _MKVOP(SASR_32),    (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsasr_s64(v,s,d,n)     _MKVOP(SASR_64),    (v) << 12 | (s) << 8 | (d) << 4 | (n),

// d[0..n-1] = s[0..n-1] <<@ v
#define _vsrol_8(v,s,d,n)       _MKVOP(SROL_8),     (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsrol_16(v,s,d,n)      _MKVOP(SROL_16),    (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsrol_32(v,s,d,n)      _MKVOP(SROL_32),    (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsrol_64(v,s,d,n)      _MKVOP(SROL_64),    (v) << 12 | (s) << 8 | (d) << 4 | (n),

// d[0..n-1] = s[0..n-1] @>> v
#define _vsror_8(v,s,d,n)       _MKVOP(SROR_8),     (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsror_16(v,s,d,n)      _MKVOP(SROR_16),    (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsror_32(v,s,d,n)      _MKVOP(SROR_32),    (v) << 12 | (s) << 8 | (d) << 4 | (n),
#define _vsror_64(v,s,d,n)      _MKVOP(SROR_64),    (v) << 12 | (s) << 8 | (d) << 4 | (n),


// d[0..n-1] = a[0..n-1] + b[0..n-1]
#define _vadd_8(a,b,d,n)       _MKVOP(ADD_I8),      (a) << 12 | (b) << 8 | (d) << 4 | (n),
#define _vadd_16(a,b,d,n)      _MKVOP(ADD_I16),     (a) << 12 | (b) << 8 | (d) << 4 | (n),
#define _vadd_32(a,b,d,n)      _MKVOP(ADD_I32),     (a) << 12 | (b) << 8 | (d) << 4 | (n),
#define _vadd_64(a,b,d,n)      _MKVOP(ADD_I64),     (a) << 12 | (b) << 8 | (d) << 4 | (n),
#define _vadd_f32(a,b,d,n)     _MKVOP(ADD_F32),     (a) << 12 | (b) << 8 | (d) << 4 | (n),
#define _vadd_f64(a,b,d,n)     _MKVOP(ADD_F64),     (a) << 12 | (b) << 8 | (d) << 4 | (n),

// Saturating versions
#define _vadds_u8(a,b,d,n)     _MKVOP(ADDS_U8),     (a) << 12 | (b) << 8 | (d) << 4 | (n),
#define _vadds_u16(a,b,d,n)    _MKVOP(ADDS_U16),    (a) << 12 | (b) << 8 | (d) << 4 | (n),
#define _vadds_u32(a,b,d,n)    _MKVOP(ADDS_U32),    (a) << 12 | (b) << 8 | (d) << 4 | (n),
#define _vadds_u64(a,b,d,n)    _MKVOP(ADDS_U64),    (a) << 12 | (b) << 8 | (d) << 4 | (n),
#define _vadds_s8(a,b,d,n)     _MKVOP(ADDS_S8),     (a) << 12 | (b) << 8 | (d) << 4 | (n),
#define _vadds_s16(a,b,d,n)    _MKVOP(ADDS_S16),    (a) << 12 | (b) << 8 | (d) << 4 | (n),
#define _vadds_s32(a,b,d,n)    _MKVOP(ADDS_S32),    (a) << 12 | (b) << 8 | (d) << 4 | (n),
#define _vadds_s64(a,b,d,n)    _MKVOP(ADDS_S64),    (a) << 12 | (b) << 8 | (d) << 4 | (n),

// d[0..n-1] = a[0..n-1] - b[0..n-1]
#define _vsub_8(a,b,d,n)       _MKVOP(SUB_I8),      (a) << 12 | (b) << 8 | (d) << 4 | (n),
#define _vsub_16(a,b,d,n)      _MKVOP(SUB_I16),     (a) << 12 | (b) << 8 | (d) << 4 | (n),
#define _vsub_32(a,b,d,n)      _MKVOP(SUB_I32),     (a) << 12 | (b) << 8 | (d) << 4 | (n),
#define _vsub_64(a,b,d,n)      _MKVOP(SUB_I64),     (a) << 12 | (b) << 8 | (d) << 4 | (n),
#define _vsub_f32(a,b,d,n)     _MKVOP(SUB_F32),     (a) << 12 | (b) << 8 | (d) << 4 | (n),
#define _vsub_f64(a,b,d,n)     _MKVOP(SUB_F64),     (a) << 12 | (b) << 8 | (d) << 4 | (n),

// Saturating versions
#define _vsubs_u8(a,b,d,n)     _MKVOP(SUBS_U8),     (a) << 12 | (b) << 8 | (d) << 4 | (n),
#define _vsubs_u16(a,b,d,n)    _MKVOP(SUBS_U16),    (a) << 12 | (b) << 8 | (d) << 4 | (n),
#define _vsubs_u32(a,b,d,n)    _MKVOP(SUBS_U32),    (a) << 12 | (b) << 8 | (d) << 4 | (n),
#define _vsubs_u64(a,b,d,n)    _MKVOP(SUBS_U64),    (a) << 12 | (b) << 8 | (d) << 4 | (n),
#define _vsubs_s8(a,b,d,n)     _MKVOP(SUBS_S8),     (a) << 12 | (b) << 8 | (d) << 4 | (n),
#define _vsubs_s16(a,b,d,n)    _MKVOP(SUBS_S16),    (a) << 12 | (b) << 8 | (d) << 4 | (n),
#define _vsubs_s32(a,b,d,n)    _MKVOP(SUBS_S32),    (a) << 12 | (b) << 8 | (d) << 4 | (n),
#define _vsubs_s64(a,b,d,n)    _MKVOP(SUBS_S64),    (a) << 12 | (b) << 8 | (d) << 4 | (n),

// d[0..n-1] = a[0..n-1] * b[0..n-1]
#define _vmul_u8(a,b,d,n)      _MKVOP(MUL_U8),      (a) << 12 | (b) << 8 | (d) << 4 | (n),
#define _vmul_u16(a,b,d,n)     _MKVOP(MUL_U16),     (a) << 12 | (b) << 8 | (d) << 4 | (n),
#define _vmul_u32(a,b,d,n)     _MKVOP(MUL_U32),     (a) << 12 | (b) << 8 | (d) << 4 | (n),
#define _vmul_u64(a,b,d,n)     _MKVOP(MUL_U64),     (a) << 12 | (b) << 8 | (d) << 4 | (n),
#define _vmul_s8(a,b,d,n)      _MKVOP(MUL_S8),      (a) << 12 | (b) << 8 | (d) << 4 | (n),
#define _vmul_s16(a,b,d,n)     _MKVOP(MUL_S16),     (a) << 12 | (b) << 8 | (d) << 4 | (n),
#define _vmul_s32(a,b,d,n)     _MKVOP(MUL_S32),     (a) << 12 | (b) << 8 | (d) << 4 | (n),
#define _vmul_s64(a,b,d,n)     _MKVOP(MUL_S64),     (a) << 12 | (b) << 8 | (d) << 4 | (n),
#define _vmul_f32(a,b,d,n)     _MKVOP(MUL_F32),     (a) << 12 | (b) << 8 | (d) << 4 | (n),
#define _vmul_f64(a,b,d,n)     _MKVOP(MUL_F64),     (a) << 12 | (b) << 8 | (d) << 4 | (n),

// Saturating versions
#define _vmuls_u8(a,b,d,n)     _MKVOP(MULS_U8),     (a) << 12 | (b) << 8 | (d) << 4 | (n),
#define _vmuls_u16(a,b,d,n)    _MKVOP(MULS_U16),    (a) << 12 | (b) << 8 | (d) << 4 | (n),
#define _vmuls_u32(a,b,d,n)    _MKVOP(MULS_U32),    (a) << 12 | (b) << 8 | (d) << 4 | (n),
#define _vmuls_u64(a,b,d,n)    _MKVOP(MULS_U64),    (a) << 12 | (b) << 8 | (d) << 4 | (n),
#define _vmuls_s8(a,b,d,n)     _MKVOP(MULS_S8),     (a) << 12 | (b) << 8 | (d) << 4 | (n),
#define _vmuls_s16(a,b,d,n)    _MKVOP(MULS_S16),    (a) << 12 | (b) << 8 | (d) << 4 | (n),
#define _vmuls_s32(a,b,d,n)    _MKVOP(MULS_S32),    (a) << 12 | (b) << 8 | (d) << 4 | (n),
#define _vmuls_s64(a,b,d,n)    _MKVOP(MULS_S64),    (a) << 12 | (b) << 8 | (d) << 4 | (n),

// d[0..n-1] = a[0..n-1] / b[0..n-1]
#define _vdiv_u8(a,b,d,n)      _MKVOP(DIV_U8),      (a) << 12 | (b) << 8 | (d) << 4 | (n),
#define _vdiv_u16(a,b,d,n)     _MKVOP(DIV_U16),     (a) << 12 | (b) << 8 | (d) << 4 | (n),
#define _vdiv_u32(a,b,d,n)     _MKVOP(DIV_U32),     (a) << 12 | (b) << 8 | (d) << 4 | (n),
#define _vdiv_u64(a,b,d,n)     _MKVOP(DIV_U64),     (a) << 12 | (b) << 8 | (d) << 4 | (n),
#define _vdiv_s8(a,b,d,n)      _MKVOP(DIV_S8),      (a) << 12 | (b) << 8 | (d) << 4 | (n),
#define _vdiv_s16(a,b,d,n)     _MKVOP(DIV_S16),     (a) << 12 | (b) << 8 | (d) << 4 | (n),
#define _vdiv_s32(a,b,d,n)     _MKVOP(DIV_S32),     (a) << 12 | (b) << 8 | (d) << 4 | (n),
#define _vdiv_s64(a,b,d,n)     _MKVOP(DIV_S64),     (a) << 12 | (b) << 8 | (d) << 4 | (n),
#define _vdiv_f32(a,b,d,n)     _MKVOP(DIV_F32),     (a) << 12 | (b) << 8 | (d) << 4 | (n),
#define _vdiv_f64(a,b,d,n)     _MKVOP(DIV_F64),     (a) << 12 | (b) << 8 | (d) << 4 | (n),

// Saturating versions
#define _vdivs_s8(a,b,d,n)     _MKVOP(DIVS_S8),     (a) << 12 | (b) << 8 | (d) << 4 | (n),
#define _vdivs_s16(a,b,d,n)    _MKVOP(DIVS_S16),    (a) << 12 | (b) << 8 | (d) << 4 | (n),
#define _vdivs_s32(a,b,d,n)    _MKVOP(DIVS_S32),    (a) << 12 | (b) << 8 | (d) << 4 | (n),
#define _vdivs_s64(a,b,d,n)    _MKVOP(DIVS_S64),    (a) << 12 | (b) << 8 | (d) << 4 | (n),

// d[0..n-1] = a[0..n-1] % b[0..n-1]
#define _vmod_u8(a,b,d,n)      _MKVOP(MOD_U8),      (a) << 12 | (b) << 8 | (d) << 4 | (n),
#define _vmod_u16(a,b,d,n)     _MKVOP(MOD_U16),     (a) << 12 | (b) << 8 | (d) << 4 | (n),
#define _vmod_u32(a,b,d,n)     _MKVOP(MOD_U32),     (a) << 12 | (b) << 8 | (d) << 4 | (n),
#define _vmod_u64(a,b,d,n)     _MKVOP(MOD_U64),     (a) << 12 | (b) << 8 | (d) << 4 | (n),
#define _vmod_s8(a,b,d,n)      _MKVOP(MOD_S8),      (a) << 12 | (b) << 8 | (d) << 4 | (n),
#define _vmod_s16(a,b,d,n)     _MKVOP(MOD_S16),     (a) << 12 | (b) << 8 | (d) << 4 | (n),
#define _vmod_s32(a,b,d,n)     _MKVOP(MOD_S32),     (a) << 12 | (b) << 8 | (d) << 4 | (n),
#define _vmod_s64(a,b,d,n)     _MKVOP(MOD_S64),     (a) << 12 | (b) << 8 | (d) << 4 | (n),
#define _vmod_f32(a,b,d,n)     _MKVOP(MOD_F32),     (a) << 12 | (b) << 8 | (d) << 4 | (n),
#define _vmod_f64(a,b,d,n)     _MKVOP(MOD_F64),     (a) << 12 | (b) << 8 | (d) << 4 | (n),

// d[0..n-1] = a[0..n-1] & b[0..n-1]
#define _vand_8(a,b,d,n)       _MKVOP(AND_8),       (a) << 12 | (b) << 8 | (d) << 4 | (n),

// d[0..n-1] = a[0..n-1] | b[0..n-1]
#define _vor_8(a,b,d,n)        _MKVOP(OR_8),        (a) << 12 | (b) << 8 | (d) << 4 | (n),

// d[0..n-1] = a[0..n-1] ^ b[0..n-1]
#define _vxor_8(a,b,d,n)       _MKVOP(XOR_8),       (a) << 12 | (b) << 8 | (d) << 4 | (n),

// d[0..n-1] = m[s[0..n-1]]
#define _vmap_8_16(s,m,d,n)    _MKVOP(MAP_8_16),    (s) << 12 | (m) << 8 | (d) << 4 | (n),
#define _vmap_8_32(s,m,d,n)    _MKVOP(MAP_8_32),    (s) << 12 | (m) << 8 | (d) << 4 | (n),
#define _vmap_8_64(s,m,d,n)    _MKVOP(MAP_8_64),    (s) << 12 | (m) << 8 | (d) << 4 | (n),
#define _vmap_16_32(s,m,d,n)   _MKVOP(MAP_16_32),   (s) << 12 | (m) << 8 | (d) << 4 | (n),
#define _vmap_16_64(s,m,d,n)   _MKVOP(MAP_16_64),   (s) << 12 | (m) << 8 | (d) << 4 | (n),

#endif

