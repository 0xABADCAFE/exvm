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

#include <cmath>

int VMCore::innerExecute() {
  int numStatements   = 0;
  register VMCore* vm = this;
  register uint16  op;

forever:
  op = *pc.inst++;
  switch (op >> 8) {
    #include "op_control_code.hpp"
    #include "op_load_code.hpp"
    #include "op_store_code.hpp"
    #include "op_move_code.hpp"
    #include "op_jump_code.hpp"
    #include "op_convert_code.hpp"
    #include "op_arithmetic_code.hpp"
    #include "op_logic_code.hpp"
    default:
      printf("No handler yet defined for opcode 0x%04X\n", (unsigned)op);
        status = VMDefs::BREAKPOINT;
        return ++numStatements;
    }
    ++numStatements;
  goto forever;

  // We can't get here, but the compiler needs to see it
  return numStatements;
}

