//****************************************************************************//
//**                                                                        **//
//** File:         vm.hpp                                                   **//
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

#ifndef _VM_DEF_OPCODES_HPP_
#define _VM_DEF_OPCODES_HPP_

// Standard instruction set, basic scalar operations.

typedef enum {
// TODO: Reorganise based on sizeless, 32-bit int only, 32-bit int+float, 64-bit contiguous blocks

  // control group ////////////////////////////////////////
  _NOP = 0,
  _BRK,

  // load group ///////////////////////////////////////////

  // immediate small literal, 0-15
  // ldq #n, rX
  // [opcode] [#n : rX]
  _LDQ,

  // immediate 16-bit literal, -32768 to 32767
  // allowed for 8/16-bit destination operands,
  // values outside the 8-bit range are truncated for 8-bit.
  //
  // ld.i #n, rX
  // [opcode] [0 : rX]
  // [ literal data  ]
  _LD_I16_8, _LD_I16_16, _LD_I16_32, _LD_I16_64,

  // immediate 32-bit literal
  // allowed for 32/64-bit desination operands
  // object file stores MSW first, after loading, convert
  // all 32-bit immediate data to endian native represntation
  // during resolution stage.
  //
  // ld.i #n, rX
  // [opcode] [0 : rX]
  // [ literal data  ]
  // [ literal data  ]
  _LD_I32_32, _LD_I32_64,

  // immediate 32-bit literal float
  // allowed for 32/64-bit desination operands
  // object file stores MSW first, after loading, convert
  // all 32-bit immediate data to endian native represntation
  // during resolution stage.
  //
  // ld.f32 #123.123, rX
  // [opcode] [0 : rX]
  // [ literal data  ]
  // [ literal data  ]
  _LD_F32,

  // register indirect
  // ld.x (rS), rD
  // [opcode] [rS : rD]
  _LD_RI_8, _LD_RI_16, _LD_RI_32, _LD_RI_64,

  // register indirect post increment
  // ld.x (rS)+, rD
  // [opcode] [rS : rD]
  _LD_RIPI_8, _LD_RIPI_16, _LD_RIPI_32, _LD_RIPI_64,

  // register indirect pre decrement
  // ld.x -(rS), rD
  // [opcode] [rS : rD]
  _LD_RIPD_8, _LD_RIPD_16, _LD_RIPD_32, _LD_RIPD_64,

  // register indirect with displacement
  // ld.x (rS,#d), rD
  // [opcode] [rS : rD]
  // [ displacement16 ]
  _LD_RID_8,  _LD_RID_16, _LD_RID_32, _LD_RID_64,

  // register indirect, scale indexed
  // ld.x (rS,rI,#s), rD
  // [opcode] [rS : rD]
  // [#scale] [ 0 : rI]
  _LD_RII_8, _LD_RII_16, _LD_RII_32, _LD_RII_64,

  // load global reference
  // ld.x label,rX
  // [opcode] [ Data Symbol ID {16:19} : rX ]
  // [          Data Symbol ID {0:15}       ]

  _LD_8, _LD_16, _LD_32, _LD_64,

  // loads the address implied by the symbol ID into the specified address reguster:
  // lda label, rX
  // [opcode] [ Data Symbol ID {16:19} : rX ]
  // [          Data Symbol ID {0:15}       ]

  _LD_ADDR,

  // store group ////////////////////////////////////////

  // register indirect
  // st.x rS, (rD)
  // [opcode] [rS : rD]
  _ST_RI_8, _ST_RI_16, _ST_RI_32, _ST_RI_64,

  // register indirect post increment
  // st.x rS, (rD)+
  // [opcode] [rS : rD]
  _ST_RIPI_8, _ST_RIPI_16, _ST_RIPI_32, _ST_RIPI_64,

  // register indirect pre decrement
  // st.x rS, -(rD)
  // [opcode] [rS : rD]
  _ST_RIPD_8, _ST_RIPD_16, _ST_RIPD_32, _ST_RIPD_64,

  // register indirect with displacement
  // st.x rS, (rD,#d)
  // [opcode] [rS : rD]
  // [ displacement16 ]
  _ST_RID_8, _ST_RID_16, _ST_RID_32, _ST_RID_64,

  // register indirect, scale indexed
  // st.x rS, (rD,rI,#d)
  // [opcode] [rS : rD]
  // [#scale] [ 0 : rI]
  _ST_RII_8, _ST_RII_16, _ST_RII_32, _ST_RII_64,

  // store global reference
  // st.x rX,label
  // [opcode] [ Data Symbol ID {16:19} : rX ]
  // [          Data Symbol ID {0:15}       ]

  _ST_8, _ST_16, _ST_32, _ST_64,

  // move group /////////////////////////////////////////

  // mv.x rS,rD
  _MV_8, _MV_16, _MV_32, _MV_64,

  // bswp.x rS,rD
  _BSWP_16, _BSWP_32, _BSWP_64,

  // exg rS,rD
  _EXG,

  // push / pop group ///////////////////////////////////

  // save multiple regs to register stack, save/restore rF, rL
  // [opcode] [rF : rL]
  _SV, _RS,

  // [opcode] [rF : rL]
  // push.x rF,rL
  _PUSH_8, _PUSH_16, _PUSH_32, _PUSH_64,

  // pop.x rF,rL
  _POP_8, _POP_16, _POP_32, _POP_64,

  // jump/branch group //////////////////////////////////

  // Branch call. Call a PC relative displacement as a function.
  _BCALL8,
  _BCALL16,

  // call global reference
  // call label
  // [opcode] [ Code Symbol ID{16:24} ]
  // [          Code Symbol ID{0-15}  ]

  _CALL, _CALLN, _RET,

  // unconditional branches, max 16-bit pc relative displacement
  // bra(.8) label
  // [opcode] [ displacement8 ]
  // bra(.16) label
  // [opcode] [     0 ]
  // [ displacement16 ]
  // pc relative
  // assembler should resolve .8/.16 automatically
  _BRA8, _BRA16,

  // computed branch via an inline jump table. Each entry in the table is
  // a 16-bit signed offset from the PC following the opcode (just like
  // normal branches).
  // case(.16) rX
  // [opcode] [ 0 : rX ]
  // [   table size    ]
  // [ displacement  0 ]
  // [ displacement  1 ]
  // ...................
  // [ displacement  n ]
  _CASE,

  // conditional branches - max 16-bit pc relative displacement
  // [opcode] [rS : rD]
  // [ displacement16 ]
  // pc relative

  _BNZ_8, _BNZ_16, _BNZ_32, _BNZ_64,

  // beq.x rS,rD,label
  // branch taken if rS == rD
  _BEQ_8,   _BEQ_16,    _BEQ_32,    _BEQ_64,    _BEQ_F32,   _BEQ_F64,

  // bgreq.x rS,rD,label
  // branch taken if rS => rD
  _BGREQ_8, _BGREQ_16,  _BGREQ_32,  _BGREQ_64,  _BGREQ_F32, _BGREQ_F64,

  // bgr.x rS,rD,label
  // branch taken if rS > rD
  _BGR_8,   _BGR_16,    _BGR_32,    _BGR_64,    _BGR_F32,   _BGR_F64,

  // cast group /////////////////////////////////////////

  // widening

  // signed extension, signed to float
  _S8_2_S16,  _S8_2_S32,  _S8_2_S64,  _S8_2_F32,  _S8_2_F64,
  _S16_2_S32, _S16_2_S64, _S16_2_F32, _S16_2_F64,
  _S32_2_S64, _S32_2_F32, _S32_2_F64,
  _S64_2_F32, _S64_2_F64,

  // unsigned to float
  // unsigned extension must be implemented in virtual code
  _U8_2_F32,  _U8_2_F64,
  _U16_2_F32, _U16_2_F64,
  _U32_2_F32, _U32_2_F64,
  _U64_2_F32, _U64_2_F64,

  // float to double
  _F32_2_F64,

  // narrowing, double to float / float to signed
  // double/float to unsigned must be implemented in virtual code
  _F64_2_F32, _F64_2_S64, _F64_2_S32, _F64_2_S16, _F64_2_S8,
  _F32_2_S64, _F32_2_S32, _F32_2_S16, _F32_2_S8,

  // Arithmetic commands, data treat as signed integer / float
  // add.x rS,rD (rD += rS)
  _ADD_I8,  _ADD_I16, _ADD_I32, _ADD_I64,
  _ADD_F32, _ADD_F64,

  // add immediate
  _ADDI_I8, _ADDI_I16, _ADDI_I32,

  // sub.x rS,rD (rD -= rS)
  _SUB_I8,  _SUB_I16, _SUB_I32, _SUB_I64,
  _SUB_F32, _SUB_F64,

  // mul.x rS,rD (rD *= rS)
  _MUL_U8,  _MUL_U16, _MUL_U32, _MUL_U64,
  _MUL_S8,  _MUL_S16, _MUL_S32, _MUL_S64,
  _MUL_F32, _MUL_F64,

  // div.x rS,rD (rD /= rS)
  _DIV_U8,  _DIV_U16, _DIV_U32, _DIV_U64,
  _DIV_S8,  _DIV_S16, _DIV_S32, _DIV_S64,
  _DIV_F32, _DIV_F64,

  // mod.x rS,rD (rD %= rS)
  _MOD_U8,  _MOD_U16,  _MOD_U32, _MOD_U64,
  _MOD_S8,  _MOD_S16,  _MOD_S32, _MOD_S64,
  _MOD_F32, _MOD_F64,

  // neg.x rS,rD (rD = -rS)
  _NEG_S8,  _NEG_S16, _NEG_S32, _NEG_S64,
  _NEG_F32, _NEG_F64,

  // asr.x rS,rD (rD >>= rS) - arithmetic, preserves sign
  _ASR_S8,  _ASR_S16, _ASR_S32, _ASR_S64,

  // min.x rS,RD
  _MIN_S8,  _MIN_S16, _MIN_S32, _MIN_S64,
  _MIN_F32, _MIN_F64,

  _MAX_S8,  _MAX_S16, _MAX_S32, _MAX_S64,
  _MAX_F32, _MAX_F64,

  // madd.f32|f64 rS,rD,rM,rA
  // rD = rS*rM + rA
  // [ opcode ][rS : rD]
  // [ 0 : rM ][ 0 : rA]
  _MUL_ADD_F32, _MUL_ADD_F64,

  // Logic commands, data treat as unsigned binary

  // and.x rS,RD (rD &= rS)
  _AND_8,  _AND_16, _AND_32, _AND_64,

  // or.x rS,RD (rD |= rS)
  _OR_8, _OR_16, _OR_32, _OR_64,

  // xor.x rS,RD (rD ^= rS)
  _XOR_8, _XOR_16, _XOR_32, _XOR_64,

  // inv.x rS,RD (rD = ~rS)
  _INV_8, _INV_16, _INV_32, _INV_64,

  // lsl.x rS,rD (rD <<= rS) - logical
  _LSL_8, _LSL_16, _LSL_32, _LSL_64,

  // lsr.x rS,rD (rD >>= rS) - logical
  _LSR_8, _LSR_16, _LSR_32, _LSR_64,

  // rol.x rS,rD (rD <@= rS) - rotate left
  _ROL_8, _ROL_16, _ROL_32, _ROL_64,

  // ror.x rS,rD (rD @>= rS) - rotate right
  _ROR_8, _ROR_16, _ROR_32, _ROR_64,

  // prefixes
  _VEC1,

  MAX_OP
} NormalOp;


