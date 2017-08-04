//****************************************************************************//
//**                                                                        **//
//** File:         vm_codemacros.hpp                                        **//
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


#ifndef _VM_CODEMACROS_HPP_
#define _VM_CODEMACROS_HPP_
#include "vm.hpp"

#if (X_ENDIAN == XA_BIGENDIAN)

inline uint16 _float32MSW(float32 f) {
  // returns the most significant 16-bits of a 32-bit floating point value
  union {
    float32 f;
    uint16 u[2];
  } u;
  u.f = f;
  return u.u[0];
}

inline uint16 _float32LSW(float32 f) {
  // returns the most significant 16-bits of a 32-bit floating point value
  union {
    float32 f;
    uint16 u[2];
  } u;
  u.f = f;
  return u.u[1];
}

// covnert a 32-bit integer immediate into 16-bit words
#define _INLINE32(x) (uint16)(( (uint32)(x) )>>16), \
                     (uint16)(( (uint32)(x) )&0xFFFF)

#if X_PTRSIZE == XA_PTRSIZE64
#define _INLINEPTR(x) (uint16)(( (uint64)(x) )>>48), \
                      (uint16)((( (uint64)(x) )>>32)&0xFFFF), \
                      (uint16)((( (uint64)(x) )>>16)&0xFFFF), \
                      (uint16)(( (uint64)(x) )&0xFFFF)
#else
#define _INLINEPTR(x) (uint16)0, \
                      (uint16)0, \
                      (uint16)((( (uint32)(x) )>>16)&0xFFFF), \
                      (uint16)(((uint32)(x))&0xFFFF)
#endif

// convert a 32-bit float immediate into 16-bit words
#define _INLINEF32(x) (_float32MSW((x))), \
                      (_float32LSW((x)))

#else

inline uint16 _float32MSW(float32 f) {
  // returns the most significant 16-bits of a 32-bit floating point value
  union { float32 f; uint16 u[2]; } u;
  u.f = f;
  return u.u[1];
}

inline uint16 _float32LSW(float32 f) {
  // returns the most significant 16-bits of a 32-bit floating point value
  union { float32 f; uint16 u[2]; } u;
  u.f = f;
  return u.u[0];
}

// covnert a 32-bit integer immediate into 16-bit words
#define _INLINE32(x) (( (uint32)(x) )&0xFFFF), \
                     (( (uint32)(x) )>>16)

#if X_PTRSIZE == XA_PTRSIZE64
  #define _INLINEPTR(x) (uint16)(( (uint64)(x) )&0xFFFF), \
                        (uint16)((( (uint64)(x) )>>16)&0xFFFF), \
                        (uint16)((( (uint64)(x) )>>32)&0xFFFF), \
                        (uint16)(( (uint64)(x) )>>48)
#else
  #define _INLINEPTR(x) (uint16)(( (uint32)(x) )&0xFFFF), \
                        (uint16)(( (uint32)(x) )>>16), \
                        (uint16)0, \
                        (uint16)0
#endif

// convert a 32-bit float immediate into 16-bit words
#define _INLINEF32(x)  (_float32LSW((x))), \
                       (_float32MSW((x)))

#endif


////////////////////////////////////////////////////////////////////////////////
// register names
#define _r0 0
#define _r1 1
#define _r2 2
#define _r3 3
#define _r4 4
#define _r5 5
#define _r6 6
#define _r7 7
#define _r8 8
#define _r9 9
#define _r10 10
#define _r11 11
#define _r12 12
#define _r13 13
#define _r14 14
#define _r15 15

// register masks (for save/restore/push/pop)
#define _mr0 1
#define _mr1 2
#define _mr2 4
#define _mr3 8
#define _mr4 16
#define _mr5 32
#define _mr6 64
#define _mr7 128
#define _mr8 256
#define _mr9  512
#define _mr10 1024
#define _mr11 2048
#define _mr12 4096
#define _mr13 8192
#define _mr14 16384
#define _mr15 32768

#define _SYM_NATIVE(x) sym_native_##x
#define _SYM_CODE(x) sym_code_##x
#define _SYM_DATA(x) sym_data_##x

////////////////////////////////////////////////////////////////////////////////
//
//  begin a named array of 16 bit words representing a code block:
//
//  _VM_CODE(myFunction) {
//
//
//  }; <- don't forget the trailing semicolon!
//
////////////////////////////////////////////////////////////////////////////////

