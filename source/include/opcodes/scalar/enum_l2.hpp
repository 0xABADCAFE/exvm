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

#ifndef _VM_DEF_SCALAR_OPCODES_L2_HPP_
#define _VM_DEF_SCALAR_OPCODES_L2_HPP_

  // immediate 16-bit integer literal, -32768 to 32767
  // allowed for 8/16-bit destination operands,
  // values outside the 8-bit range are truncated for 8-bit.
  //
  // ld.i #n, rX
  // [opcode] [0 : rX]
  // [ literal data  ]
  _LD_16_I64,

  // immediate 32-bit literal, can be 32-bit integer or floating point.
  // allowed for 32/64-bit destination operands.
  //
  // ld.x #n, rX
  // [opcode] [0 : rX]
  // [ literal data  ]
  // [ literal data  ]
  _LD_32_I64, _LD_32_F64,

  // register indirect
  // ld.x (rS), rD
  // [opcode] [rS : rD]
  _LD_RI_64,

  // register indirect post increment
  // ld.x (rS)+, rD
  // [opcode] [rS : rD]
  _LD_RIPI_64,

  // register indirect pre decrement
  // ld.x -(rS), rD
  // [opcode] [rS : rD]
  _LD_RIPD_64,

  // register indirect with displacement
  // ld.x (rS,#d), rD
  // [opcode] [rS : rD]
  // [ displacement16 ]
  _LD_RID_64,

  // load global reference
  // ld.x label,rX
  // [opcode] [ Data Symbol ID {16:19} : rX ]
  // [          Data Symbol ID {0:15}       ]
  _LD_64,

  // store group ////////////////////////////////////////

  // register indirect
  // st.x rS, (rD)
  // [opcode] [rS : rD]
  _ST_RI_64,

  // register indirect post increment
  // st.x rS, (rD)+
  // [opcode] [rS : rD]
  _ST_RIPI_64,

  // register indirect pre decrement
  // st.x rS, -(rD)
  // [opcode] [rS : rD]
  _ST_RIPD_64,

  // register indirect with displacement
  // st.x rS, (rD,#d)
  // [opcode] [rS : rD]
  // [ displacement16 ]
  _ST_RID_64,

  // store global reference
  // st.x rX,label
  // [opcode] [ Data Symbol ID {16:19} : rX ]
  // [          Data Symbol ID {0:15}       ]
  _ST_64,

  // move group /////////////////////////////////////////

  // mv.x rS,rD
  _MV_64,

  // bswp.x rS,rD
  _BSWP_64,

  // push / pop group ///////////////////////////////////

  // Push values from register(s) to data stack
  // push.x rA,rB,rC...
  // [opcode] [0 : 0]
  // [#register mask]
  _PUSH_64,

  // Pop values from stack to register(s)
  // pop.x rA,rB,rC...
  // [opcode] [0 : 0]
  // [#register mask]
  _POP_64,

  // jump/branch group //////////////////////////////////
  // conditional branches - max 16-bit pc relative displacement
  // [opcode] [rS : rD]
  // [ displacement16 ]
  // pc relative

  _BNZ_64,

  // beq.x rS,rD,label
  // branch taken if rS == rD
  _BEQ_64,
  _BEQ_F64,

  // bgreq.x rS,rD,label
  // branch taken if rS => rD
  _BGREQ_64,
  _BGREQ_F64,

  // bgr.x rS,rD,label
  // branch taken if rS > rD
  _BGR_64,
  _BGR_F64,

  // cast group /////////////////////////////////////////

  // widening

  // signed extension, signed to float
  _S8_2_S64,
  _S8_2_F64,
  _S16_2_S64,
  _S16_2_F64,
  _S32_2_S64,
  _S32_2_F64,
  _S64_2_F32,
  _S64_2_F64,

  // unsigned to float
  // unsigned extension must be implemented in virtual code
  _U8_2_F64,
  _U16_2_F64,
  _U32_2_F64,
  _U64_2_F32,
  _U64_2_F64,

  // float to double
  _F32_2_F64,

  // narrowing, double to float / float to signed
  // double/float to unsigned must be implemented in virtual code
  _F64_2_F32,
  _F64_2_S64,
  _F64_2_S32,
  _F64_2_S16,
  _F64_2_S8,
  _F32_2_S64,

  // Arithmetic commands, data treat as signed integer / float
  // add.x rS,rD (rD += rS)
  _ADD_I64,
  _ADD_F64,

  // sub.x rS,rD (rD -= rS)
  _SUB_I64,
  _SUB_F64,

  // mul.x rS,rD (rD *= rS)
  _MUL_U64,
  _MUL_S64,
  _MUL_F64,

  // div.x rS,rD (rD /= rS)
  _DIV_U64,
  _DIV_S64,
  _DIV_F64,

  // mod.x rS,rD (rD %= rS)
  _MOD_U64,
  _MOD_S64,
  _MOD_F64,

  // neg.x rS,rD (rD = -rS)
  _NEG_S64,
  _NEG_F64,

  // asr.x rS,rD (rD >>= rS) - arithmetic, preserves sign
  _ASR_S64,

  // min.x rS,RD
  _MIN_S64,
  _MIN_F64,

  _MAX_S64,
  _MAX_F64,

  // Logic commands, data treat as unsigned binary

  // and.x rS,RD (rD &= rS)
  _AND_64,

  // or.x rS,RD (rD |= rS)
  _OR_64,

  // xor.x rS,RD (rD ^= rS)
  _XOR_64,

  // inv.x rS,RD (rD = ~rS)
  _INV_64,

  // lsl.x rS,rD (rD <<= rS) - logical
  _LSL_64,

  // lsr.x rS,rD (rD >>= rS) - logical
  _LSR_64,

  // rol.x rS,rD (rD <@= rS) - rotate left
  _ROL_64,

  // ror.x rS,rD (rD @>= rS) - rotate right
  _ROR_64,

#endif

