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

    default:
      debuglog(LOG_ERROR, "No handler yet defined for opcode 0x%04X\n", (unsigned)op);
      vm->status = VMDefs::BREAKPOINT;
      return;
  }
}

