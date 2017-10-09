//****************************************************************************//
//**                                                                        **//
//** File:         vm_handlers.hpp                                          **//
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

#ifndef _VM_CORE_HPP_
#error vmhandlers.hpp must not be included manually!
#endif
#define _DECLARE_OP(x)  static void do##x(ExVM::Interpreter*, uint16);

typedef void (*Handler)(Interpreter*, uint16);

// TODO: Reorganise based on sizeless, 32-bit int only, 32-bit int+float, 64-bit contiguous blocks

// control group
_DECLARE_OP(NOP)
_DECLARE_OP(BRK)

// load group
_DECLARE_OP(LDQ)
_DECLARE_OP(LD_16_I8)
_DECLARE_OP(LD_16_I16)
_DECLARE_OP(LD_16_I32)
_DECLARE_OP(LD_16_I64)
_DECLARE_OP(LD_32_32)
_DECLARE_OP(LD_32_I64)
_DECLARE_OP(LD_32_F64)
_DECLARE_OP(LD_RI_8)
_DECLARE_OP(LD_RI_16)
_DECLARE_OP(LD_RI_32)
_DECLARE_OP(LD_RI_64)
_DECLARE_OP(LD_RIPI_8)
_DECLARE_OP(LD_RIPI_16)
_DECLARE_OP(LD_RIPI_32)
_DECLARE_OP(LD_RIPI_64)
_DECLARE_OP(LD_RIPD_8)
_DECLARE_OP(LD_RIPD_16)
_DECLARE_OP(LD_RIPD_32)
_DECLARE_OP(LD_RIPD_64)
_DECLARE_OP(LD_RID_8)
_DECLARE_OP(LD_RID_16)
_DECLARE_OP(LD_RID_32)
_DECLARE_OP(LD_RID_64)

_DECLARE_OP(LD_8)
_DECLARE_OP(LD_16)
_DECLARE_OP(LD_32)
_DECLARE_OP(LD_64)
_DECLARE_OP(LD_ADDR)

// store group
_DECLARE_OP(ST_RI_8)
_DECLARE_OP(ST_RI_16)
_DECLARE_OP(ST_RI_32)
_DECLARE_OP(ST_RI_64)
_DECLARE_OP(ST_RIPI_8)
_DECLARE_OP(ST_RIPI_16)
_DECLARE_OP(ST_RIPI_32)
_DECLARE_OP(ST_RIPI_64)
_DECLARE_OP(ST_RIPD_8)
_DECLARE_OP(ST_RIPD_16)
_DECLARE_OP(ST_RIPD_32)
_DECLARE_OP(ST_RIPD_64)
_DECLARE_OP(ST_RID_8)
_DECLARE_OP(ST_RID_16)
_DECLARE_OP(ST_RID_32)
_DECLARE_OP(ST_RID_64)
_DECLARE_OP(ST_8)
_DECLARE_OP(ST_16)
_DECLARE_OP(ST_32)
_DECLARE_OP(ST_64)

// move group
_DECLARE_OP(MV_8)
_DECLARE_OP(MV_16)
_DECLARE_OP(MV_32)
_DECLARE_OP(MV_64)
_DECLARE_OP(BSWP_16)
_DECLARE_OP(BSWP_32)
_DECLARE_OP(BSWP_64)
_DECLARE_OP(EXG)

// These functions are defined in the class even for switch-case
//_DECLARE_OP(SV)
//_DECLARE_OP(RS)
//_DECLARE_OP(PUSH_8)
//_DECLARE_OP(PUSH_16)
//_DECLARE_OP(PUSH_32)
//_DECLARE_OP(PUSH_64)
//_DECLARE_OP(POP_8)
//_DECLARE_OP(POP_16)
//_DECLARE_OP(POP_32)
//_DECLARE_OP(POP_64)
//_DECLARE_OP(SALLOC)
//_DECLARE_OP(SFREE)

// jump group
//_DECLARE_OP(BCALL8)
//_DECLARE_OP(BCALL16)
//_DECLARE_OP(CALL)
//_DECLARE_OP(CALLN)

_DECLARE_OP(RET)
_DECLARE_OP(BRA8)
_DECLARE_OP(BRA16)
_DECLARE_OP(CASE)

