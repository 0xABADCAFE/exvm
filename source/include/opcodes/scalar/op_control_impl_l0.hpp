//****************************************************************************//
//**                                                                        **//
//** File:         op_control_code.hpp                                      **//
//** Description:  Control group opcode implementation                      **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2001-09-02                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

_DEFINE_OP(NOP) {

}
_END_OP

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

_DEFINE_OP(BRK) {
  vm->status = VMDefs::BREAKPOINT;
  vm->exceptionOffset = EXC_OFFSET_STD;
  _HALT
}
_END_OP
