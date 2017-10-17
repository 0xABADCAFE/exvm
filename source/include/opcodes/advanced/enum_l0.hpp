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

#ifndef _VM_DEF_ADVANCED_OPCODES_L0_HPP_
#define _VM_DEF_ADVANCED_OPCODES_L0_HPP_

  // Implementation Level 0 : 32-bit integer only //////////////////////////////////////////////////////////////////////

  // register indirect, scale indexed
  // ld.x (rS,rI,#s), rD
  _LD_RII_8, _LD_RII_16, _LD_RII_32,

  // register indirect, scale indexed
  // st.x rS, (rD,rI,#d)
  _ST_RII_8, _ST_RII_16, _ST_RII_32,


#endif

