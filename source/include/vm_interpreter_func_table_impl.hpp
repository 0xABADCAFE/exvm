//****************************************************************************//
//**                                                                        **//
//** File:         vm_interpreter_func_table_impl.hpp                       **//
//** Description:  Host Machine definitions                                 **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2001-08-29                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):      Stub replacement for needed exng/xbase.hpp defs          **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

// simple model, no exception based return, check status after each instruction

register const Handler* h = currHandler; // temp pointer;
while (status == VMDefs::RUNNING) {
  uint16 op = *pc.inst++;
  h[(op>>8)](this, op);
  ++numStatements;
}