// Vector Instruction set. These are invoked by the scalar _VEC prefix. Vector instructions perform block operations
// directly on memory regions indicated by the addresses in the scalar registers. This is endian safe since all the
// vector operations affect every element in the set.

// While the intention is that these instructions should make use of host native vector units and memory streaming
// they can be implemented in a purely scalar fashion on machines without any such hardware. In these cases it is
// expected that vector calls will still significantly outperform any non vector implementation in virtual code as a
// direct consequence of the elimiation of the interpretation overhead.

typedef enum {

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //
  // Single Vector functions (vector is destination only)
  //
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // Scalar to Vector Fill
  //
  // vd[i] = x

  _VFILL_8,  _VFILL_16,  _VFILL_32,  _VFILL_64, // op_vec_fill_impl.hpp

  // Scalar minimum in vector
  _VSMIN_U8, _VSMIN_U16, _VSMIN_U32, _VSMIN_U64, // op_vec_smin_impl.hpp
  _VSMIN_S8, _VSMIN_S16, _VSMIN_S32, _VSMIN_S64,
  _VSMIN_F32,_VSMIN_F64,

  // Scalar maximum in vector
  _VSMAX_U8, _VSMAX_U16, _VSMAX_U32, _VSMAX_U64, // op_vec_smax_impl.hpp
  _VSMAX_S8, _VSMAX_S16, _VSMAX_S32, _VSMAX_S64,
  _VSMAX_F32,_VSMAX_F64,

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //
  // Two Vector functions (one vector source, one vector destination)
  //
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // Vector negate (integer)
  //
  // vd[i] = -vs[i]

  _VNEG_S8,  _VNEG_S16,  _VNEG_S32,  _VNEG_S64, // op_vec_neg_impl.hpp

  // Vector negate (flaot)
  //
  // vd[i] = -vs[i]

  _VNEG_F32, _VNEG_F64, // op_vec_neg_impl.hpp

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // Vector absolute (signed integer)
  //
  // vd[i] = |vs[i]|

  _VABS_S8,  _VABS_S16,  _VABS_S32,  _VABS_S64, // op_vec_abs_impl.hpp

  // Vector absolute (float)
  //
  // vd[i] = abs(vs[i])

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  _VABS_F32, _VABS_F64, // op_vec_abs_impl.hpp

  // Vector inverse (int)
  //
  // vd[i] = ~vs[i]

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  _VINV_8, // op_vec_inv_impl.hpp

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // Scalar on Vector addition (integer)
  //
  // vd[i] = vs[i] + x

  _VSADD_I8,  _VSADD_I16,  _VSADD_I32,  _VSADD_I64, // op_vec_sadd_impl.hpp

  // Scalar on Vector addition (float)
  //
  // vd[i] = vs[i] + x

  _VSADD_F32, _VSADD_F64, // op_vec_sadd_impl.hpp

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // Scalar on Vector addition (unsigned integer, saturated)
  //
  // vd[i] = vs[i] + x

  _VSADDS_U8, _VSADDS_U16, _VSADDS_U32, _VSADDS_U64, // op_vec_sadd_saturated_impl.hpp

  // Scalar on Vector addition (signed integer, saturated)
  //
  // vd[i] = vs[i] + x

  _VSADDS_S8, _VSADDS_S16, _VSADDS_S32, _VSADDS_S64, // op_vec_sadd_saturated_impl.hpp

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // Scalar on Vector subtraction (integer)
  //
  // vd[i] = vs[i] + x

  _VSSUB_I8,  _VSSUB_I16,  _VSSUB_I32,  _VSSUB_I64, // op_vec_ssub_impl.hpp

  // Scalar on Vector subtraction (float)
  //
  // vd[i] = vs[i] + x

  _VSSUB_F32, _VSSUB_F64, // op_vec_ssub_impl.hpp

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // Scalar on Vector subtraction (unsigned integer, saturated)
  //
  // vd[i] = vs[i] - x

  _VSSUBS_U8, _VSSUBS_U16, _VSSUBS_U32, _VSSUBS_U64, // op_vec_ssub_saturated_impl.hpp

  // Scalar on Vector subtraction (signed integer, saturated)
  //
  // vd[i] = vs[i] - x

  _VSSUBS_S8, _VSSUBS_S16, _VSSUBS_S32, _VSSUBS_S64, // op_vec_ssub_saturated_impl.hpp

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // Scalar Scalar Vector multiply (unsigned integer)
  //
  // vd[i] = vs[i] * x

  _VSMUL_U8,  _VSMUL_U16,  _VSMUL_U32,  _VSMUL_U64, // op_vec_smul_impl.hpp

  // Scalar on Vector multiply (signed integer)
  //
  // vd[i] = vs[i] * x

  _VSMUL_S8,  _VSMUL_S16,  _VSMUL_S32,  _VSMUL_S64, // op_vec_smul_impl.hpp

  // Scalar on Vector multiply (float)
  //
  // vd[i] = vs[i] * x

  _VSMUL_F32, _VSMUL_F64, // op_vec_smul_impl.hpp

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // Scalar on Vector multiply (unsigned integer, saturated)
  //
  // vd[i] = vs[i] * x

  _VSMULS_U8, _VSMULS_U16, _VSMULS_U32, _VSMULS_U64, // op_vec_smul_saturated_impl.hpp

  // Scalar on Vector multiply (signed integer, saturated)
  //
  // vd[i] = vs[i] * x

  _VSMULS_S8, _VSMULS_S16, _VSMULS_S32, _VSMULS_S64, // op_vec_smul_saturated_impl.hpp

  // Scalar on Vector division (unsigned integer)
  //
  // vd[i] = vs[i] / x

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  _VSDIV_U8,  _VSDIV_U16,  _VSDIV_U32,  _VSDIV_U64, // op_vec_sdiv_impl.hpp

  // Scalar on Vector division (signed integer)
  //
  // vd[i] = vs[i] / x

  _VSDIV_S8,  _VSDIV_S16,  _VSDIV_S32,  _VSDIV_S64, // op_vec_sdiv_impl.hpp

  // Scalar on Vector division (float)
  //
  // vd[i] = vs[i] / x

  _VSDIV_F32, _VSDIV_F64, // op_vec_sdiv_impl.hpp

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // No saturating unsigned division as it can never overflow.

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // Scalar on Vector division (signed integer, saturated)
  //
  // vd[i] = vs[i] / x

  _VSDIVS_S8, _VSDIVS_S16, _VSDIVS_S32, _VSDIVS_S64, // op_vec_sdiv_saturated_impl.hpp

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // Scalar on Vector modulus (unsigned integer)
  //
  // vd[i] = vs[i] % x

  _VSMOD_U8,  _VSMOD_U16,  _VSMOD_U32,  _VSMOD_U64, // op_vec_smod_impl.hpp

  // Scalar on Vector modulus (signed integer)
  //
  // vd[i] = vs[i] % x

  _VSMOD_S8,  _VSMOD_S16,  _VSMOD_S32,  _VSMOD_S64, // op_vec_smod_impl.hpp

  // Scalar on Vector modulus (float)
  //
  // vd[i] = vs[i] % x

  _VSMOD_F32, _VSMOD_F64, // op_vec_smod_impl.hpp

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // No saturating modulus.

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // Scalar on Vector bitwise AND
  //
  // vd[i] = vs[i] & x
  _VSAND_8,   _VSAND_16,   _VSAND_32,   _VSAND_64, // op_vec_sand_impl.hpp

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // Scalar on Vector bitwise OR
  //
  // vd[i] = vs[i] | x
  _VSOR_8,    _VSOR_16,    _VSOR_32,    _VSOR_64, // op_vec_sor_impl.hpp

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // Scalar on Vector XOR
  //
  // vd[i] = vs[i] ^ x
  _VSXOR_8,   _VSXOR_16,   _VSXOR_32,   _VSXOR_64, // op_vec_sxor_impl.hpp

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // Scalar on Vector logical shift left
  //
  // vd[i] = vs[i] << x

  _VSLSL_8,   _VSLSL_16,   _VSLSL_32,   _VSLSL_64, // op_vec_slsl_impl.hpp

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // Scalar on Vector logical shift right
  //
  // vd[i] = vs[i] >> x

  _VSLSR_8,   _VSLSR_16,   _VSLSR_32,   _VSLSR_64, // op_vec_slsr_impl.hpp

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // Scalar on Vector arithmetic shift left
  //
  // vd[i] = vs[i] << x

  _VSASL_8,   _VSASL_16,   _VSASL_32,   _VSASL_64, // op_vec_sasl_impl.hpp

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // Scalar on Vector arithmetic shift right
  //
  // vd[i] = vs[i] >> x

  _VSASR_8,   _VSASR_16,   _VSASR_32,   _VSASR_64, // op_vec_sasr_impl.hpp

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // Scalar on Vector rotate left
  //
  // vd[i] = vs[i] <<@ x

  _VSROL_8,   _VSROL_16,   _VSROL_32,   _VSROL_64, // op_vec_srol_impl.hpp

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // Scalar on Vector rotate right
  //
  // vd[i] = vs[i] @>> x

  _VSROR_8,   _VSROR_16,   _VSROR_32,   _VSROR_64, // op_vec_sror_impl.hpp

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //
  // Three vector functions (two vector sources, one vector destination)
  //
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // Vector addition (integer)
  //
  // vd[i] = va[i] + vb[i]

  _VADD_I8,  _VADD_I16,  _VADD_I32,  _VADD_I64, // op_vec_vadd_impl.hpp

  // Vector addition (float)
  //
  // vd[i] = va[i] + vb[i]

  _VADD_F32, _VADD_F64, // op_vec_vadd_impl.hpp

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // Vector addition (unsigned integer, saturated)
  //
  // vd[i] = va[i] + vb[i]

  _VADDS_U8, _VADDS_U16, _VADDS_U32, _VADDS_U64, // op_vec_vadd_saturated_impl.hpp

  // Vector addition (signed integer, saturated)
  //
  // vd[i] = va[i] + vb[i]

  _VADDS_S8, _VADDS_S16, _VADDS_S32, _VADDS_S64, // op_vec_vadd_saturated_impl.hpp

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // Vector subtraction (integer)
  //
  // vd[i] = va[i] - vb[i]

  _VSUB_I8,  _VSUB_I16,  _VSUB_I32,  _VSUB_I64, // op_vec_vsub_impl.hpp

  // Vector subtraction (float)
  //
  // vd[i] = va[i] - vb[i]

  _VSUB_F32, _VSUB_F64, // op_vec_vsub_impl.hpp

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // Vector subtraction (unsigned integer, saturated)
  //
  // vd[i] = va[i] - vb[i]

  _VSUBS_U8, _VSUBS_U16, _VSUBS_U32, _VSUBS_U64, // op_vec_vsub_saturated_impl.hpp

  // Vector subtraction (signed integer, saturated)
  //
  // vd[i] = va[i] - vb[i]

  _VSUBS_S8, _VSUBS_S16, _VSUBS_S32, _VSUBS_S64, // op_vec_vsub_saturated_impl.hpp

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // Vector multiply (unsigned integer)
  //
  // vd[i] = va[i] * vb[i]

  _VMUL_U8,  _VMUL_U16,  _VMUL_U32,  _VMUL_U64, // op_vec_vmul_impl.hpp

  // Vector multiply (signed integer)
  //
  // vd[i] = va[i] * vb[i]

  _VMUL_S8,  _VMUL_S16,  _VMUL_S32,  _VMUL_S64, // op_vec_vmul_impl.hpp

  // Vector multiply (float)
  //
  // vd[i] = va[i] * vb[i]

  _VMUL_F32, _VMUL_F64, // op_vec_vmul_impl.hpp

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // Vector multiply (unsigned integer, saturated)
  //
  // vd[i] = va[i] * vb[i]

  _VMULS_U8, _VMULS_U16, _VMULS_U32, _VMULS_U64, // op_vec_vmul_saturated_impl.hpp

  // Vector multiply (signed integer, saturated)
  //
  // vd[i] = va[i] * vb[i]

  _VMULS_S8, _VMULS_S16, _VMULS_S32, _VMULS_S64, // op_vec_vmul_saturated_impl.hpp

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // Vector division (unsigned integer)
  //
  // vd[i] = va[i] / vb[i]

  _VDIV_U8,  _VDIV_U16,  _VDIV_U32,  _VDIV_U64, // op_vec_vdiv_impl.hpp

  // Vector division (signed integer)
  //
  // vd[i] = va[i] / vb[i]

  _VDIV_S8,  _VDIV_S16,  _VDIV_S32,  _VDIV_S64, // op_vec_vdiv_impl.hpp

  // Vector division (float)
  //
  // vd[i] = va[i] / vb[i]

  _VDIV_F32, _VDIV_F64, // op_vec_vdiv_impl.hpp

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // No unsigned saturating vector division

  // Vector division (signed integer, saturated)
  //
  // vd[i] = va[i] / vb[i]

  _VDIVS_S8, _VDIVS_S16, _VDIVS_S32, _VDIVS_S64, // op_vec_vdiv_saturated_impl.hpp

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // Vector modulus (unsigned integer)
  //
  // vd[i] = va[i] % vb[i]

  _VMOD_U8,  _VMOD_U16,  _VMOD_U32,  _VMOD_U64, // op_vec_vmod_impl.hpp

  // Vector modulus (signed integer)
  //
  // vd[i] = va[i] % vb[i]

  _VMOD_S8,  _VMOD_S16,  _VMOD_S32,  _VMOD_S64, // op_vec_vmod_impl.hpp

  // Vector modulus (float)
  //
  // vd[i] = va[i] % vb[i]

  _VMOD_F32, _VMOD_F64, // op_vec_vmod_impl.hpp

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // No saturating vector modulus

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // Vector AND/OR/XOR - All operate at a byte size since there is no behavioural differences for other word sizes.
  //
  // vd[i] = va[i] &|^ vb[i]

  _VAND_8,   _VOR_8,     _VXOR_8, // op_vec_vbitwise_impl.hpp


  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // Vector mapping - convert an array of indexed values into values
  //
  // vd[i] = vm[vs[i]]
  _VMAP_8_16, _VMAP_8_32, _VMAP_8_64, _VMAP_16_32, _VMAP_16_64, // op_vec_map_impl.hpp

  MAX_VEC
} VectorOp;

#endif
