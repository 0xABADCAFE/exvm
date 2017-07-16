//****************************************************************************//
//**                                                                        **//
//** File:         vm_interpreter_switch_case.hpp                           **//
//** Description:  VMCore class definition                                  **//
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
  register VMCore* vm = this;
  register uint16  op;

forever:
  op = *pc.inst++;
  switch (op >> 8) {
    #include "op_control_impl.hpp"
    #include "op_load_impl.hpp"
    #include "op_store_impl.hpp"
    #include "op_move_impl.hpp"
    #include "op_jump_impl.hpp"
    #include "op_convert_impl.hpp"
    #include "op_arithmetic_impl.hpp"
    #include "op_logic_impl.hpp"
    default:
      printf("No handler yet defined for opcode 0x%04X\n", (unsigned)op);
        status = VMDefs::BREAKPOINT;
        goto interpreter_bailout;
    }
    ++numStatements;
  goto forever;

interpreter_bailout:
  ++numStatements; // include the statement last executed that led here
}
