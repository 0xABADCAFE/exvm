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
    default:
      printf("No vector handler yet defined for opcode 0x%04X\n", (unsigned)op);
      vm->status = VMDefs::BREAKPOINT;
      return;
  }
}

