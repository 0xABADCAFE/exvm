//****************************************************************************//
//**                                                                        **//
//** File:         vm_vec_interpreter_switch_case.hpp                       **//
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
    #include "op_vec_fill_impl.hpp"
    #include "op_vec_neg_impl.hpp"
    #include "op_vec_abs_impl.hpp"
    #include "op_vec_inv_impl.hpp"
    #include "op_vec_sadd_impl.hpp"
    #include "op_vec_sadd_saturated_impl.hpp"
    #include "op_vec_ssub_impl.hpp"
    #include "op_vec_ssub_saturated_impl.hpp"
    #include "op_vec_smul_impl.hpp"
    #include "op_vec_smul_saturated_impl.hpp"
    #include "op_vec_sdiv_impl.hpp"
    #include "op_vec_sdiv_saturated_impl.hpp"
    #include "op_vec_smod_impl.hpp"
    #include "op_vec_sand_impl.hpp"
    #include "op_vec_sor_impl.hpp"
    #include "op_vec_sxor_impl.hpp"
    #include "op_vec_slsl_impl.hpp"
    #include "op_vec_slsr_impl.hpp"
    #include "op_vec_sasl_impl.hpp"
    #include "op_vec_sasr_impl.hpp"
    #include "op_vec_srol_impl.hpp"
    #include "op_vec_sror_impl.hpp"

    default:
      printf("No vector handler yet defined for opcode 0x%04X\n", (unsigned)op);
      vm->status = VMDefs::BREAKPOINT;
      return;
  }
}