_DECLARE_OP(BNZ_8)
_DECLARE_OP(BNZ_16)
_DECLARE_OP(BNZ_32)
_DECLARE_OP(BNZ_64)

_DECLARE_OP(BEQ_8)
_DECLARE_OP(BEQ_16)
_DECLARE_OP(BEQ_32)
_DECLARE_OP(BEQ_64)
_DECLARE_OP(BEQ_F32)
_DECLARE_OP(BEQ_F64)
_DECLARE_OP(BGREQ_8)
_DECLARE_OP(BGREQ_16)
_DECLARE_OP(BGREQ_32)
_DECLARE_OP(BGREQ_64)
_DECLARE_OP(BGREQ_F32)
_DECLARE_OP(BGREQ_F64)
_DECLARE_OP(BGR_8)
_DECLARE_OP(BGR_16)
_DECLARE_OP(BGR_32)
_DECLARE_OP(BGR_64)
_DECLARE_OP(BGR_F32)
_DECLARE_OP(BGR_F64)

// cast widening group
_DECLARE_OP(S8_2_S16)
_DECLARE_OP(S8_2_S32)
_DECLARE_OP(S8_2_S64)
_DECLARE_OP(S8_2_F32)
_DECLARE_OP(S8_2_F64)
_DECLARE_OP(S16_2_S32)
_DECLARE_OP(S16_2_S64)
_DECLARE_OP(S16_2_F32)
_DECLARE_OP(S16_2_F64)
_DECLARE_OP(S32_2_S64)
_DECLARE_OP(S32_2_F32)
_DECLARE_OP(S32_2_F64)
_DECLARE_OP(S64_2_F32)
_DECLARE_OP(S64_2_F64)
_DECLARE_OP(U8_2_F32)
_DECLARE_OP(U8_2_F64)
_DECLARE_OP(U16_2_F32)
_DECLARE_OP(U16_2_F64)
_DECLARE_OP(U32_2_F32)
_DECLARE_OP(U32_2_F64)
_DECLARE_OP(U64_2_F32)
_DECLARE_OP(U64_2_F64)
_DECLARE_OP(F32_2_F64)

// cast narrowing group
_DECLARE_OP(F64_2_F32)
_DECLARE_OP(F64_2_S64)
_DECLARE_OP(F64_2_S32)
_DECLARE_OP(F64_2_S16)
_DECLARE_OP(F64_2_S8)
_DECLARE_OP(F32_2_S64)
_DECLARE_OP(F32_2_S32)
_DECLARE_OP(F32_2_S16)
_DECLARE_OP(F32_2_S8)

// aritmetic group
_DECLARE_OP(ADD_I8)
_DECLARE_OP(ADD_I16)
_DECLARE_OP(ADD_I32)
_DECLARE_OP(ADD_I64)
_DECLARE_OP(ADD_F32)
_DECLARE_OP(ADD_F64)

_DECLARE_OP(ADDI_I8)
_DECLARE_OP(ADDI_I16)
_DECLARE_OP(ADDI_I32)

_DECLARE_OP(SUB_I8)
_DECLARE_OP(SUB_I16)
_DECLARE_OP(SUB_I32)
_DECLARE_OP(SUB_I64)
_DECLARE_OP(SUB_F32)
_DECLARE_OP(SUB_F64)
_DECLARE_OP(MUL_U8)
_DECLARE_OP(MUL_U16)
_DECLARE_OP(MUL_U32)
_DECLARE_OP(MUL_U64)
_DECLARE_OP(MUL_S8)
_DECLARE_OP(MUL_S16)
_DECLARE_OP(MUL_S32)
_DECLARE_OP(MUL_S64)
_DECLARE_OP(MUL_F32)
_DECLARE_OP(MUL_F64)
_DECLARE_OP(DIV_U8)
_DECLARE_OP(DIV_U16)
_DECLARE_OP(DIV_U32)
_DECLARE_OP(DIV_U64)
_DECLARE_OP(DIV_S8)
_DECLARE_OP(DIV_S16)
_DECLARE_OP(DIV_S32)
_DECLARE_OP(DIV_S64)
_DECLARE_OP(DIV_F32)
_DECLARE_OP(DIV_F64)
_DECLARE_OP(MOD_U8)
_DECLARE_OP(MOD_U16)
_DECLARE_OP(MOD_U32)
_DECLARE_OP(MOD_U64)
_DECLARE_OP(MOD_S8)
_DECLARE_OP(MOD_S16)
_DECLARE_OP(MOD_S32)
_DECLARE_OP(MOD_S64)
_DECLARE_OP(MOD_F32)
_DECLARE_OP(MOD_F64)
_DECLARE_OP(NEG_S8)
_DECLARE_OP(NEG_S16)
_DECLARE_OP(NEG_S32)
_DECLARE_OP(NEG_S64)
_DECLARE_OP(NEG_F32)
_DECLARE_OP(NEG_F64)

