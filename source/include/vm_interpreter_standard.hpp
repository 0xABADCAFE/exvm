//****************************************************************************//
//**                                                                        **//
//** File:         vm_core.hpp                                              **//
//** Description:  Virtual Machine Core definitions                         **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2001-08-29                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

#ifndef _VM_INTERPRETER_STANDARD_HPP_
#define _VM_INTERPRETER_STANDARD_HPP_

namespace ExVM {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// StandardInterpreter
//
// Represents the core interpreter for the virtual machine and is primarily responsible for the runtime execution of
// virtual code.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class StandardInterpreter : public Interpreter {

  friend class ExVM::FunctionalTest;

  public:
    StandardInterpreter(size_t rStackSize, size_t dStackSize, size_t cStackSize);
    ~StandardInterpreter();

    void dump();
    void execute();

  private:
    #define CLASS StandardInterpreter
    #include "vm_interpreter_opcode_funcs.hpp"
    #undef CLASS
};

}
#endif
