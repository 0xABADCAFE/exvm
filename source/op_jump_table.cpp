//****************************************************************************//
//**                                                                        **//
//** File:         op_normal_table.cpp                                      **//
//** Description:  Function Table build model                               **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2001-09-16                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

#include "include/machine.hpp"

#if _VM_INTERPRETER == _VM_INTERPRETER_FUNC_TABLE
  #include "include/vm_core.hpp"
  #include <cstdio>

  #include "include/vm_interpreter_func_table.hpp"
using namespace ExVM;

_DEFINE_OP(ILLEGAL) {
  debuglog(LOG_ERROR, "No handler yet defined for opcode 0x%04X\n", (unsigned)op);
  vm->status = VMDefs::BREAKPOINT;
}



// normal instruction set

const Interpreter::Handler Interpreter::handlers[256] = {
  // control group
  _REFER_OP(NOP),
  _REFER_OP(BRK),

  // load group
  _REFER_OP(LDQ),
  _REFER_OP(LD_16_I8),
  _REFER_OP(LD_16_I16),
  _REFER_OP(LD_16_I32),
  _REFER_OP(LD_16_I64),
  _REFER_OP(LD_32_32),
  _REFER_OP(LD_32_I64),
  _REFER_OP(LD_32_F64),
  _REFER_OP(LD_RI_8),
  _REFER_OP(LD_RI_16),
  _REFER_OP(LD_RI_32),
  _REFER_OP(LD_RI_64),
  _REFER_OP(LD_RIPI_8),
  _REFER_OP(LD_RIPI_16),
  _REFER_OP(LD_RIPI_32),
  _REFER_OP(LD_RIPI_64),
  _REFER_OP(LD_RIPD_8),
  _REFER_OP(LD_RIPD_16),
  _REFER_OP(LD_RIPD_32),
  _REFER_OP(LD_RIPD_64),
  _REFER_OP(LD_RID_8),
  _REFER_OP(LD_RID_16),
  _REFER_OP(LD_RID_32),
  _REFER_OP(LD_RID_64),
  _REFER_OP(LD_RII_8),
  _REFER_OP(LD_RII_16),
  _REFER_OP(LD_RII_32),
  _REFER_OP(LD_RII_64),
  _REFER_OP(LD_8),
  _REFER_OP(LD_16),
  _REFER_OP(LD_32),
  _REFER_OP(LD_64),
  _REFER_OP(LD_ADDR),

  // store group - 24
  _REFER_OP(ST_RI_8),
  _REFER_OP(ST_RI_16),
  _REFER_OP(ST_RI_32),
  _REFER_OP(ST_RI_64),
  _REFER_OP(ST_RIPI_8),
  _REFER_OP(ST_RIPI_16),
  _REFER_OP(ST_RIPI_32),
  _REFER_OP(ST_RIPI_64),
  _REFER_OP(ST_RIPD_8),
  _REFER_OP(ST_RIPD_16),
  _REFER_OP(ST_RIPD_32),
  _REFER_OP(ST_RIPD_64),
  _REFER_OP(ST_RID_8),
  _REFER_OP(ST_RID_16),
  _REFER_OP(ST_RID_32),
  _REFER_OP(ST_RID_64),
  _REFER_OP(ST_RII_8),
  _REFER_OP(ST_RII_16),
  _REFER_OP(ST_RII_32),
  _REFER_OP(ST_RII_64),
  _REFER_OP(ST_8),
  _REFER_OP(ST_16),
  _REFER_OP(ST_32),
  _REFER_OP(ST_64),

  // move group
  _REFER_OP(MV_8),
  _REFER_OP(MV_16),
  _REFER_OP(MV_32),
  _REFER_OP(MV_64),
  _REFER_OP(BSWP_16),
  _REFER_OP(BSWP_32),
  _REFER_OP(BSWP_64),
  _REFER_OP(EXG),
  _REFER_OP(SV),
  _REFER_OP(RS),
  _REFER_OP(PUSH_8),
  _REFER_OP(PUSH_16),
  _REFER_OP(PUSH_32),
  _REFER_OP(PUSH_64),
  _REFER_OP(POP_8),
  _REFER_OP(POP_16),
  _REFER_OP(POP_32),
  _REFER_OP(POP_64),

  // jump group
  _REFER_OP(BCALL8),
  _REFER_OP(BCALL16),
  _REFER_OP(CALL),
  _REFER_OP(CALLN),
  _REFER_OP(RET),
  _REFER_OP(BRA8),
  _REFER_OP(BRA16),
  _REFER_OP(CASE),

  _REFER_OP(BNZ_8),
  _REFER_OP(BNZ_16),
  _REFER_OP(BNZ_32),
  _REFER_OP(BNZ_64),

  _REFER_OP(BEQ_8),
  _REFER_OP(BEQ_16),
  _REFER_OP(BEQ_32),
  _REFER_OP(BEQ_64),
  _REFER_OP(BEQ_F32),
  _REFER_OP(BEQ_F64),
  _REFER_OP(BGREQ_8),
  _REFER_OP(BGREQ_16),
  _REFER_OP(BGREQ_32),
  _REFER_OP(BGREQ_64),
  _REFER_OP(BGREQ_F32),
  _REFER_OP(BGREQ_F64),
  _REFER_OP(BGR_8),
  _REFER_OP(BGR_16),
  _REFER_OP(BGR_32),
  _REFER_OP(BGR_64),
  _REFER_OP(BGR_F32),
  _REFER_OP(BGR_F64),

  // cast widening group
  _REFER_OP(S8_2_S16),
  _REFER_OP(S8_2_S32),
  _REFER_OP(S8_2_S64),
  _REFER_OP(S8_2_F32),
  _REFER_OP(S8_2_F64),
  _REFER_OP(S16_2_S32),
  _REFER_OP(S16_2_S64),
  _REFER_OP(S16_2_F32),
  _REFER_OP(S16_2_F64),
  _REFER_OP(S32_2_S64),
  _REFER_OP(S32_2_F32),
  _REFER_OP(S32_2_F64),
  _REFER_OP(S64_2_F32),
  _REFER_OP(S64_2_F64),
  _REFER_OP(U8_2_F32),
  _REFER_OP(U8_2_F64),
  _REFER_OP(U16_2_F32),
  _REFER_OP(U16_2_F64),
  _REFER_OP(U32_2_F32),
  _REFER_OP(U32_2_F64),
  _REFER_OP(U64_2_F32),
  _REFER_OP(U64_2_F64),
  _REFER_OP(F32_2_F64),

  // cast narrowing group
  _REFER_OP(F64_2_F32),
  _REFER_OP(F64_2_S64),
  _REFER_OP(F64_2_S32),
  _REFER_OP(F64_2_S16),
  _REFER_OP(F64_2_S8),
  _REFER_OP(F32_2_S64),
  _REFER_OP(F32_2_S32),
  _REFER_OP(F32_2_S16),
  _REFER_OP(F32_2_S8),

  // aritmetic group
  _REFER_OP(ADD_I8),
  _REFER_OP(ADD_I16),
  _REFER_OP(ADD_I32),
  _REFER_OP(ADD_I64),
  _REFER_OP(ADD_F32),
  _REFER_OP(ADD_F64),
  _REFER_OP(ADDI_I8),
  _REFER_OP(ADDI_I16),
  _REFER_OP(ADDI_I32),

  _REFER_OP(SUB_I8),
  _REFER_OP(SUB_I16),
  _REFER_OP(SUB_I32),
  _REFER_OP(SUB_I64),
  _REFER_OP(SUB_F32),
  _REFER_OP(SUB_F64),
  _REFER_OP(MUL_U8),
  _REFER_OP(MUL_U16),
  _REFER_OP(MUL_U32),
  _REFER_OP(MUL_U64),
  _REFER_OP(MUL_S8),
  _REFER_OP(MUL_S16),
  _REFER_OP(MUL_S32),
  _REFER_OP(MUL_S64),
  _REFER_OP(MUL_F32),
  _REFER_OP(MUL_F64),
  _REFER_OP(DIV_U8),
  _REFER_OP(DIV_U16),
  _REFER_OP(DIV_U32),
  _REFER_OP(DIV_U64),
  _REFER_OP(DIV_S8),
  _REFER_OP(DIV_S16),
  _REFER_OP(DIV_S32),
  _REFER_OP(DIV_S64),
  _REFER_OP(DIV_F32),
  _REFER_OP(DIV_F64),
  _REFER_OP(MOD_U8),
  _REFER_OP(MOD_U16),
  _REFER_OP(MOD_U32),
  _REFER_OP(MOD_U64),
  _REFER_OP(MOD_S8),
  _REFER_OP(MOD_S16),
  _REFER_OP(MOD_S32),
  _REFER_OP(MOD_S64),
  _REFER_OP(MOD_F32),
  _REFER_OP(MOD_F64),
  _REFER_OP(NEG_S8),
  _REFER_OP(NEG_S16),
  _REFER_OP(NEG_S32),
  _REFER_OP(NEG_S64),
  _REFER_OP(NEG_F32),
  _REFER_OP(NEG_F64),
  _REFER_OP(ASR_S8),
  _REFER_OP(ASR_S16),
  _REFER_OP(ASR_S32),
  _REFER_OP(ASR_S64),
  _REFER_OP(MIN_S8),
  _REFER_OP(MIN_S16),
  _REFER_OP(MIN_S32),
  _REFER_OP(MIN_S64),
  _REFER_OP(MIN_F32),
  _REFER_OP(MIN_F64),
  _REFER_OP(MAX_S8),
  _REFER_OP(MAX_S16),
  _REFER_OP(MAX_S32),
  _REFER_OP(MAX_S64),
  _REFER_OP(MAX_F32),
  _REFER_OP(MAX_F64),
  _REFER_OP(MUL_ADD_F32),
  _REFER_OP(MUL_ADD_F64),
  // logic group
  _REFER_OP(AND_8),
  _REFER_OP(AND_16),
  _REFER_OP(AND_32),
  _REFER_OP(AND_64),
  _REFER_OP(OR_8),
  _REFER_OP(OR_16),
  _REFER_OP(OR_32),
  _REFER_OP(OR_64),
  _REFER_OP(XOR_8),
  _REFER_OP(XOR_16),
  _REFER_OP(XOR_32),
  _REFER_OP(XOR_64),
  _REFER_OP(INV_8),
  _REFER_OP(INV_16),
  _REFER_OP(INV_32),
  _REFER_OP(INV_64),
  _REFER_OP(LSL_8),
  _REFER_OP(LSL_16),
  _REFER_OP(LSL_32),
  _REFER_OP(LSL_64),
  _REFER_OP(LSR_8),
  _REFER_OP(LSR_16),
  _REFER_OP(LSR_32),
  _REFER_OP(LSR_64),
  _REFER_OP(ROL_8),
  _REFER_OP(ROL_16),
  _REFER_OP(ROL_32),
  _REFER_OP(ROL_64),
  _REFER_OP(ROR_8),
  _REFER_OP(ROR_16),
  _REFER_OP(ROR_32),
  _REFER_OP(ROR_64),

  // prefix group
  _REFER_OP(ADV),
  _REFER_OP(VEC1),

  _REFER_OP(ILLEGAL)
};