_DECLARE_OP(ASR_S8)
_DECLARE_OP(ASR_S16)
_DECLARE_OP(ASR_S32)
_DECLARE_OP(ASR_S64)
_DECLARE_OP(MIN_S8)
_DECLARE_OP(MIN_S16)
_DECLARE_OP(MIN_S32)
_DECLARE_OP(MIN_S64)
_DECLARE_OP(MIN_F32)
_DECLARE_OP(MIN_F64)
_DECLARE_OP(MAX_S8)
_DECLARE_OP(MAX_S16)
_DECLARE_OP(MAX_S32)
_DECLARE_OP(MAX_S64)
_DECLARE_OP(MAX_F32)
_DECLARE_OP(MAX_F64)

// logic group
_DECLARE_OP(AND_8)
_DECLARE_OP(AND_16)
_DECLARE_OP(AND_32)
_DECLARE_OP(AND_64)
_DECLARE_OP(OR_8)
_DECLARE_OP(OR_16)
_DECLARE_OP(OR_32)
_DECLARE_OP(OR_64)
_DECLARE_OP(XOR_8)
_DECLARE_OP(XOR_16)
_DECLARE_OP(XOR_32)
_DECLARE_OP(XOR_64)
_DECLARE_OP(INV_8)
_DECLARE_OP(INV_16)
_DECLARE_OP(INV_32)
_DECLARE_OP(INV_64)
_DECLARE_OP(LSL_8)
_DECLARE_OP(LSL_16)
_DECLARE_OP(LSL_32)
_DECLARE_OP(LSL_64)
_DECLARE_OP(LSR_8)
_DECLARE_OP(LSR_16)
_DECLARE_OP(LSR_32)
_DECLARE_OP(LSR_64)
_DECLARE_OP(ROL_8)
_DECLARE_OP(ROL_16)
_DECLARE_OP(ROL_32)
_DECLARE_OP(ROL_64)
_DECLARE_OP(ROR_8)
_DECLARE_OP(ROR_16)
_DECLARE_OP(ROR_32)
_DECLARE_OP(ROR_64)

// These functions are defined in the class even for switch-case

// misc group
_DECLARE_OP(ILLEGAL);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Vector instructions
_DECLARE_OP(VFILL_8)
_DECLARE_OP(VFILL_16)
_DECLARE_OP(VFILL_32)
_DECLARE_OP(VFILL_64)
// op_vec_smin_impl.hpp
_DECLARE_OP(VSMIN_U8)
_DECLARE_OP(VSMIN_U16)
_DECLARE_OP(VSMIN_U32)
_DECLARE_OP(VSMIN_U64)
_DECLARE_OP(VSMIN_S8)
_DECLARE_OP(VSMIN_S16)
_DECLARE_OP(VSMIN_S32)
_DECLARE_OP(VSMIN_S64)
_DECLARE_OP(VSMIN_F32)
_DECLARE_OP(VSMIN_F64)
// op_vec_smax_impl.hpp
_DECLARE_OP(VSMAX_U8)
_DECLARE_OP(VSMAX_U16)
_DECLARE_OP(VSMAX_U32)
_DECLARE_OP(VSMAX_U64)
_DECLARE_OP(VSMAX_S8)
_DECLARE_OP(VSMAX_S16)
_DECLARE_OP(VSMAX_S32)
_DECLARE_OP(VSMAX_S64)
_DECLARE_OP(VSMAX_F32)
_DECLARE_OP(VSMAX_F64)

 // op_vec_ssum_impl.hpp
