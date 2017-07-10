//****************************************************************************//
//**                                                                        **//
//** File:         vm_interpreter_custom_amiga_68k_impl.hpp                 **//
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

// set up CPU trap handling, written in asm
Task* thisTask         = FindTask(0);
void* old68KTrap       = thisTask->tc_TrapCode;
thisTask->tc_TrapCode  = (void*)(&trap_68K);

// jump into the asm execute code
asm(
  "\n/*************************************/\n\n"
  "\tmove.l %0, a0\n"
  "\tjsr _execute_68K\n"
  "\n/*************************************/\n\n"
  :                                 // no outputs
  : "g"(this)                       // inputs
  : "d0", "d1", "a0", "a1","cc"     // clobbers
);

// reset the trap code to whatever it was previously
thisTask->tc_TrapCode = old68KTrap;