#define _VM_CODE(x) uint16 _vmCode##x[] =


////////////////////////////////////////////////////////////////////////////////
//
//  refer to a named code block:
//
//  uint16* code = _VM_ENTRY(myFunction);
//
////////////////////////////////////////////////////////////////////////////////

#define _VM_ENTRY(x) (_vmCode##x)

#define _VM_EXTERN(x) extern uint16 _vmCode##x[]

////////////////////////////////////////////////////////////////////////////////
//
//  obtain the size (in words) of a named code block:
//
//  size_t size = _VM_CODE_SIZE(myFunction);
//
////////////////////////////////////////////////////////////////////////////////

#define _VM_CODE_SIZE(x) (sizeof(_vmCode##x)/sizeof(uint16))

////////////////////////////////////////////////////////////////////////////////
//
//  create an opcode word:
//
//  _MKOP(<name>)
//
//  generates the 16-bit word for the named opcode, ie (VMDefs::_<name>)<<8
//
////////////////////////////////////////////////////////////////////////////////

#define _MKOP(x) ((VMDefs::_##x)<<8)


////////////////////////////////////////////////////////////////////////////////
//
//  control group
//
////////////////////////////////////////////////////////////////////////////////

#define _nop                  _MKOP(NOP),
#define _brk                  _MKOP(BRK),

////////////////////////////////////////////////////////////////////////////////
//
//  load group
//
//  _operation(number, _rD)          - literals, globals
//  _operation(_rS, _rD)             - register indirect, postinc, predec
//  _operation(_rS, offset, _rD)     - indirect with displacement
//  _operation(_rS, _rI, scale, _rD) - inirect scaled indexed
//
////////////////////////////////////////////////////////////////////////////////

#define _ldq(n,r)             _MKOP(LDQ)|(n)<<4|(r),
#define _ld_16_i8(n,r)        _MKOP(LD_I16_8)|(r), (n),
#define _ld_16_i16(n,r)       _MKOP(LD_I16_16)|(r), (n),
#define _ld_16_i32(n,r)       _MKOP(LD_I16_32)|(r), (n),
#define _ld_16_i64(n,r)       _MKOP(LD_I16_64)|(r), (n),
#define _ld_32_i32(n,r)       _MKOP(LD_I32_32)|(r), _INLINE32(n),
#define _ld_32_i64(n,r)       _MKOP(LD_I32_64)|(r), _INLINE32(n),
#define _ld_32_f32(n,r)       _MKOP(LD_F32)|(r), _INLINEF32(n),
#define _ld_ri_8(s,d)         _MKOP(LD_RI_8)|(s)<<4|(d),
#define _ld_ri_16(s,d)        _MKOP(LD_RI_16)|(s)<<4|(d),
#define _ld_ri_32(s,d)        _MKOP(LD_RI_32)|(s)<<4|(d),
#define _ld_ri_64(s,d)        _MKOP(LD_RI_64)|(s)<<4|(d),
#define _ld_ripi_8(s,d)       _MKOP(LD_RIPI_8)|(s)<<4|(d),
#define _ld_ripi_16(s,d)      _MKOP(LD_RIPI_16)|(s)<<4|(d),
#define _ld_ripi_32(s,d)      _MKOP(LD_RIPI_32)|(s)<<4|(d),
#define _ld_ripi_64(s,d)      _MKOP(LD_RIPI_64)|(s)<<4|(d),
#define _ld_ripd_8(s,d)       _MKOP(LD_RIPD_8)|(s)<<4|(d),
#define _ld_ripd_16(s,d)      _MKOP(LD_RIPD_16)|(s)<<4|(d),
#define _ld_ripd_32(s,d)      _MKOP(LD_RIPD_32)|(s)<<4|(d),
#define _ld_ripd_64(s,d)      _MKOP(LD_RIPD_64)|(s)<<4|(d),
#define _ld_rid_8(s,o,d)      _MKOP(LD_RID_8)|(s)<<4|(d),
#define _ld_rid_16(s,o,d)     _MKOP(LD_RID_16)|(s)<<4|(d), (uint16)(o),
#define _ld_rid_32(s,o,d)     _MKOP(LD_RID_32)|(s)<<4|(d), (uint16)(o),
#define _ld_rid_64(s,o,d)     _MKOP(LD_RID_64)|(s)<<4|(d), (uint16)(o),
#define _ld_rii_8(s,i,f,d)    _MKOP(LD_RII_8)|(s)<<4|(d), ((f)<<8)|((i)&0xF),
#define _ld_rii_16(s,i,f,d)   _MKOP(LD_RII_16)|(s)<<4|(d), ((f)<<8)|((i)&0xF),
#define _ld_rii_32(s,i,f,d)   _MKOP(LD_RII_32)|(s)<<4|(d), ((f)<<8)|((i)&0xF),
#define _ld_rii_64(s,i,f,d)   _MKOP(LD_RII_64)|(s)<<4|(d), ((f)<<8)|((i)&0xF),

