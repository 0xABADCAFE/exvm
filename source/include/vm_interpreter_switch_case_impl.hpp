//****************************************************************************//
//**                                                                        **//
//** File:         vm_interpreter_switch_case.hpp                           **//
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
  register Interpreter* vm = this;
  register uint16  op;

forever:
  op = *pc.inst++;
  switch (op >> 8) {
    #include "opcodes/scalar/op_control_impl_l0.hpp"
    #include "opcodes/scalar/op_load_impl_l0.hpp"
    #include "opcodes/scalar/op_store_impl_l0.hpp"
    #include "opcodes/scalar/op_move_impl_l0.hpp"
    #include "opcodes/scalar/op_jump_impl_l0.hpp"
    #include "opcodes/scalar/op_convert_impl_l0.hpp"
    #include "opcodes/scalar/op_arithmetic_impl_l0.hpp"
    #include "opcodes/scalar/op_logic_impl_l0.hpp"

    #include "opcodes/scalar/op_jump_impl_l1.hpp"
    #include "opcodes/scalar/op_convert_impl_l1.hpp"
    #include "opcodes/scalar/op_arithmetic_impl_l1.hpp"

    #include "opcodes/scalar/op_load_impl_l2.hpp"
    #include "opcodes/scalar/op_store_impl_l2.hpp"
    #include "opcodes/scalar/op_move_impl_l2.hpp"
    #include "opcodes/scalar/op_jump_impl_l2.hpp"
    #include "opcodes/scalar/op_convert_impl_l2.hpp"
    #include "opcodes/scalar/op_arithmetic_impl_l2.hpp"
    #include "opcodes/scalar/op_logic_impl_l2.hpp"

    _DEFINE_OP(ADV) {
      doADV(vm, op);
      if (vm->status != VMDefs::RUNNING) {
        _HALT
      }
    }
    _END_OP

    _DEFINE_OP(VEC1) {
      doVEC1(vm, op);
      if (vm->status != VMDefs::RUNNING) {
        _HALT
      }
    }
    _END_OP

    default:
      debuglog(LOG_ERROR, "No handler yet defined for opcode 0x%04X\n", (unsigned)op);
        status = VMDefs::ILLEGAL_OPCODE;
        _HALT
    }
    ++numStatements;
  goto forever;

interpreter_bailout:
  ++numStatements; // include the statement last executed that led here

  // If the status indicates we had an exception, check if there is a handler.
  // If the handler can recover from the exception, it will set the status back to RUNNING.
  if (
    vm->status >= VMDefs::BREAKPOINT &&
    vm->status < VMDefs::_MAX_VMSTATUS
  ) {
    uint32 handlerID = vm->status - VMDefs::BREAKPOINT;
    if (vm->hostExceptionHandlers[handlerID]) {
      vm->hostExceptionHandlers[handlerID](vm);
      if (vm->status == VMDefs::RUNNING) {
        goto forever;
      }
    }
  }

}