const Interpreter::Handler Interpreter::vectorHandlers[256] = {
  _REFER_OP(VFILL_8),
  _REFER_OP(VFILL_16),
  _REFER_OP(VFILL_32),
  _REFER_OP(VFILL_64), // op_vec_fill_impl.hpp

  _REFER_OP(VSMIN_U8),
  _REFER_OP(VSMIN_U16),
  _REFER_OP(VSMIN_U32),
  _REFER_OP(VSMIN_U64),
  _REFER_OP(VSMIN_S8),
  _REFER_OP(VSMIN_S16),
  _REFER_OP(VSMIN_S32),
  _REFER_OP(VSMIN_S64),
  _REFER_OP(VSMIN_F32),
  _REFER_OP(VSMIN_F64), // op_vec_smin_impl.hpp

  _REFER_OP(VSMAX_U8),
  _REFER_OP(VSMAX_U16),
  _REFER_OP(VSMAX_U32),
  _REFER_OP(VSMAX_U64),
  _REFER_OP(VSMAX_S8),
  _REFER_OP(VSMAX_S16),
  _REFER_OP(VSMAX_S32),
  _REFER_OP(VSMAX_S64),
  _REFER_OP(VSMAX_F32),
  _REFER_OP(VSMAX_F64), // op_vec_smax_impl.hpp

  _REFER_OP(VSSUM_U8),
  _REFER_OP(VSSUM_U16),
  _REFER_OP(VSSUM_U32),
  _REFER_OP(VSSUM_U64),
  _REFER_OP(VSSUM_S8),
  _REFER_OP(VSSUM_S16),
  _REFER_OP(VSSUM_S32),
  _REFER_OP(VSSUM_S64),
  _REFER_OP(VSSUM_F32),
  _REFER_OP(VSSUM_F64),

  _REFER_OP(VNEG_S8),
  _REFER_OP(VNEG_S16),
  _REFER_OP(VNEG_S32),
  _REFER_OP(VNEG_S64), // op_vec_neg_impl.hpp
  _REFER_OP(VNEG_F32),
  _REFER_OP(VNEG_F64), // op_vec_neg_impl.hpp
  _REFER_OP(VABS_S8),
  _REFER_OP(VABS_S16),
  _REFER_OP(VABS_S32),
  _REFER_OP(VABS_S64), // op_vec_abs_impl.hpp
  _REFER_OP(VABS_F32),
  _REFER_OP(VABS_F64), // op_vec_abs_impl.hpp
  _REFER_OP(VINV_8), // op_vec_inv_impl.hpp
  _REFER_OP(VSADD_I8),
  _REFER_OP(VSADD_I16),
  _REFER_OP(VSADD_I32),
  _REFER_OP(VSADD_I64), // op_vec_sadd_impl.hpp
  _REFER_OP(VSADD_F32),
  _REFER_OP(VSADD_F64), // op_vec_sadd_impl.hpp
  _REFER_OP(VSADDS_U8),
  _REFER_OP(VSADDS_U16),
  _REFER_OP(VSADDS_U32),
  _REFER_OP(VSADDS_U64), // op_vec_sadd_saturated_impl.hpp
  _REFER_OP(VSADDS_S8),
  _REFER_OP(VSADDS_S16),
  _REFER_OP(VSADDS_S32),
  _REFER_OP(VSADDS_S64), // op_vec_sadd_saturated_impl.hpp
  _REFER_OP(VSSUB_I8),
  _REFER_OP(VSSUB_I16),
  _REFER_OP(VSSUB_I32),
  _REFER_OP(VSSUB_I64), // op_vec_ssub_impl.hpp
  _REFER_OP(VSSUB_F32),
  _REFER_OP(VSSUB_F64), // op_vec_ssub_impl.hpp
  _REFER_OP(VSSUBS_U8),
  _REFER_OP(VSSUBS_U16),
  _REFER_OP(VSSUBS_U32),
  _REFER_OP(VSSUBS_U64), // op_vec_ssub_saturated_impl.hpp
  _REFER_OP(VSSUBS_S8),
  _REFER_OP(VSSUBS_S16),
  _REFER_OP(VSSUBS_S32),
  _REFER_OP(VSSUBS_S64), // op_vec_ssub_saturated_impl.hpp
  _REFER_OP(VSMUL_U8),
  _REFER_OP(VSMUL_U16),
  _REFER_OP(VSMUL_U32),
  _REFER_OP(VSMUL_U64), // op_vec_smul_impl.hpp
  _REFER_OP(VSMUL_S8),
  _REFER_OP(VSMUL_S16),
  _REFER_OP(VSMUL_S32),
  _REFER_OP(VSMUL_S64), // op_vec_smul_impl.hpp
  _REFER_OP(VSMUL_F32),
  _REFER_OP(VSMUL_F64), // op_vec_smul_impl.hpp
  _REFER_OP(VSMULS_U8),
  _REFER_OP(VSMULS_U16),
  _REFER_OP(VSMULS_U32),
  _REFER_OP(VSMULS_U64), // op_vec_smul_saturated_impl.hpp
  _REFER_OP(VSMULS_S8),
  _REFER_OP(VSMULS_S16),
  _REFER_OP(VSMULS_S32),
  _REFER_OP(VSMULS_S64), // op_vec_smul_saturated_impl.hpp
  _REFER_OP(VSDIV_U8),
  _REFER_OP(VSDIV_U16),
  _REFER_OP(VSDIV_U32),
  _REFER_OP(VSDIV_U64), // op_vec_sdiv_impl.hpp
  _REFER_OP(VSDIV_S8),
  _REFER_OP(VSDIV_S16),
  _REFER_OP(VSDIV_S32),
  _REFER_OP(VSDIV_S64), // op_vec_sdiv_impl.hpp
  _REFER_OP(VSDIV_F32),
  _REFER_OP(VSDIV_F64), // op_vec_sdiv_impl.hpp
  _REFER_OP(VSDIVS_S8),
  _REFER_OP(VSDIVS_S16),
  _REFER_OP(VSDIVS_S32),
  _REFER_OP(VSDIVS_S64), // op_vec_sdiv_saturated_impl.hpp
  _REFER_OP(VSMOD_U8),
  _REFER_OP(VSMOD_U16),
  _REFER_OP(VSMOD_U32),
  _REFER_OP(VSMOD_U64), // op_vec_smod_impl.hpp
  _REFER_OP(VSMOD_S8),
  _REFER_OP(VSMOD_S16),
  _REFER_OP(VSMOD_S32),
  _REFER_OP(VSMOD_S64), // op_vec_smod_impl.hpp
  _REFER_OP(VSMOD_F32),
  _REFER_OP(VSMOD_F64), // op_vec_smod_impl.hpp
  _REFER_OP(VSAND_8),
  _REFER_OP(VSAND_16),
  _REFER_OP(VSAND_32),
  _REFER_OP(VSAND_64), // op_vec_sand_impl.hpp
  _REFER_OP(VSOR_8),
  _REFER_OP(VSOR_16),
  _REFER_OP(VSOR_32),
  _REFER_OP(VSOR_64), // op_vec_sor_impl.hpp
  _REFER_OP(VSXOR_8),
  _REFER_OP(VSXOR_16),
  _REFER_OP(VSXOR_32),
  _REFER_OP(VSXOR_64), // op_vec_sxor_impl.hpp
  _REFER_OP(VSLSL_8),
  _REFER_OP(VSLSL_16),
  _REFER_OP(VSLSL_32),
  _REFER_OP(VSLSL_64), // op_vec_slsl_impl.hpp
  _REFER_OP(VSLSR_8),
  _REFER_OP(VSLSR_16),
  _REFER_OP(VSLSR_32),
  _REFER_OP(VSLSR_64), // op_vec_slsr_impl.hpp
  _REFER_OP(VSASL_8),
  _REFER_OP(VSASL_16),
  _REFER_OP(VSASL_32),
  _REFER_OP(VSASL_64), // op_vec_sasl_impl.hpp
  _REFER_OP(VSASR_8),
  _REFER_OP(VSASR_16),
  _REFER_OP(VSASR_32),
  _REFER_OP(VSASR_64), // op_vec_sasr_impl.hpp
  _REFER_OP(VSROL_8),
  _REFER_OP(VSROL_16),
  _REFER_OP(VSROL_32),
  _REFER_OP(VSROL_64), // op_vec_srol_impl.hpp
  _REFER_OP(VSROR_8),
  _REFER_OP(VSROR_16),
  _REFER_OP(VSROR_32),
  _REFER_OP(VSROR_64), // op_vec_sror_impl.hpp
  _REFER_OP(VADD_I8),
  _REFER_OP(VADD_I16),
  _REFER_OP(VADD_I32),
  _REFER_OP(VADD_I64), // op_vec_vadd_impl.hpp
  _REFER_OP(VADD_F32),
  _REFER_OP(VADD_F64), // op_vec_vadd_impl.hpp
  _REFER_OP(VADDS_U8),
  _REFER_OP(VADDS_U16),
  _REFER_OP(VADDS_U32),
  _REFER_OP(VADDS_U64), // op_vec_vadd_saturated_impl.hpp
  _REFER_OP(VADDS_S8),
  _REFER_OP(VADDS_S16),
  _REFER_OP(VADDS_S32),
  _REFER_OP(VADDS_S64), // op_vec_vadd_saturated_impl.hpp
  _REFER_OP(VSUB_I8),
  _REFER_OP(VSUB_I16),
  _REFER_OP(VSUB_I32),
  _REFER_OP(VSUB_I64), // op_vec_vsub_impl.hpp
  _REFER_OP(VSUB_F32),
  _REFER_OP(VSUB_F64), // op_vec_vsub_impl.hpp
  _REFER_OP(VSUBS_U8),
  _REFER_OP(VSUBS_U16),
  _REFER_OP(VSUBS_U32),
  _REFER_OP(VSUBS_U64), // op_vec_vsub_saturated_impl.hpp
  _REFER_OP(VSUBS_S8),
  _REFER_OP(VSUBS_S16),
  _REFER_OP(VSUBS_S32),
  _REFER_OP(VSUBS_S64), // op_vec_vsub_saturated_impl.hpp
  _REFER_OP(VMUL_U8),
  _REFER_OP(VMUL_U16),
  _REFER_OP(VMUL_U32),
  _REFER_OP(VMUL_U64), // op_vec_vmul_impl.hpp
  _REFER_OP(VMUL_S8),
  _REFER_OP(VMUL_S16),
  _REFER_OP(VMUL_S32),
  _REFER_OP(VMUL_S64), // op_vec_vmul_impl.hpp
  _REFER_OP(VMUL_F32),
  _REFER_OP(VMUL_F64), // op_vec_vmul_impl.hpp
  _REFER_OP(VMULS_U8),
  _REFER_OP(VMULS_U16),
  _REFER_OP(VMULS_U32),
  _REFER_OP(VMULS_U64), // op_vec_vmul_saturated_impl.hpp
  _REFER_OP(VMULS_S8),
  _REFER_OP(VMULS_S16),
  _REFER_OP(VMULS_S32),
  _REFER_OP(VMULS_S64), // op_vec_vmul_saturated_impl.hpp
  _REFER_OP(VDIV_U8),
  _REFER_OP(VDIV_U16),
  _REFER_OP(VDIV_U32),
  _REFER_OP(VDIV_U64), // op_vec_vdiv_impl.hpp
  _REFER_OP(VDIV_S8),
  _REFER_OP(VDIV_S16),
  _REFER_OP(VDIV_S32),
  _REFER_OP(VDIV_S64), // op_vec_vdiv_impl.hpp
  _REFER_OP(VDIV_F32),
  _REFER_OP(VDIV_F64), // op_vec_vdiv_impl.hpp
  _REFER_OP(VDIVS_S8),
  _REFER_OP(VDIVS_S16),
  _REFER_OP(VDIVS_S32),
  _REFER_OP(VDIVS_S64), // op_vec_vdiv_saturated_impl.hpp
  _REFER_OP(VMOD_U8),
  _REFER_OP(VMOD_U16),
  _REFER_OP(VMOD_U32),
  _REFER_OP(VMOD_U64), // op_vec_vmod_impl.hpp
  _REFER_OP(VMOD_S8),
  _REFER_OP(VMOD_S16),
  _REFER_OP(VMOD_S32),
  _REFER_OP(VMOD_S64), // op_vec_vmod_impl.hpp
  _REFER_OP(VMOD_F32),
  _REFER_OP(VMOD_F64), // op_vec_vmod_impl.hpp
  _REFER_OP(VAND_8),
  _REFER_OP(VOR_8),
  _REFER_OP(VXOR_8),

  _REFER_OP(VMAP_8_16),
  _REFER_OP(VMAP_8_32),
  _REFER_OP(VMAP_8_64),
  _REFER_OP(VMAP_16_32),
  _REFER_OP(VMAP_16_64),
};


#endif
