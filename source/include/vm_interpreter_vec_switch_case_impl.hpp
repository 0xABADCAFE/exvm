//****************************************************************************//
//**                                                                        **//
//** File:         vm_interpreter_vec_switch_case.hpp                       **//
//** Description:  Interpreter class definition                             **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2001-08-29                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

{

  switch (op & 0xFF) {
    // Includes added in strict order of the opcode enumerations

    // Implementation Level 0 //////////////////////////////////////////////////////////////////////////////////////////

    // Single vector operations (destination or source only)
    #include "opcodes/vector/op_vec_fill_impl_l0.hpp"
    #include "opcodes/vector/op_vec_smin_impl_l0.hpp"
    #include "opcodes/vector/op_vec_smax_impl_l0.hpp"
    #include "opcodes/vector/op_vec_ssum_impl_l0.hpp"

    // Two vector operations (usually scalar and source to destination)
    #include "opcodes/vector/op_vec_neg_impl_l0.hpp"
    #include "opcodes/vector/op_vec_abs_impl_l0.hpp"
    #include "opcodes/vector/op_vec_inv_impl_l0.hpp"
    #include "opcodes/vector/op_vec_sadd_impl_l0.hpp"
    #include "opcodes/vector/op_vec_sadd_saturated_impl_l0.hpp"
    #include "opcodes/vector/op_vec_ssub_impl_l0.hpp"
    #include "opcodes/vector/op_vec_ssub_saturated_impl_l0.hpp"
    #include "opcodes/vector/op_vec_smul_impl_l0.hpp"
    #include "opcodes/vector/op_vec_smul_saturated_impl_l0.hpp"
    #include "opcodes/vector/op_vec_sdiv_impl_l0.hpp"
    #include "opcodes/vector/op_vec_sdiv_saturated_impl_l0.hpp"
    #include "opcodes/vector/op_vec_smod_impl_l0.hpp"
    #include "opcodes/vector/op_vec_sand_impl_l0.hpp"
    #include "opcodes/vector/op_vec_sor_impl_l0.hpp"
    #include "opcodes/vector/op_vec_sxor_impl_l0.hpp"
    #include "opcodes/vector/op_vec_slsl_impl_l0.hpp"
    #include "opcodes/vector/op_vec_slsr_impl_l0.hpp"
    #include "opcodes/vector/op_vec_sasl_impl_l0.hpp"
    #include "opcodes/vector/op_vec_sasr_impl_l0.hpp"
    #include "opcodes/vector/op_vec_srol_impl_l0.hpp"
    #include "opcodes/vector/op_vec_sror_impl_l0.hpp"

    // Three vector operations (source1 and source2 to destination)
    #include "opcodes/vector/op_vec_vadd_impl_l0.hpp"
    #include "opcodes/vector/op_vec_vadd_saturated_impl_l0.hpp"
    #include "opcodes/vector/op_vec_vsub_impl_l0.hpp"
    #include "opcodes/vector/op_vec_vsub_saturated_impl_l0.hpp"
    #include "opcodes/vector/op_vec_vmul_impl_l0.hpp"
    #include "opcodes/vector/op_vec_vmul_saturated_impl_l0.hpp"
    #include "opcodes/vector/op_vec_vdiv_impl_l0.hpp"
    #include "opcodes/vector/op_vec_vdiv_saturated_impl_l0.hpp"
    #include "opcodes/vector/op_vec_vmod_impl_l0.hpp"
    #include "opcodes/vector/op_vec_vbitwise_impl_l0.hpp"
    #include "opcodes/vector/op_vec_vmap_impl_l0.hpp"

    // Implementation Level 1 //////////////////////////////////////////////////////////////////////////////////////////

    // Single vector operations (destination or source only)
    #include "opcodes/vector/op_vec_smin_impl_l1.hpp"
    #include "opcodes/vector/op_vec_smax_impl_l1.hpp"
    #include "opcodes/vector/op_vec_ssum_impl_l1.hpp"

    // Two vector operations (usually scalar and source to destination)
    #include "opcodes/vector/op_vec_neg_impl_l1.hpp"
    #include "opcodes/vector/op_vec_abs_impl_l1.hpp"
    #include "opcodes/vector/op_vec_sadd_impl_l1.hpp"
    #include "opcodes/vector/op_vec_ssub_impl_l1.hpp"
    #include "opcodes/vector/op_vec_smul_impl_l1.hpp"
    #include "opcodes/vector/op_vec_sdiv_impl_l1.hpp"
    #include "opcodes/vector/op_vec_smod_impl_l1.hpp"

    // Three vector operations (source1 and source2 to destination)
    #include "opcodes/vector/op_vec_vadd_impl_l1.hpp"
    #include "opcodes/vector/op_vec_vsub_impl_l1.hpp"
    #include "opcodes/vector/op_vec_vmul_impl_l1.hpp"
    #include "opcodes/vector/op_vec_vdiv_impl_l1.hpp"
    #include "opcodes/vector/op_vec_vmod_impl_l1.hpp"
    #include "opcodes/vector/op_vec_vmac_impl_l1.hpp"

    // Implementation Level 2 //////////////////////////////////////////////////////////////////////////////////////////

    // Single vector operations (destination or source only)
    #include "opcodes/vector/op_vec_fill_impl_l2.hpp"
    #include "opcodes/vector/op_vec_smin_impl_l2.hpp"
    #include "opcodes/vector/op_vec_smax_impl_l2.hpp"
    #include "opcodes/vector/op_vec_ssum_impl_l2.hpp"

    // Two vector operations (usually scalar and source to destination)
    #include "opcodes/vector/op_vec_neg_impl_l2.hpp"
    #include "opcodes/vector/op_vec_abs_impl_l2.hpp"
    #include "opcodes/vector/op_vec_sadd_impl_l2.hpp"
    #include "opcodes/vector/op_vec_sadd_saturated_impl_l2.hpp"
    #include "opcodes/vector/op_vec_ssub_impl_l2.hpp"
    #include "opcodes/vector/op_vec_ssub_saturated_impl_l2.hpp"
    #include "opcodes/vector/op_vec_smul_impl_l2.hpp"
    #include "opcodes/vector/op_vec_smul_saturated_impl_l2.hpp"
    #include "opcodes/vector/op_vec_sdiv_impl_l2.hpp"
    #include "opcodes/vector/op_vec_sdiv_saturated_impl_l2.hpp"
    #include "opcodes/vector/op_vec_smod_impl_l2.hpp"
    #include "opcodes/vector/op_vec_sand_impl_l2.hpp"
    #include "opcodes/vector/op_vec_sor_impl_l2.hpp"
    #include "opcodes/vector/op_vec_sxor_impl_l2.hpp"
    #include "opcodes/vector/op_vec_slsl_impl_l2.hpp"
    #include "opcodes/vector/op_vec_slsr_impl_l2.hpp"
    #include "opcodes/vector/op_vec_sasl_impl_l2.hpp"
    #include "opcodes/vector/op_vec_sasr_impl_l2.hpp"
    #include "opcodes/vector/op_vec_srol_impl_l2.hpp"
    #include "opcodes/vector/op_vec_sror_impl_l2.hpp"

    // Three vector operations (source1 and source2 to destination)
    #include "opcodes/vector/op_vec_vadd_impl_l2.hpp"
    #include "opcodes/vector/op_vec_vadd_saturated_impl_l2.hpp"
    #include "opcodes/vector/op_vec_vsub_impl_l2.hpp"
    #include "opcodes/vector/op_vec_vsub_saturated_impl_l2.hpp"
    #include "opcodes/vector/op_vec_vmul_impl_l2.hpp"
    #include "opcodes/vector/op_vec_vmul_saturated_impl_l2.hpp"
    #include "opcodes/vector/op_vec_vdiv_impl_l2.hpp"
    #include "opcodes/vector/op_vec_vdiv_saturated_impl_l2.hpp"
    #include "opcodes/vector/op_vec_vmod_impl_l2.hpp"
    #include "opcodes/vector/op_vec_vmap_impl_l2.hpp"
    #include "opcodes/vector/op_vec_vmac_impl_l2.hpp"

    default:
      debuglog(LOG_ERROR, "No vector handler yet defined for opcode 0x%04X\n", (unsigned)op);
      vm->status = VMDefs::BREAKPOINT;
      return;
  }
}

