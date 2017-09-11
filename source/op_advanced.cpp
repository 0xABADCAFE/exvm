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

const float64 INV_LN_2 = 1.44269504089;

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

  #include "include/opcodes/advanced/op_adv_const_impl.hpp"
  #include "include/opcodes/advanced/op_adv_roots_impl.hpp"
  #include "include/opcodes/advanced/op_adv_trig_impl.hpp"
  #include "include/opcodes/advanced/op_adv_powers_impl.hpp"
  #include "include/opcodes/advanced/op_adv_logs_impl.hpp"
  #include "include/opcodes/advanced/op_adv_trunc_impl.hpp"
  #include "include/opcodes/advanced/op_adv_lerp_impl.hpp"

#endif
