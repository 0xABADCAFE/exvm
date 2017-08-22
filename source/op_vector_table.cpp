//****************************************************************************//
//**                                                                        **//
//** File:         op_vector_table.cpp                                      **//
//** Description:  Function Table build model                               **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2017-08-17                                               **//
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

// vector instruction set

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
