//****************************************************************************//
//**                                                                        **//
//** File:         opcodes/vector/enum.hpp                                  **//
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

#ifndef _VM_DEF_VECTOR_OPCODES_HPP_
#define _VM_DEF_VECTOR_OPCODES_HPP_

// Vector Instruction set. These are invoked by the scalar _VEC prefix. Vector instructions perform block operations
// directly on memory regions indicated by the addresses in the scalar registers. This is endian safe since all the
// vector operations affect every element in the set.

// While the intention is that these instructions should make use of host native vector units and memory streaming
// they can be implemented in a purely scalar fashion on machines without any such hardware. In these cases it is
// expected that vector calls will still significantly outperform any non vector implementation in virtual code as a
// direct consequence of the elimiation of the interpretation overhead.

typedef enum {

  // Implementation Level 0
  #include "enum_l0.hpp"

  // Implementation Level 1
  #include "enum_l1.hpp"

  // Implementation Level 2
  #include "enum_l2.hpp"

  MAX_VEC
} VectorOp;

#endif

