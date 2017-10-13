//****************************************************************************//
//**                                                                        **//
//** File:         op_vector.cpp                                            **//
//** Description:  Vectorised instructions (array primitives)               **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2017-08                                                  **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//
#include "include/vm_core.hpp"
#include "include/vm_inline.hpp"
#include "include/machine.hpp"
#include <cstdio>

#include <limits.h>

#if _VM_INTERPRETER == _VM_INTERPRETER_FUNC_TABLE
  #include "include/vm_interpreter_func_table.hpp"
#elif _VM_INTERPRETER == _VM_INTERPRETER_SWITCH_CASE
  #include "include/vm_interpreter_switch_case.hpp"
#elif _VM_INTERPRETER == _VM_INTERPRETER_CUSTOM
  #include "include/vm_interpreter_custom.hpp"
#endif


/*
#if _VM_INTERPRETER == _VM_INTERPRETER_FUNC_TABLE

  #include "include/vm_interpreter_func_table.hpp"


// Upon entry, the pc points to the 16-bit word following the current opcode.
// Normally, this would be the address of the next opcode. Handlers that use
// extension words must ensure that they increment the pc so that it points
// to the next opcode.

// Arguments:
// vm is a pointer to the VMCore instance
// op is the current opcode word

  #include "include/op_jump_impl.hpp"

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

void ExVM::Interpreter::doVEC1(ExVM::Interpreter* vm, uint16 op) {

  // The next word in the instruction stream defines up to 4 registers
  uint16 vArgs = *vm->pc.inst++;

#if _VM_INTERPRETER == _VM_INTERPRETER_FUNC_TABLE
  #include "include/vm_interpreter_vec_func_table_impl.hpp"
#elif _VM_INTERPRETER == _VM_INTERPRETER_SWITCH_CASE
  #include "include/vm_interpreter_vec_switch_case_impl.hpp"
#elif _VM_INTERPRETER == _VM_INTERPRETER_CUSTOM
  #include "include/vm_interpreter_vec_custom_impl.hpp"
#endif

}

#if _VM_INTERPRETER == _VM_INTERPRETER_FUNC_TABLE
  #include <cmath>
  #undef _DEFINE_OP
  #define _DEFINE_OP(x) void ExVM::Interpreter::do##x(ExVM::Interpreter* vm UNUSED, uint16 vArgs UNUSED)

  // Implementation Level 0 //////////////////////////////////////////////////////////////////////////////////////////

  // Single vector operations (destination or source only)
  #include "include/opcodes/vector/op_vec_fill_impl_l0.hpp"
  #include "include/opcodes/vector/op_vec_smin_impl_l0.hpp"
  #include "include/opcodes/vector/op_vec_smax_impl_l0.hpp"
  #include "include/opcodes/vector/op_vec_ssum_impl_l0.hpp"

  // Two vector operations (usually scalar and source to destination)
  #include "include/opcodes/vector/op_vec_neg_impl_l0.hpp"
  #include "include/opcodes/vector/op_vec_abs_impl_l0.hpp"
  #include "include/opcodes/vector/op_vec_inv_impl_l0.hpp"
  #include "include/opcodes/vector/op_vec_sadd_impl_l0.hpp"
  #include "include/opcodes/vector/op_vec_sadd_saturated_impl_l0.hpp"
  #include "include/opcodes/vector/op_vec_ssub_impl_l0.hpp"
  #include "include/opcodes/vector/op_vec_ssub_saturated_impl_l0.hpp"
  #include "include/opcodes/vector/op_vec_smul_impl_l0.hpp"
  #include "include/opcodes/vector/op_vec_smul_saturated_impl_l0.hpp"
  #include "include/opcodes/vector/op_vec_sdiv_impl_l0.hpp"
  #include "include/opcodes/vector/op_vec_sdiv_saturated_impl_l0.hpp"
  #include "include/opcodes/vector/op_vec_smod_impl_l0.hpp"
  #include "include/opcodes/vector/op_vec_sand_impl_l0.hpp"
  #include "include/opcodes/vector/op_vec_sor_impl_l0.hpp"
  #include "include/opcodes/vector/op_vec_sxor_impl_l0.hpp"
  #include "include/opcodes/vector/op_vec_slsl_impl_l0.hpp"
  #include "include/opcodes/vector/op_vec_slsr_impl_l0.hpp"
  #include "include/opcodes/vector/op_vec_sasl_impl_l0.hpp"
  #include "include/opcodes/vector/op_vec_sasr_impl_l0.hpp"
  #include "include/opcodes/vector/op_vec_srol_impl_l0.hpp"
  #include "include/opcodes/vector/op_vec_sror_impl_l0.hpp"

  // Three vector operations (source1 and source2 to destination)
  #include "include/opcodes/vector/op_vec_vadd_impl_l0.hpp"
  #include "include/opcodes/vector/op_vec_vadd_saturated_impl_l0.hpp"
  #include "include/opcodes/vector/op_vec_vsub_impl_l0.hpp"
  #include "include/opcodes/vector/op_vec_vsub_saturated_impl_l0.hpp"
  #include "include/opcodes/vector/op_vec_vmul_impl_l0.hpp"
  #include "include/opcodes/vector/op_vec_vmul_saturated_impl_l0.hpp"
  #include "include/opcodes/vector/op_vec_vdiv_impl_l0.hpp"
  #include "include/opcodes/vector/op_vec_vdiv_saturated_impl_l0.hpp"
  #include "include/opcodes/vector/op_vec_vmod_impl_l0.hpp"
  #include "include/opcodes/vector/op_vec_vbitwise_impl_l0.hpp"
  #include "include/opcodes/vector/op_vec_vmap_impl_l0.hpp"

  // Implementation Level 1 //////////////////////////////////////////////////////////////////////////////////////////

  // Single vector operations (destination or source only)
  #include "include/opcodes/vector/op_vec_smin_impl_l1.hpp"
  #include "include/opcodes/vector/op_vec_smax_impl_l1.hpp"
  #include "include/opcodes/vector/op_vec_ssum_impl_l1.hpp"

  // Two vector operations (usually scalar and source to destination)
  #include "include/opcodes/vector/op_vec_neg_impl_l1.hpp"
  #include "include/opcodes/vector/op_vec_abs_impl_l1.hpp"
  #include "include/opcodes/vector/op_vec_sadd_impl_l1.hpp"
  #include "include/opcodes/vector/op_vec_ssub_impl_l1.hpp"
  #include "include/opcodes/vector/op_vec_smul_impl_l1.hpp"
  #include "include/opcodes/vector/op_vec_sdiv_impl_l1.hpp"
  #include "include/opcodes/vector/op_vec_smod_impl_l1.hpp"

  // Three vector operations (source1 and source2 to destination)
  #include "include/opcodes/vector/op_vec_vadd_impl_l1.hpp"
  #include "include/opcodes/vector/op_vec_vsub_impl_l1.hpp"
  #include "include/opcodes/vector/op_vec_vmul_impl_l1.hpp"
  #include "include/opcodes/vector/op_vec_vdiv_impl_l1.hpp"
  #include "include/opcodes/vector/op_vec_vmod_impl_l1.hpp"
  #include "include/opcodes/vector/op_vec_vmac_impl_l1.hpp"

  // Implementation Level 2 //////////////////////////////////////////////////////////////////////////////////////////

  // Single vector operations (destination or source only)
  #include "include/opcodes/vector/op_vec_fill_impl_l2.hpp"
  #include "include/opcodes/vector/op_vec_smin_impl_l2.hpp"
  #include "include/opcodes/vector/op_vec_smax_impl_l2.hpp"
  #include "include/opcodes/vector/op_vec_ssum_impl_l2.hpp"

  // Two vector operations (usually scalar and source to destination)
  #include "include/opcodes/vector/op_vec_neg_impl_l2.hpp"
  #include "include/opcodes/vector/op_vec_abs_impl_l2.hpp"
  #include "include/opcodes/vector/op_vec_sadd_impl_l2.hpp"
  #include "include/opcodes/vector/op_vec_sadd_saturated_impl_l2.hpp"
  #include "include/opcodes/vector/op_vec_ssub_impl_l2.hpp"
  #include "include/opcodes/vector/op_vec_ssub_saturated_impl_l2.hpp"
  #include "include/opcodes/vector/op_vec_smul_impl_l2.hpp"
  #include "include/opcodes/vector/op_vec_smul_saturated_impl_l2.hpp"
  #include "include/opcodes/vector/op_vec_sdiv_impl_l2.hpp"
  #include "include/opcodes/vector/op_vec_sdiv_saturated_impl_l2.hpp"
  #include "include/opcodes/vector/op_vec_smod_impl_l2.hpp"
  #include "include/opcodes/vector/op_vec_sand_impl_l2.hpp"
  #include "include/opcodes/vector/op_vec_sor_impl_l2.hpp"
  #include "include/opcodes/vector/op_vec_sxor_impl_l2.hpp"
  #include "include/opcodes/vector/op_vec_slsl_impl_l2.hpp"
  #include "include/opcodes/vector/op_vec_slsr_impl_l2.hpp"
  #include "include/opcodes/vector/op_vec_sasl_impl_l2.hpp"
  #include "include/opcodes/vector/op_vec_sasr_impl_l2.hpp"
  #include "include/opcodes/vector/op_vec_srol_impl_l2.hpp"
  #include "include/opcodes/vector/op_vec_sror_impl_l2.hpp"

  // Three vector operations (source1 and source2 to destination)
  #include "include/opcodes/vector/op_vec_vadd_impl_l2.hpp"
  #include "include/opcodes/vector/op_vec_vadd_saturated_impl_l2.hpp"
  #include "include/opcodes/vector/op_vec_vsub_impl_l2.hpp"
  #include "include/opcodes/vector/op_vec_vsub_saturated_impl_l2.hpp"
  #include "include/opcodes/vector/op_vec_vmul_impl_l2.hpp"
  #include "include/opcodes/vector/op_vec_vmul_saturated_impl_l2.hpp"
  #include "include/opcodes/vector/op_vec_vdiv_impl_l2.hpp"
  #include "include/opcodes/vector/op_vec_vdiv_saturated_impl_l2.hpp"
  #include "include/opcodes/vector/op_vec_vmod_impl_l2.hpp"
  #include "include/opcodes/vector/op_vec_vmap_impl_l2.hpp"
  #include "include/opcodes/vector/op_vec_vmac_impl_l2.hpp"


#endif
