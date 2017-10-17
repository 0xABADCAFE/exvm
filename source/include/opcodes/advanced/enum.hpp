//****************************************************************************//
//**                                                                        **//
//** File:         opcodes/advanced/enum.hpp                                **//
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

#ifndef _VM_DEF_ADVANCED_OPCODES_HPP_
#define _VM_DEF_ADVANCED_OPCODES_HPP_

// Advanced Instruction set. These are invoked by the scalar _ADV prefix. Advanced insructions provide various extra
// functions that otherwise would require the use of native function calls to expose.

typedef enum {

  // Implementation Level 0
  #include "enum_l0.hpp"

  // Implementation Level 1
  #include "enum_l1.hpp"

  // Implementation Level 2
  #include "enum_l2.hpp"
  MAX_ADV
} AdvancedOp;


// Constants for the load constant operators
typedef enum {
  // Common multiples of PI
  CONST_PI         = 0,
  CONST_2PI        = 1,
  CONST_HALF_PI    = 2,
  CONST_INV_PI     = 3,

  // Golden ratio
  CONST_PHI        = 4,

  // Euler's Number
  CONST_E          = 4,

  // Pythagoras' Constant
  CONST_SQRT_2     = 5,
  CONST_INV_SQRT_2 = 6,

  // Theodorus' Constant
  CONST_SQRT_3     = 7,

  // Root of 5, used in several other definitions
  CONST_SQRT_5     = 8,

  // Binary natural log
  CONST_LN_2       = 9,
  CONST_INV_LN_2   = 10,

  // Misc - Universal Parabolic Constant
  CONST_UNIPB      = 11,
  MAX_CONST        = 16 // for now
} AdvancedOpConstant;

#endif