// Ignores the actual symbol indicator and inserts an unresolved symbol ID
#define _ld_8_unresolved(x,d)            _MKOP(LD_8)|(d), 0xFFFF,
#define _ld_16_unresolved(x,d)           _MKOP(LD_16)|(d), 0xFFFF,
#define _ld_32_unresolved(x,d)           _MKOP(LD_32)|(d), 0xFFFF,
#define _ld_64_unresolved(x,d)           _MKOP(LD_64)|(d), 0xFFFF,
#define _lda_unresolved(x,d)             _MKOP(LD_ADDR)|(d), 0xFFFF,

// For testing mock resolved symbols
#define _ld_8(x,d)            _MKOP(LD_8)|(d), (uint16)_SYM_DATA(x),
#define _ld_16(x,d)           _MKOP(LD_16)|(d), (uint16)_SYM_DATA(x),
#define _ld_32(x,d)           _MKOP(LD_32)|(d), (uint16)_SYM_DATA(x),
#define _ld_64(x,d)           _MKOP(LD_64)|(d), (uint16)_SYM_DATA(x),
#define _lda(x,d)             _MKOP(LD_ADDR)|(d), (uint16)_SYM_DATA(x),

////////////////////////////////////////////////////////////////////////////////
//
//  store group
//
//  _operation(rS, label)            - globals
//  _operation(_rS, _rD)             - register indirect, postinc, predec
//  _operation(_rS, _rD, offset)     - indirect with displacement
//  _operation(_rS, _rD, _rI, scale) - inirect scaled indexed
//
////////////////////////////////////////////////////////////////////////////////

#define _st_ri_8(s,d)         _MKOP(ST_RI_8)|(s)<<4|(d),
#define _st_ri_16(s,d)        _MKOP(ST_RI_16)|(s)<<4|(d),
#define _st_ri_32(s,d)        _MKOP(ST_RI_32)|(s)<<4|(d),
#define _st_ri_64(s,d)        _MKOP(ST_RI_64)|(s)<<4|(d),
#define _st_ripi_8(s,d)       _MKOP(ST_RIPI_8)|(s)<<4|(d),
#define _st_ripi_16(s,d)      _MKOP(ST_RIPI_16)|(s)<<4|(d),
#define _st_ripi_32(s,d)      _MKOP(ST_RIPI_32)|(s)<<4|(d),
#define _st_ripi_64(s,d)      _MKOP(ST_RIPI_64)|(s)<<4|(d),
#define _st_ripd_8(s,d)       _MKOP(ST_RIPD_8)|(s)<<4|(d),
#define _st_ripd_16(s,d)      _MKOP(ST_RIPD_16)|(s)<<4|(d),
#define _st_ripd_32(s,d)      _MKOP(ST_RIPD_32)|(s)<<4|(d),
#define _st_ripd_64(s,d)      _MKOP(ST_RIPD_64)|(s)<<4|(d),
#define _st_rid_8(s,d,o)      _MKOP(ST_RID_8)|(s)<<4|(d), (uint16)(o),
#define _st_rid_16(s,d,o)     _MKOP(ST_RID_16)|(s)<<4|(d), (uint16)(o),
#define _st_rid_32(s,d,o)     _MKOP(ST_RID_32)|(s)<<4|(d), (uint16)(o),
#define _st_rid_64(s,d,o)     _MKOP(ST_RID_64)|(s)<<4|(d), (uint16)(o),
#define _st_rii_8(s,d,i,f)    _MKOP(ST_RII_8)|(s)<<4|(d), ((f)<<8)|((i)&0xF),
#define _st_rii_16(s,d,i,f)   _MKOP(ST_RII_16)|(s)<<4|(d), ((f)<<8)|((i)&0xF),
#define _st_rii_32(s,d,i,f)   _MKOP(ST_RII_32)|(s)<<4|(d), ((f)<<8)|((i)&0xF),
#define _st_rii_64(s,d,i,f)   _MKOP(ST_RII_64)|(s)<<4|(d), ((f)<<8)|((i)&0xF),

