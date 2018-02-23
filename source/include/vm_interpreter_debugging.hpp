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

#ifndef _VM_INTERPRETER_DEBUGGING_HPP_
#define _VM_INTERPRETER_DEBUGGING_HPP_


namespace ExVM {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// DebuggingInterpreter
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class DebuggingInterpreter : public Interpreter {
  friend ExVM::FunctionalTest;

  public:

    enum {
      FLAG_LOG_CALLS        = 1,
      FLAG_LOG_NATIVE_CALLS = 2,
    };

    DebuggingInterpreter(size_t rStackSize, size_t dStackSize, size_t cStackSize);
    ~DebuggingInterpreter();

    void dump();
    void execute();

  private:
    float64 totalTime;
    float64 nativeTime;
    uint64 totalStatements;
    uint32 functionCalls;
    uint32 nativeFunctionCalls;
    uint32 branchCalls;
    uint32 conditionalBranchesTaken;
    uint32 conditionalBranchesNotTaken;
    uint32 unconditionalBranches;
    uint32 debugFlags;

    uint32 scalarCount[256];
    uint32 advancedCount[256];
    uint32 vectorCount[256];

    static const char* statusCodes[];

    #define CLASS DebuggingInterpreter
    #include "vm_interpreter_opcode_funcs.hpp"
    #undef CLASS
};

}
#endif
