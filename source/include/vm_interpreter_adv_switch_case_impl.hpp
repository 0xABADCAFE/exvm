//****************************************************************************//
//**                                                                        **//
//** File:         vm_interpreter_adv_switch_case.hpp                       **//
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

    // Implementation level 0
    #include "opcodes/advanced/op_adv_load_impl_l0.hpp"
    #include "opcodes/advanced/op_adv_store_impl_l0.hpp"
    #include "opcodes/advanced/op_adv_logic_impl_l0.hpp"

    // Implementation level 1
    #include "opcodes/advanced/op_adv_const_impl_l1.hpp"
    #include "opcodes/advanced/op_adv_madd_impl_l1.hpp"
    #include "opcodes/advanced/op_adv_roots_impl_l1.hpp"
    #include "opcodes/advanced/op_adv_trig_impl_l1.hpp"
    #include "opcodes/advanced/op_adv_powers_impl_l1.hpp"
    #include "opcodes/advanced/op_adv_logs_impl_l1.hpp"
    #include "opcodes/advanced/op_adv_trunc_impl_l1.hpp"
    #include "opcodes/advanced/op_adv_lerp_impl_l1.hpp"
    #include "opcodes/advanced/op_adv_vec2_f32_impl_l1.hpp"
    #include "opcodes/advanced/op_adv_complex_f32_impl_l1.hpp"
    #include "opcodes/advanced/op_adv_vec3_f32_impl_l1.hpp"

    // Implementation level 2
    #include "opcodes/advanced/op_adv_load_impl_l2.hpp"
    #include "opcodes/advanced/op_adv_store_impl_l2.hpp"
    #include "opcodes/advanced/op_adv_logic_impl_l2.hpp"
    #include "opcodes/advanced/op_adv_const_impl_l2.hpp"
    #include "opcodes/advanced/op_adv_madd_impl_l2.hpp"
    #include "opcodes/advanced/op_adv_roots_impl_l2.hpp"
    #include "opcodes/advanced/op_adv_trig_impl_l2.hpp"
    #include "opcodes/advanced/op_adv_powers_impl_l2.hpp"
    #include "opcodes/advanced/op_adv_logs_impl_l2.hpp"
    #include "opcodes/advanced/op_adv_trunc_impl_l2.hpp"
    #include "opcodes/advanced/op_adv_lerp_impl_l2.hpp"

    default:
      debuglog(LOG_ERROR, "No handler yet defined for advanced opcode 0x%04X\n", (unsigned)op);
      vm->status = VMDefs::BREAKPOINT;
      return;
  }
}