// Ignores the actual symbol indicator and inserts an unresolved symbol ID
#define _st_8_unresolved(s,x)            _MKOP(ST_8)|(s), (uint16)_SYM_DATA(x),
#define _st_16_unresolved(s,x)           _MKOP(ST_16)|(s), (uint16)_SYM_DATA(x),
#define _st_32_unresolved(s,x)           _MKOP(ST_32)|(s), (uint16)_SYM_DATA(x),
#define _st_64_unresolved(s,x)           _MKOP(ST_64)|(s), (uint16)_SYM_DATA(x),

// For testing mock resolved symbols
#define _st_8(s,x)            _MKOP(ST_8)|(s), (uint16)_SYM_DATA(x),
#define _st_16(s,x)           _MKOP(ST_16)|(s), (uint16)_SYM_DATA(x),
#define _st_32(s,x)           _MKOP(ST_32)|(s), (uint16)_SYM_DATA(x),
#define _st_64(s,x)           _MKOP(ST_64)|(s), (uint16)_SYM_DATA(x),

////////////////////////////////////////////////////////////////////////////////
//
//  move group
//
//  _operation(_rS, rD)         - move, exg
//  _operation(_r1|_r2|..._r16) - save, restore, push, pop
//
////////////////////////////////////////////////////////////////////////////////

#define _move_8(s,d)          _MKOP(MV_8)|(s)<<4|(d),
#define _move_16(s,d)         _MKOP(MV_16)|(s)<<4|(d),
#define _move_32(s,d)         _MKOP(MV_32)|(s)<<4|(d),
#define _move_64(s,d)         _MKOP(MV_64)|(s)<<4|(d),
#define _exg(s,d)             _MKOP(EXG)|(s)<<4|(d),
#define _save(m)              _MKOP(SV), (m),
#define _restore(m)           _MKOP(RS), (m),
#define _push_8(m)            _MKOP(PUSH_8), (m),
#define _push_16(m)           _MKOP(PUSH_16), (m),
#define _push_32(m)           _MKOP(PUSH_32), (m),
#define _push_64(m)           _MKOP(PUSH_64), (m),
#define _pop_8(m)             _MKOP(POP_8), (m),
#define _pop_16(m)            _MKOP(POP_16), (m),
#define _pop_32(m)            _MKOP(POP_32), (m),
#define _pop_64(m)            _MKOP(POP_64), (m),

////////////////////////////////////////////////////////////////////////////////
//
//  jump group
//
//  _operation(label)            - bra, call, calln
//  _operation(_rS, _rD, offset) - bxx
//
////////////////////////////////////////////////////////////////////////////////


#define _bcall_8_unresolved(x) _MKOP(CALL), 0xFFFF,
#define _bcall_unresolved(x)   _MKOP(CALLN), 0xFFFF,

#define _bcall_8(x)           _MKOP(CALL), (uint16)_SYM_CODE(x),
#define _bcall(x)             _MKOP(CALLN), (uint16)_SYM_NATIVE(x),

#define _call_unresolved(x)   _MKOP(CALL), 0xFFFF,
#define _calln_unresolved(x)  _MKOP(CALLN), 0xFFFF,

#define _call(x)              _MKOP(CALL), (uint16)_SYM_CODE(x),
#define _calln(x)             _MKOP(CALLN), (uint16)_SYM_NATIVE(x),

#define _ret                  _MKOP(RET)
#define _bra_8(o)             _MKOP(BRA8)|(o),
#define _bra(o)               _MKOP(BRA16), (uint16)(o),
#define _case(r,sz)           _MKOP(CASE)|(r), (sz),

#define _bnz_8(r,o)           _MKOP(BNZ_8)|(r), (uint16)(o),
#define _bnz_16(r,o)          _MKOP(BNZ_16)|(r), (uint16)(o),
#define _bnz_32(r,o)          _MKOP(BNZ_32)|(r), (uint16)(o),
#define _bnz_64(r,o)          _MKOP(BNZ_64)|(r), (uint16)(o),