_DECLARE_OP(VSSUM_U8)
_DECLARE_OP(VSSUM_U16)
_DECLARE_OP(VSSUM_U32)
_DECLARE_OP(VSSUM_U64)
_DECLARE_OP(VSSUM_S8)
_DECLARE_OP(VSSUM_S16)
_DECLARE_OP(VSSUM_S32)
_DECLARE_OP(VSSUM_S64)
_DECLARE_OP(VSSUM_F32)
_DECLARE_OP(VSSUM_F64)

// op_vec_fill_impl.hpp
_DECLARE_OP(VNEG_S8)
_DECLARE_OP(VNEG_S16)
_DECLARE_OP(VNEG_S32)
_DECLARE_OP(VNEG_S64)
// op_vec_neg_impl.hpp
_DECLARE_OP(VNEG_F32)
_DECLARE_OP(VNEG_F64)
// op_vec_neg_impl.hpp
_DECLARE_OP(VABS_S8)
_DECLARE_OP(VABS_S16)
_DECLARE_OP(VABS_S32)
_DECLARE_OP(VABS_S64)
// op_vec_abs_impl.hpp
_DECLARE_OP(VABS_F32)
_DECLARE_OP(VABS_F64)
// op_vec_abs_impl.hpp
_DECLARE_OP(VINV_8)
// op_vec_inv_impl.hpp
_DECLARE_OP(VSADD_I8)
_DECLARE_OP(VSADD_I16)
_DECLARE_OP(VSADD_I32)
_DECLARE_OP(VSADD_I64)
// op_vec_sadd_impl.hpp
_DECLARE_OP(VSADD_F32)
_DECLARE_OP(VSADD_F64)
// op_vec_sadd_impl.hpp
_DECLARE_OP(VSADDS_U8)
_DECLARE_OP(VSADDS_U16)
_DECLARE_OP(VSADDS_U32)
_DECLARE_OP(VSADDS_U64)
// op_vec_sadd_saturated_impl.hpp
_DECLARE_OP(VSADDS_S8)
_DECLARE_OP(VSADDS_S16)
_DECLARE_OP(VSADDS_S32)
_DECLARE_OP(VSADDS_S64)
// op_vec_sadd_saturated_impl.hpp
_DECLARE_OP(VSSUB_I8)
_DECLARE_OP(VSSUB_I16)
_DECLARE_OP(VSSUB_I32)
_DECLARE_OP(VSSUB_I64)
// op_vec_ssub_impl.hpp
_DECLARE_OP(VSSUB_F32)
_DECLARE_OP(VSSUB_F64)
// op_vec_ssub_impl.hpp
_DECLARE_OP(VSSUBS_U8)
_DECLARE_OP(VSSUBS_U16)
_DECLARE_OP(VSSUBS_U32)
_DECLARE_OP(VSSUBS_U64)
 // op_vec_ssub_saturated_impl.hpp
_DECLARE_OP(VSSUBS_S8)
_DECLARE_OP(VSSUBS_S16)
_DECLARE_OP(VSSUBS_S32)
_DECLARE_OP(VSSUBS_S64)
// op_vec_ssub_saturated_impl.hpp
_DECLARE_OP(VSMUL_U8)
_DECLARE_OP(VSMUL_U16)
_DECLARE_OP(VSMUL_U32)
_DECLARE_OP(VSMUL_U64)
// op_vec_smul_impl.hpp
_DECLARE_OP(VSMUL_S8)
_DECLARE_OP(VSMUL_S16)
_DECLARE_OP(VSMUL_S32)
_DECLARE_OP(VSMUL_S64)
// op_vec_smul_impl.hpp
_DECLARE_OP(VSMUL_F32)
_DECLARE_OP(VSMUL_F64)
 // op_vec_smul_impl.hpp
