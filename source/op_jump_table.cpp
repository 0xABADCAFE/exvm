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
  printf("No handler yet defined for opcode 0x%04X\n", (unsigned)op);
  vm->status = VMDefs::BREAKPOINT;
}



// normal instruction set

const Interpreter::Handler Interpreter::handlers[256] = {
  // control group
  _REFER_OP(NOP),
  _REFER_OP(BRK),

  // load group
  _REFER_OP(LDQ),
  _REFER_OP(LD_I16_8),
  _REFER_OP(LD_I16_16),
  _REFER_OP(LD_I16_32),
  _REFER_OP(LD_I16_64),
  _REFER_OP(LD_I32_32),
  _REFER_OP(LD_I32_64),
  _REFER_OP(LD_F32),
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
  _REFER_OP(VEC1),
  // misc group

  _REFER_OP(ILLEGAL),

  _REFER_OP(ILLEGAL)
};

const Interpreter::Handler Interpreter::vectorHandlers[256] = {

  _REFER_OP(FILL_8),  _REFER_OP(FILL_16),  _REFER_OP(FILL_32),  _REFER_OP(FILL_64), // op_vec_fill_impl.hpp
  _REFER_OP(NEG_S8),  _REFER_OP(NEG_S16),  _REFER_OP(NEG_S32),  _REFER_OP(NEG_S64), // op_vec_neg_impl.hpp
  _REFER_OP(NEG_F32), _REFER_OP(NEG_F64), // op_vec_neg_impl.hpp
  _REFER_OP(ABS_S8),  _REFER_OP(ABS_S16),  _REFER_OP(ABS_S32),  _REFER_OP(ABS_S64), // op_vec_abs_impl.hpp
  _REFER_OP(ABS_F32), _REFER_OP(ABS_F64), // op_vec_abs_impl.hpp
  _REFER_OP(INV_8), // op_vec_inv_impl.hpp
  _REFER_OP(SADD_I8),  _REFER_OP(SADD_I16),  _REFER_OP(SADD_I32),  _REFER_OP(SADD_I64), // op_vec_sadd_impl.hpp
  _REFER_OP(SADD_F32), _REFER_OP(SADD_F64), // op_vec_sadd_impl.hpp
  _REFER_OP(SADDS_U8), _REFER_OP(SADDS_U16), _REFER_OP(SADDS_U32), _REFER_OP(SADDS_U64), // op_vec_sadd_saturated_impl.hpp
  _REFER_OP(SADDS_S8), _REFER_OP(SADDS_S16), _REFER_OP(SADDS_S32), _REFER_OP(SADDS_S64), // op_vec_sadd_saturated_impl.hpp
  _REFER_OP(SSUB_I8),  _REFER_OP(SSUB_I16),  _REFER_OP(SSUB_I32),  _REFER_OP(SSUB_I64), // op_vec_ssub_impl.hpp
  _REFER_OP(SSUB_F32), _REFER_OP(SSUB_F64), // op_vec_ssub_impl.hpp
  _REFER_OP(SSUBS_U8), _REFER_OP(SSUBS_U16), _REFER_OP(SSUBS_U32), _REFER_OP(SSUBS_U64), // op_vec_ssub_saturated_impl.hpp
  _REFER_OP(SSUBS_S8), _REFER_OP(SSUBS_S16), _REFER_OP(SSUBS_S32), _REFER_OP(SSUBS_S64), // op_vec_ssub_saturated_impl.hpp
  _REFER_OP(SMUL_U8),  _REFER_OP(SMUL_U16),  _REFER_OP(SMUL_U32),  _REFER_OP(SMUL_U64), // op_vec_smul_impl.hpp
  _REFER_OP(SMUL_S8),  _REFER_OP(SMUL_S16),  _REFER_OP(SMUL_S32),  _REFER_OP(SMUL_S64), // op_vec_smul_impl.hpp
  _REFER_OP(SMUL_F32), _REFER_OP(SMUL_F64), // op_vec_smul_impl.hpp
  _REFER_OP(SMULS_U8), _REFER_OP(SMULS_U16), _REFER_OP(SMULS_U32), _REFER_OP(SMULS_U64), // op_vec_smul_saturated_impl.hpp
  _REFER_OP(SMULS_S8), _REFER_OP(SMULS_S16), _REFER_OP(SMULS_S32), _REFER_OP(SMULS_S64), // op_vec_smul_saturated_impl.hpp
  _REFER_OP(SDIV_U8),  _REFER_OP(SDIV_U16),  _REFER_OP(SDIV_U32),  _REFER_OP(SDIV_U64), // op_vec_sdiv_impl.hpp
  _REFER_OP(SDIV_S8),  _REFER_OP(SDIV_S16),  _REFER_OP(SDIV_S32),  _REFER_OP(SDIV_S64), // op_vec_sdiv_impl.hpp
  _REFER_OP(SDIV_F32), _REFER_OP(SDIV_F64), // op_vec_sdiv_impl.hpp
  _REFER_OP(SDIVS_S8), _REFER_OP(SDIVS_S16), _REFER_OP(SDIVS_S32), _REFER_OP(SDIVS_S64), // op_vec_sdiv_saturated_impl.hpp
  _REFER_OP(SMOD_U8),  _REFER_OP(SMOD_U16),  _REFER_OP(SMOD_U32),  _REFER_OP(SMOD_U64), // op_vec_smod_impl.hpp
  _REFER_OP(SMOD_S8),  _REFER_OP(SMOD_S16),  _REFER_OP(SMOD_S32),  _REFER_OP(SMOD_S64), // op_vec_smod_impl.hpp
  _REFER_OP(SMOD_F32), _REFER_OP(SMOD_F64), // op_vec_smod_impl.hpp
  _REFER_OP(SAND_8),   _REFER_OP(SAND_16),   _REFER_OP(SAND_32),   _REFER_OP(SAND_64), // op_vec_sand_impl.hpp
  _REFER_OP(SOR_8),    _REFER_OP(SOR_16),    _REFER_OP(SOR_32),    _REFER_OP(SOR_64), // op_vec_sor_impl.hpp
  _REFER_OP(SXOR_8),   _REFER_OP(SXOR_16),   _REFER_OP(SXOR_32),   _REFER_OP(SXOR_64), // op_vec_sxor_impl.hpp
  _REFER_OP(SLSL_8),   _REFER_OP(SLSL_16),   _REFER_OP(SLSL_32),   _REFER_OP(SLSL_64), // op_vec_slsl_impl.hpp
  _REFER_OP(SLSR_8),   _REFER_OP(SLSR_16),   _REFER_OP(SLSR_32),   _REFER_OP(SLSR_64), // op_vec_slsr_impl.hpp
  _REFER_OP(SASL_8),   _REFER_OP(SASL_16),   _REFER_OP(SASL_32),   _REFER_OP(SASL_64), // op_vec_sasl_impl.hpp
  _REFER_OP(SASR_8),   _REFER_OP(SASR_16),   _REFER_OP(SASR_32),   _REFER_OP(SASR_64), // op_vec_sasr_impl.hpp
  _REFER_OP(SROL_8),   _REFER_OP(SROL_16),   _REFER_OP(SROL_32),   _REFER_OP(SROL_64), // op_vec_srol_impl.hpp
  _REFER_OP(SROR_8),   _REFER_OP(SROR_16),   _REFER_OP(SROR_32),   _REFER_OP(SROR_64), // op_vec_sror_impl.hpp
  _REFER_OP(ADD_I8),  _REFER_OP(ADD_I16),  _REFER_OP(ADD_I32),  _REFER_OP(ADD_I64), // op_vec_vadd_impl.hpp
  _REFER_OP(ADD_F32), _REFER_OP(ADD_F64), // op_vec_vadd_impl.hpp
  _REFER_OP(ADDS_U8), _REFER_OP(ADDS_U16), _REFER_OP(ADDS_U32), _REFER_OP(ADDS_U64), // op_vec_vadd_saturated_impl.hpp
  _REFER_OP(ADDS_S8), _REFER_OP(ADDS_S16), _REFER_OP(ADDS_S32), _REFER_OP(ADDS_S64), // op_vec_vadd_saturated_impl.hpp
  _REFER_OP(SUB_I8),  _REFER_OP(SUB_I16),  _REFER_OP(SUB_I32),  _REFER_OP(SUB_I64), // op_vec_vsub_impl.hpp
  _REFER_OP(SUB_F32), _REFER_OP(SUB_F64), // op_vec_vsub_impl.hpp
  _REFER_OP(SUBS_U8), _REFER_OP(SUBS_U16), _REFER_OP(SUBS_U32), _REFER_OP(SUBS_U64), // op_vec_vsub_saturated_impl.hpp
  _REFER_OP(SUBS_S8), _REFER_OP(SUBS_S16), _REFER_OP(SUBS_S32), _REFER_OP(SUBS_S64), // op_vec_vsub_saturated_impl.hpp
  _REFER_OP(MUL_U8),  _REFER_OP(MUL_U16),  _REFER_OP(MUL_U32),  _REFER_OP(MUL_U64), // op_vec_vmul_impl.hpp
  _REFER_OP(MUL_S8),  _REFER_OP(MUL_S16),  _REFER_OP(MUL_S32),  _REFER_OP(MUL_S64), // op_vec_vmul_impl.hpp
  _REFER_OP(MUL_F32), _REFER_OP(MUL_F64), // op_vec_vmul_impl.hpp
  _REFER_OP(MULS_U8), _REFER_OP(MULS_U16), _REFER_OP(MULS_U32), _REFER_OP(MULS_U64), // op_vec_vmul_saturated_impl.hpp
  _REFER_OP(MULS_S8), _REFER_OP(MULS_S16), _REFER_OP(MULS_S32), _REFER_OP(MULS_S64), // op_vec_vmul_saturated_impl.hpp
  _REFER_OP(DIV_U8),  _REFER_OP(DIV_U16),  _REFER_OP(DIV_U32),  _REFER_OP(DIV_U64), // op_vec_vdiv_impl.hpp
  _REFER_OP(DIV_S8),  _REFER_OP(DIV_S16),  _REFER_OP(DIV_S32),  _REFER_OP(DIV_S64), // op_vec_vdiv_impl.hpp
  _REFER_OP(DIV_F32), _REFER_OP(DIV_F64), // op_vec_vdiv_impl.hpp
  _REFER_OP(DIVS_S8), _REFER_OP(DIVS_S16), _REFER_OP(DIVS_S32), _REFER_OP(DIVS_S64), // op_vec_vdiv_saturated_impl.hpp
  _REFER_OP(MOD_U8),  _REFER_OP(MOD_U16),  _REFER_OP(MOD_U32),  _REFER_OP(MOD_U64), // op_vec_vmod_impl.hpp
  _REFER_OP(MOD_S8),  _REFER_OP(MOD_S16),  _REFER_OP(MOD_S32),  _REFER_OP(MOD_S64), // op_vec_vmod_impl.hpp
  _REFER_OP(MOD_F32), _REFER_OP(MOD_F64), // op_vec_vmod_impl.hpp
  _REFER_OP(AND_8),   _REFER_OP(OR_8),     _REFER_OP(XOR_8),
};


#endif