// Fake Less a < b based on b > a
#define _bls_8(s,d,o)         _MKOP(BGR_8)|(d)<<4|(s), (uint16)(o),
#define _bls_16(s,d,o)        _MKOP(BGR_16)|(d)<<4|(s), (uint16)(o),
#define _bls_32(s,d,o)        _MKOP(BGR_32)|(d)<<4|(s), (uint16)(o),
#define _bls_64(s,d,o)        _MKOP(BGR_64)|(d)<<4|(s), (uint16)(o),
#define _bls_f32(s,d,o)       _MKOP(BGR_F32)|(d)<<4|(s), (uint16)(o),
#define _bls_f64(s,d,o)       _MKOP(BGR_F64)|(d)<<4|(s), (uint16)(o),
#define _blseq_8(s,d,o)       _MKOP(BGREQ_8)|(d)<<4|(s), (uint16)(o),
#define _blseq_16(s,d,o)      _MKOP(BGREQ_16)|(d)<<4|(s), (uint16)(o),
#define _blseq_32(s,d,o)      _MKOP(BGREQ_32)|(d)<<4|(s), (uint16)(o),
#define _blseq_64(s,d,o)      _MKOP(BGREQ_64)|(d)<<4|(s), (uint16)(o),
#define _blseq_f32(s,d,o)     _MKOP(BGREQ_F32)|(d)<<4|(s), (uint16)(o),
#define _blseq_f64(s,d,o)     _MKOP(BGREQ_F64)|(d)<<4|(s), (uint16)(o),

#define _beq_8(s,d,o)         _MKOP(BEQ_8)|(s)<<4|(d), (uint16)(o),
#define _beq_16(s,d,o)        _MKOP(BEQ_16)|(s)<<4|(d), (uint16)(o),
#define _beq_32(s,d,o)        _MKOP(BEQ_32)|(s)<<4|(d), (uint16)(o),
#define _beq_64(s,d,o)        _MKOP(BEQ_64)|(s)<<4|(d), (uint16)(o),
#define _beq_f32(s,d,o)       _MKOP(BEQ_F32)|(s)<<4|(d), (uint16)(o),
#define _beq_f64(s,d,o)       _MKOP(BEQ_F64)|(s)<<4|(d), (uint16)(o),
#define _bgreq_8(s,d,o)       _MKOP(BGREQ_8)|(s)<<4|(d), (uint16)(o),
#define _bgreq_16(s,d,o)      _MKOP(BGREQ_16)|(s)<<4|(d), (uint16)(o),
#define _bgreq_32(s,d,o)      _MKOP(BGREQ_32)|(s)<<4|(d), (uint16)(o),
#define _bgreq_64(s,d,o)      _MKOP(BGREQ_64)|(s)<<4|(d), (uint16)(o),
#define _bgreq_f32(s,d,o)     _MKOP(BGREQ_F32)|(s)<<4|(d), (uint16)(o),
#define _bgreq_f64(s,d,o)     _MKOP(BGREQ_F64)|(s)<<4|(d), (uint16)(o),
#define _bgr_8(s,d,o)         _MKOP(BGR_8)|(s)<<4|(d), (uint16)(o),
#define _bgr_16(s,d,o)        _MKOP(BGR_16)|(s)<<4|(d), (uint16)(o),
#define _bgr_32(s,d,o)        _MKOP(BGR_32)|(s)<<4|(d), (uint16)(o),
#define _bgr_64(s,d,o)        _MKOP(BGR_64)|(s)<<4|(d), (uint16)(o),
#define _bgr_f32(s,d,o)       _MKOP(BGR_F32)|(s)<<4|(d), (uint16)(o),
#define _bgr_f64(s,d,o)       _MKOP(BGR_F64)|(s)<<4|(d), (uint16)(o),

////////////////////////////////////////////////////////////////////////////////
//
//  conversion group
//
//  _operation(_rS, _rD)
//
////////////////////////////////////////////////////////////////////////////////