_DECLARE_OP(VSMULS_U8)
_DECLARE_OP(VSMULS_U16)
_DECLARE_OP(VSMULS_U32)
_DECLARE_OP(VSMULS_U64)
// op_vec_smul_saturated_impl.hpp
_DECLARE_OP(VSMULS_S8)
_DECLARE_OP(VSMULS_S16)
_DECLARE_OP(VSMULS_S32)
_DECLARE_OP(VSMULS_S64)
// op_vec_smul_saturated_impl.hpp
_DECLARE_OP(VSDIV_U8)
_DECLARE_OP(VSDIV_U16)
_DECLARE_OP(VSDIV_U32)
_DECLARE_OP(VSDIV_U64)
// op_vec_sdiv_impl.hpp
_DECLARE_OP(VSDIV_S8)
_DECLARE_OP(VSDIV_S16)
_DECLARE_OP(VSDIV_S32)
_DECLARE_OP(VSDIV_S64)
// op_vec_sdiv_impl.hpp
_DECLARE_OP(VSDIV_F32)
_DECLARE_OP(VSDIV_F64)
// op_vec_sdiv_impl.hpp
_DECLARE_OP(VSDIVS_S8)
_DECLARE_OP(VSDIVS_S16)
_DECLARE_OP(VSDIVS_S32)
_DECLARE_OP(VSDIVS_S64)
// op_vec_sdiv_saturated_impl.hpp
_DECLARE_OP(VSMOD_U8)
_DECLARE_OP(VSMOD_U16)
_DECLARE_OP(VSMOD_U32)
_DECLARE_OP(VSMOD_U64)
// op_vec_smod_impl.hpp
_DECLARE_OP(VSMOD_S8)
_DECLARE_OP(VSMOD_S16)
_DECLARE_OP(VSMOD_S32)
_DECLARE_OP(VSMOD_S64)
// op_vec_smod_impl.hpp
_DECLARE_OP(VSMOD_F32)
_DECLARE_OP(VSMOD_F64)
// op_vec_smod_impl.hpp
_DECLARE_OP(VSAND_8)
_DECLARE_OP(VSAND_16)
_DECLARE_OP(VSAND_32)
_DECLARE_OP(VSAND_64)
// op_vec_sand_impl.hpp
_DECLARE_OP(VSOR_8)
_DECLARE_OP(VSOR_16)
_DECLARE_OP(VSOR_32)
_DECLARE_OP(VSOR_64)
// op_vec_sor_impl.hpp
_DECLARE_OP(VSXOR_8)
_DECLARE_OP(VSXOR_16)
_DECLARE_OP(VSXOR_32)
_DECLARE_OP(VSXOR_64)
// op_vec_sxor_impl.hpp
_DECLARE_OP(VSLSL_8)
_DECLARE_OP(VSLSL_16)
_DECLARE_OP(VSLSL_32)
_DECLARE_OP(VSLSL_64)
// op_vec_slsl_impl.hpp
_DECLARE_OP(VSLSR_8)
_DECLARE_OP(VSLSR_16)
_DECLARE_OP(VSLSR_32)
_DECLARE_OP(VSLSR_64)
// op_vec_slsr_impl.hpp
_DECLARE_OP(VSASL_8)
_DECLARE_OP(VSASL_16)
_DECLARE_OP(VSASL_32)
_DECLARE_OP(VSASL_64)
// op_vec_sasl_impl.hpp
_DECLARE_OP(VSASR_8)
_DECLARE_OP(VSASR_16)
_DECLARE_OP(VSASR_32)
_DECLARE_OP(VSASR_64)
// op_vec_sasr_impl.hpp
_DECLARE_OP(VSROL_8)
_DECLARE_OP(VSROL_16)
_DECLARE_OP(VSROL_32)
_DECLARE_OP(VSROL_64)
// op_vec_srol_impl.hpp
_DECLARE_OP(VSROR_8)
_DECLARE_OP(VSROR_16)
_DECLARE_OP(VSROR_32)
_DECLARE_OP(VSROR_64)
// op_vec_sror_impl.hpp
_DECLARE_OP(VADD_I8)
_DECLARE_OP(VADD_I16)
_DECLARE_OP(VADD_I32)
_DECLARE_OP(VADD_I64)
// op_vec_vadd_impl.hpp
_DECLARE_OP(VADD_F32)
_DECLARE_OP(VADD_F64)
// op_vec_vadd_impl.hpp
_DECLARE_OP(VADDS_U8)
_DECLARE_OP(VADDS_U16)
_DECLARE_OP(VADDS_U32)
_DECLARE_OP(VADDS_U64)
// op_vec_vadd_saturated_impl.hpp
_DECLARE_OP(VADDS_S8)
_DECLARE_OP(VADDS_S16)
_DECLARE_OP(VADDS_S32)
_DECLARE_OP(VADDS_S64)
// op_vec_vadd_saturated_impl.hpp
_DECLARE_OP(VSUB_I8)
_DECLARE_OP(VSUB_I16)
_DECLARE_OP(VSUB_I32)
_DECLARE_OP(VSUB_I64)
// op_vec_vsub_impl.hpp
_DECLARE_OP(VSUB_F32)
_DECLARE_OP(VSUB_F64)
// op_vec_vsub_impl.hpp
_DECLARE_OP(VSUBS_U8)
_DECLARE_OP(VSUBS_U16)
_DECLARE_OP(VSUBS_U32)
_DECLARE_OP(VSUBS_U64)
// op_vec_vsub_saturated_impl.hpp
_DECLARE_OP(VSUBS_S8)
_DECLARE_OP(VSUBS_S16)
_DECLARE_OP(VSUBS_S32)
_DECLARE_OP(VSUBS_S64)
// op_vec_vsub_saturated_impl.hpp
_DECLARE_OP(VMUL_U8)
_DECLARE_OP(VMUL_U16)
_DECLARE_OP(VMUL_U32)
_DECLARE_OP(VMUL_U64)
// op_vec_vmul_impl.hpp
_DECLARE_OP(VMUL_S8)
_DECLARE_OP(VMUL_S16)
_DECLARE_OP(VMUL_S32)
_DECLARE_OP(VMUL_S64)
// op_vec_vmul_impl.hpp
_DECLARE_OP(VMUL_F32)
_DECLARE_OP(VMUL_F64)
// op_vec_vmul_impl.hpp
_DECLARE_OP(VMULS_U8)
_DECLARE_OP(VMULS_U16)
_DECLARE_OP(VMULS_U32)
_DECLARE_OP(VMULS_U64)
// op_vec_vmul_saturated_impl.hpp
_DECLARE_OP(VMULS_S8)
_DECLARE_OP(VMULS_S16)
_DECLARE_OP(VMULS_S32)
_DECLARE_OP(VMULS_S64)
// op_vec_vmul_saturated_impl.hpp
_DECLARE_OP(VDIV_U8)
_DECLARE_OP(VDIV_U16)
_DECLARE_OP(VDIV_U32)
_DECLARE_OP(VDIV_U64)
// op_vec_vdiv_impl.hpp
_DECLARE_OP(VDIV_S8)
_DECLARE_OP(VDIV_S16)
_DECLARE_OP(VDIV_S32)
_DECLARE_OP(VDIV_S64)
// op_vec_vdiv_impl.hpp
_DECLARE_OP(VDIV_F32)
_DECLARE_OP(VDIV_F64)
// op_vec_vdiv_impl.hpp
_DECLARE_OP(VDIVS_S8)
_DECLARE_OP(VDIVS_S16)
_DECLARE_OP(VDIVS_S32)
_DECLARE_OP(VDIVS_S64)
// op_vec_vdiv_saturated_impl.hpp
_DECLARE_OP(VMOD_U8)
_DECLARE_OP(VMOD_U16)
_DECLARE_OP(VMOD_U32)
_DECLARE_OP(VMOD_U64)
// op_vec_vmod_impl.hpp
_DECLARE_OP(VMOD_S8)
_DECLARE_OP(VMOD_S16)
_DECLARE_OP(VMOD_S32)
_DECLARE_OP(VMOD_S64)
// op_vec_vmod_impl.hpp
_DECLARE_OP(VMOD_F32)
_DECLARE_OP(VMOD_F64)
// op_vec_vmod_impl.hpp
_DECLARE_OP(VAND_8)
_DECLARE_OP(VOR_8)
_DECLARE_OP(VXOR_8)
// op_vec_vmap_impl.hpp
_DECLARE_OP(VMAP_8_16)
_DECLARE_OP(VMAP_8_32)
_DECLARE_OP(VMAP_8_64)
_DECLARE_OP(VMAP_16_32)
_DECLARE_OP(VMAP_16_64)

// op_vec_vmac_impl.hpp
_DECLARE_OP(VMAC_F32)
_DECLARE_OP(VMAC_F64)

static const Handler handlers[256];         // normal handlers
static const Handler advancedHandlers[256]; // advanced handlers
static const Handler vectorHandlers[256];   // vector handlers

