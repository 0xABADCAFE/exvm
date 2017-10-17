//****************************************************************************//
//**                                                                        **//
//** File:         opcodes/scalar/enum.hpp                                  **//
//** Description:  Virtual Machine definitions                              **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2001-08-14                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

#ifndef _VM_DEF_SCALAR_OPCODES_HPP_
#define _VM_DEF_SCALAR_OPCODES_HPP_

typedef enum {

  // Implementation Level 0
  #include "enum_l0.hpp"

  // Implementation Level 1
  #include "enum_l1.hpp"

  // Implementation Level 2
  #include "enum_l2.hpp"

  // Prefixes //////////////////////////////////////////////////////////////////////////////////////////////////////////

  // Advanced operations (transcendal arithmetic etc)
  _ADV,

  // Streaming Vector operations (array primitives)
  _VEC1,

  MAX_OP
} NormalOp;

#endif