#define _s8to_s16(s,d)        _MKOP(S8_2_S16)|(s)<<4|(d),
#define _s8to_s32(s,d)        _MKOP(S8_2_S32)|(s)<<4|(d),
#define _s8to_s64(s,d)        _MKOP(S8_2_S64)|(s)<<4|(d),
#define _s8to_f32(s,d)        _MKOP(S8_2_F32)|(s)<<4|(d),
#define _s8to_f64(s,d)        _MKOP(S8_2_F64)|(s)<<4|(d),
#define _s16to_s32(s,d)       _MKOP(S16_2_S32)|(s)<<4|(d),
#define _s16to_s64(s,d)       _MKOP(S16_2_S64)|(s)<<4|(d),
#define _s16to_f32(s,d)       _MKOP(S16_2_F32)|(s)<<4|(d),
#define _s16to_f64(s,d)       _MKOP(S16_2_F64)|(s)<<4|(d),
#define _s32to_s64(s,d)       _MKOP(S32_2_S64)|(s)<<4|(d),
#define _s32to_f32(s,d)       _MKOP(S32_2_F32)|(s)<<4|(d),
#define _s32to_f64(s,d)       _MKOP(S32_2_F64)|(s)<<4|(d),
#define _s64to_f32(s,d)       _MKOP(S64_2_F32)|(s)<<4|(d),
#define _s64to_f64(s,d)       _MKOP(S64_2_F64)|(s)<<4|(d),
#define _u8to_f32(s,d)        _MKOP(U8_2_F32)|(s)<<4|(d),
#define _u8to_f64(s,d)        _MKOP(U8_2_F64)|(s)<<4|(d),
#define _u16to_f32(s,d)       _MKOP(U16_2_F32)|(s)<<4|(d),
#define _u16to_f64(s,d)       _MKOP(U16_2_F64)|(s)<<4|(d),
#define _u32to_f32(s,d)       _MKOP(U32_2_F32)|(s)<<4|(d),
#define _u32to_f64(s,d)       _MKOP(U32_2_F64)|(s)<<4|(d),
#define _u64to_f32(s,d)       _MKOP(U64_2_F32)|(s)<<4|(d),
#define _u64to_f64(s,d)       _MKOP(U64_2_F64)|(s)<<4|(d),
#define _f32to_f64(s,d)       _MKOP(F32_2_F64)|(s)<<4|(d),
#define _f64to_f32(s,d)       _MKOP(F64_2_F32)|(s)<<4|(d),
#define _f64to_s64(s,d)       _MKOP(F64_2_S64)|(s)<<4|(d),
#define _f64to_s32(s,d)       _MKOP(F64_2_S32)|(s)<<4|(d),
#define _f64to_s16(s,d)       _MKOP(F64_2_S16)|(s)<<4|(d),
#define _f64to_s8(s,d)        _MKOP(F64_2_S8)|(s)<<4|(d),
#define _f32to_s64(s,d)       _MKOP(F32_2_S64)|(s)<<4|(d),
#define _f32to_s32(s,d)       _MKOP(F32_2_S32)|(s)<<4|(d),
#define _f32to_s16(s,d)       _MKOP(F32_2_S16)|(s)<<4|(d),
#define _f32to_s8(s,d)        _MKOP(F32_2_S8)|(s)<<4|(d),

////////////////////////////////////////////////////////////////////////////////
//
//  arithmetic group
//
//  _operation(_rS, _rD)
//
////////////////////////////////////////////////////////////////////////////////

