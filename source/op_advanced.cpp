//****************************************************************************//
//**                                                                        **//
//** File:         op_advanced.cpp                                          **//
//** Description:  Advanced instructions                                    **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2017-09-04                                               **//
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
#include <cmath>

/**
 * Useful constants
 */
const float64 predefinedConstants[ExVM::VMDefs::MAX_CONST] = {
  3.141592653589793, //..2 238462643383279502884197169399375105820974  // CONST_PI
  6.283185307179586, //..6 476925286766559005768394338798750211641949  // CONST_2PI
  1.570796326794897, //..6 619231321691639751442098584699687552910487  // CONST_HALF_PI
  0.318309886183791, //..0 671537767526745028724068919291480912897495  // CONST_INV_PI
  1.618033988749895, //..4 848204586834365638117720309179805762862135  // CONST_PHI
  2.718281828459045, //..5 235360287471352662497757247093699959574966  // CONST_E
  1.414213562373095, //..5 048801688724209698078569671875376948073176  // CONST_SQRT_2
  0.707106781186548, //..7 524400844362104849039284835937688474036588  // CONST_INV_SQRT_2
  1.732050807568877, //..7 293527446341505872366942805253810380628055  // CONST_SQRT_3
  2.236067977499790, //..89 696409173668731276235440618359611525724270 // CONST_SQRT_5
  0.693147180559945, //..5 309417232121458176568075500134360255254120  // CONST_LN_2
  1.442695040888963, //..3 407359924681001892137426645954152985934135  // CONST_INV_LN_2
  2.295587149392638, //..3 074034298049189490387597832203638583483929  // CONST_UNIPB
};

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

void ExVM::Interpreter::doADV(ExVM::Interpreter* vm, uint16 op) {

  // The next word in the instruction stream defines up to 4 registers
  uint16 vArgs = *vm->pc.inst++;

#if _VM_INTERPRETER == _VM_INTERPRETER_FUNC_TABLE
  #include "include/vm_interpreter_adv_func_table_impl.hpp"
#elif _VM_INTERPRETER == _VM_INTERPRETER_SWITCH_CASE
  #include "include/vm_interpreter_adv_switch_case_impl.hpp"
#elif _VM_INTERPRETER == _VM_INTERPRETER_CUSTOM
  #include "include/vm_interpreter_adv_custom_impl.hpp"
#endif

}

#if _VM_INTERPRETER == _VM_INTERPRETER_FUNC_TABLE

  #undef _DEFINE_OP
  #define _DEFINE_OP(x) void ExVM::Interpreter::do##x(ExVM::Interpreter* vm UNUSED, uint16 vArgs UNUSED)

  // Implementation level 0
  #include "include/opcodes/advanced/op_adv_load_impl_l0.hpp"
  #include "include/opcodes/advanced/op_adv_store_impl_l0.hpp"
  #include "include/opcodes/advanced/op_adv_logic_impl_l0.hpp"

  // Implementation level 1
  #include "include/opcodes/advanced/op_adv_const_impl_l1.hpp"
  #include "include/opcodes/advanced/op_adv_madd_impl_l1.hpp"
  #include "include/opcodes/advanced/op_adv_roots_impl_l1.hpp"
  #include "include/opcodes/advanced/op_adv_trig_impl_l1.hpp"
  #include "include/opcodes/advanced/op_adv_powers_impl_l1.hpp"
  #include "include/opcodes/advanced/op_adv_logs_impl_l1.hpp"
  #include "include/opcodes/advanced/op_adv_trunc_impl_l1.hpp"
  #include "include/opcodes/advanced/op_adv_lerp_impl_l1.hpp"
  #include "include/opcodes/advanced/op_adv_vec3_f32_impl_l1.hpp"

  // Implementation level 2
  #include "include/opcodes/advanced/op_adv_load_impl_l2.hpp"
  #include "include/opcodes/advanced/op_adv_store_impl_l2.hpp"
  #include "include/opcodes/advanced/op_adv_logic_impl_l0.hpp"
  #include "include/opcodes/advanced/op_adv_const_impl_l2.hpp"
  #include "include/opcodes/advanced/op_adv_madd_impl_l2.hpp"
  #include "include/opcodes/advanced/op_adv_roots_impl_l2.hpp"
  #include "include/opcodes/advanced/op_adv_trig_impl_l2.hpp"
  #include "include/opcodes/advanced/op_adv_powers_impl_l2.hpp"
  #include "include/opcodes/advanced/op_adv_logs_impl_l2.hpp"
  #include "include/opcodes/advanced/op_adv_trunc_impl_l2.hpp"
  #include "include/opcodes/advanced/op_adv_lerp_impl_l2.hpp"
#endif