#define _add_8(s,d)           _MKOP(ADD_I8)|(s)<<4|(d),
#define _add_16(s,d)          _MKOP(ADD_I16)|(s)<<4|(d),
#define _add_32(s,d)          _MKOP(ADD_I32)|(s)<<4|(d),
#define _add_64(s,d)          _MKOP(ADD_I64)|(s)<<4|(d),
#define _add_f32(s,d)         _MKOP(ADD_F32)|(s)<<4|(d),
#define _add_f64(s,d)         _MKOP(ADD_F64)|(s)<<4|(d),
#define _addi_8(n,r)          _MKOP(ADDI_I8)|(r), (n),
#define _addi_16(n,r)         _MKOP(ADDI_I16)|(r), (n),
#define _addi_32(n,r)         _MKOP(ADDI_I32)|(r), _INLINE32(n),
#define _sub_8(s,d)           _MKOP(SUB_I8)|(s)<<4|(d),
#define _sub_16(s,d)          _MKOP(SUB_I16)|(s)<<4|(d),
#define _sub_32(s,d)          _MKOP(SUB_I32)|(s)<<4|(d),
#define _sub_64(s,d)          _MKOP(SUB_I64)|(s)<<4|(d),
#define _sub_f32(s,d)         _MKOP(SUB_F32)|(s)<<4|(d),
#define _sub_f64(s,d)         _MKOP(SUB_F64)|(s)<<4|(d),
#define _subi_8(n,r)          _MKOP(ADDI_I8)|(r), (uint16)(-(n)),
#define _subi_16(n,r)         _MKOP(ADDI_I16)|(r), (uint16)(-(n)),
#define _subi_32(n,r)         _MKOP(ADDI_I32)|(r), _INLINE32(-(n)),
#define _mul_u8(s,d)          _MKOP(MUL_U8)|(s)<<4|(d),
#define _mul_u16(s,d)         _MKOP(MUL_U16)|(s)<<4|(d),
#define _mul_u32(s,d)         _MKOP(MUL_U32)|(s)<<4|(d),
#define _mul_u64(s,d)         _MKOP(MUL_U64)|(s)<<4|(d),
#define _mul_s8(s,d)          _MKOP(MUL_S8)|(s)<<4|(d),
#define _mul_s16(s,d)         _MKOP(MUL_S16)|(s)<<4|(d),
#define _mul_s32(s,d)         _MKOP(MUL_S32)|(s)<<4|(d),
#define _mul_s64(s,d)         _MKOP(MUL_S64)|(s)<<4|(d),
#define _mul_f32(s,d)         _MKOP(MUL_F32)|(s)<<4|(d),
#define _mul_f64(s,d)         _MKOP(MUL_F64)|(s)<<4|(d),
#define _div_u8(s,d)          _MKOP(DIV_U8)|(s)<<4|(d),
#define _div_u16(s,d)         _MKOP(DIV_U16)|(s)<<4|(d),
#define _div_u32(s,d)         _MKOP(DIV_U32)|(s)<<4|(d),
#define _div_u64(s,d)         _MKOP(DIV_U64)|(s)<<4|(d),
#define _div_s8(s,d)          _MKOP(DIV_S8)|(s)<<4|(d),
#define _div_s16(s,d)         _MKOP(DIV_S16)|(s)<<4|(d),
#define _div_s32(s,d)         _MKOP(DIV_S32)|(s)<<4|(d),
#define _div_s64(s,d)         _MKOP(DIV_S64)|(s)<<4|(d),
#define _div_f32(s,d)         _MKOP(DIV_F32)|(s)<<4|(d),
#define _div_f64(s,d)         _MKOP(DIV_F64)|(s)<<4|(d),
#define _mod_u8(s,d)          _MKOP(MOD_U8)|(s)<<4|(d),
#define _mod_u16(s,d)         _MKOP(MOD_U16)|(s)<<4|(d),
#define _mod_u32(s,d)         _MKOP(MOD_U32)|(s)<<4|(d),
#define _mod_u64(s,d)         _MKOP(MOD_U64)|(s)<<4|(d),
#define _mod_s8(s,d)          _MKOP(MOD_S8)|(s)<<4|(d),
#define _mod_s15(s,d)         _MKOP(MOD_S16)|(s)<<4|(d),
#define _mod_s32(s,d)         _MKOP(MOD_S32)|(s)<<4|(d),
#define _mod_s64(s,d)         _MKOP(MOD_S64)|(s)<<4|(d),
#define _mod_f32(s,d)         _MKOP(MOD_F32)|(s)<<4|(d),
#define _mod_f64(s,d)         _MKOP(MOD_F64)|(s)<<4|(d),
#define _neg_s8(s,d)          _MKOP(NEG_S8)|(s)<<4|(d),
#define _neg_s16(s,d)         _MKOP(NEG_S16)|(s)<<4|(d),
#define _neg_s32(s,d)         _MKOP(NEG_S32)|(s)<<4|(d),
#define _neg_s64(s,d)         _MKOP(NEG_S64)|(s)<<4|(d),
#define _neg_f32(s,d)         _MKOP(NEG_F32)|(s)<<4|(d),
#define _neg_f64(s,d)         _MKOP(NEG_F64)|(s)<<4|(d),

#define _asr_s8(s,d)          _MKOP(ASR_S8)|(s)<<4|(d),
#define _asr_s16(s,d)         _MKOP(ASR_S16)|(s)<<4|(d),
#define _asr_s32(s,d)         _MKOP(ASR_S32)|(s)<<4|(d),
#define _asr_s64(s,d)         _MKOP(ASR_S64)|(s)<<4|(d),
#define _min_s8(s,d)          _MKOP(MIN_S8)|(s)<<4|(d),
#define _min_s16(s,d)         _MKOP(MIN_S16)|(s)<<4|(d),
#define _min_s32(s,d)         _MKOP(MIN_S32)|(s)<<4|(d),
#define _min_s64(s,d)         _MKOP(MIN_S64)|(s)<<4|(d),
#define _min_f32(s,d)         _MKOP(MIN_F32)|(s)<<4|(d),
#define _min_f64(s,d)         _MKOP(MIN_F64)|(s)<<4|(d),
#define _max_s8(s,d)          _MKOP(MAX_S8)|(s)<<4|(d),
#define _max_s16(s,d)         _MKOP(MAX_S16)|(s)<<4|(d),
#define _max_s32(s,d)         _MKOP(MAX_S32)|(s)<<4|(d),
#define _max_s64(s,d)         _MKOP(MAX_S64)|(s)<<4|(d),
#define _max_f32(s,d)         _MKOP(MAX_F32)|(s)<<4|(d),
#define _max_f64(s,d)         _MKOP(MAX_F64)|(s)<<4|(d),

////////////////////////////////////////////////////////////////////////////////
//
//  logic group
//
//  _operation(_rS, _rD)
//
////////////////////////////////////////////////////////////////////////////////

#define _and_8(s,d)           _MKOP(AND_8)|(s)<<4|(d),
#define _and_16(s,d)          _MKOP(AND_16)|(s)<<4|(d),
#define _and_32(s,d)          _MKOP(AND_32)|(s)<<4|(d),
#define _and_64(s,d)          _MKOP(AND_64)|(s)<<4|(d),
#define _or_8(s,d)            _MKOP(OR_8)|(s)<<4|(d),
#define _or_16(s,d)           _MKOP(OR_16)|(s)<<4|(d),
#define _or_32(s,d)           _MKOP(OR_32)|(s)<<4|(d),
#define _or_64(s,d)           _MKOP(OR_64)|(s)<<4|(d),
#define _xor_8(s,d)           _MKOP(XOR_8)|(s)<<4|(d),
#define _xor_16(s,d)          _MKOP(XOR_16)|(s)<<4|(d),
#define _xor_32(s,d)          _MKOP(XOR_32)|(s)<<4|(d),
#define _xor_64(s,d)          _MKOP(XOR_64)|(s)<<4|(d),
#define _inv_8(s,d)           _MKOP(INV_8)|(s)<<4|(d),
#define _inv_16(s,d)          _MKOP(INV_16)|(s)<<4|(d),
#define _inv_32(s,d)          _MKOP(INV_32)|(s)<<4|(d),
#define _inv_64(s,d)          _MKOP(INV_64)|(s)<<4|(d),
#define _lsl_8(s,d)           _MKOP(LSL_8)|(s)<<4|(d),
#define _lsl_16(s,d)          _MKOP(LSL_16)|(s)<<4|(d),
#define _lsl_32(s,d)          _MKOP(LSL_32)|(s)<<4|(d),
#define _lsl_64(s,d)          _MKOP(LSL_64)|(s)<<4|(d),
#define _lsr_8(s,d)           _MKOP(LSR_8)|(s)<<4|(d),
#define _lsr_16(s,d)          _MKOP(LSR_16)|(s)<<4|(d),
#define _lsr_32(s,d)          _MKOP(LSR_32)|(s)<<4|(d),
#define _lsr_64(s,d)          _MKOP(LSR_64)|(s)<<4|(d),
#define _rol_8(s,d)           _MKOP(ROL_8)|(s)<<4|(d),
#define _rol_16(s,d)          _MKOP(ROL_16)|(s)<<4|(d),
#define _rol_32(s,d)          _MKOP(ROL_32)|(s)<<4|(d),
#define _rol_64(s,d)          _MKOP(ROL_64)|(s)<<4|(d),
#define _ror_8(s,d)           _MKOP(ROR_8)|(s)<<4|(d),
#define _ror_16(s,d)          _MKOP(ROR_16)|(s)<<4|(d),
#define _ror_32(s,d)          _MKOP(ROR_32)|(s)<<4|(d),
#define _ror_64(s,d)          _MKOP(ROR_64)|(s)<<4|(d),

////////////////////////////////////////////////////////////////////////////////
//
//  misc group
//
////////////////////////////////////////////////////////////////////////////////

#define _madd_f32(s,d,m,c)    _MKOP(MUL_ADD_F32)|(s)<<4|(d),(m)<<8|(c),
#define _madd_f64(s,d,m,c)    _MKOP(MUL_ADD_F64)|(s)<<4|(d),(s)<<8|(c),

#endif

