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


#ifndef _VM_DEFS_HPP_
#define _VM_DEFS_HPP_
#include "machine.hpp"

#define VM_FULL_DEBUG

// types:
// .s8, .s16, .s32, .s64 - signed integer
// .u8, .u16, .u32, .u64 - unsigned integer
// .f32, .f64            - float
// .i                    - any integer type
// .f                    - any float type
// .a                    - any arithmetic type

// .8, .16, .32, .64     - size only (untyped)
// .x                    - any operand

class VMDefs {
public:

  // Opcode definitions

  typedef enum {
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
    // [opcode] [ 0 : rX]
    // [ extension data ]
    // [ extension data ]

    // in object code format
    // [ MSB : 1-bit internal/external, 15-bit index MSW ]
    // [ 16-bit index LSW ]

    // in memory
    // [ 32-bit endian native operand address in host memory ]

    _LD_8, _LD_16, _LD_32, _LD_64,

    // loads the address of the operand into a register
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
    // [opcode] [ 0 : rX]
    // [ extension data ]
    // [ extension data ]

    // in object code format
    // [ MSB : 1-bit internal/external, 15-bit index MSW ]
    // [ 16-bit index LSW ]

    // in memory
    // [ 32-bit endian native operand address in host memory ]

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
    // [opcode] [     0 ]
    // [ extension data ]
    // [ extension data ]

    // in object code format
    // [ MSB : 1-bit internal/external, 15-bit index MSW ]
    // [ 16-bit index LSW ]

    // in memory
    // [ 32-bit endian native operand address in host memory ]

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

    MAX_OP
  } NormalOp;

  typedef enum {
    // bit masks used in multi-register transfers
    BITMASK_R1 = 0x0001,
    BITMASK_R2 = 0x0002,
    BITMASK_R3 = 0x0004,
    BITMASK_R4 = 0x0008,
    BITMASK_R5 = 0x0010,
    BITMASK_R6 = 0x0020,
    BITMASK_R7 = 0x0040,
    BITMASK_R8 = 0x0080,
    BITMASK_R9 = 0x0100,
    BITMASK_R10 = 0x0200,
    BITMASK_R11 = 0x0400,
    BITMASK_R12 = 0x0800,
    BITMASK_R13 = 0x1000,
    BITMASK_R14 = 0x2000,
    BITMASK_R15 = 0x4000,
    BITMASK_R16 = 0x8000
  } MultiRegMask;

  typedef enum {
    RUNNING = 0,
    INITIAL,
    COMPLETED,
    BREAKPOINT,
    ILLEGAL_OPCODE,
    ZERO_DIVIDE,
    REG_STACK_OVERFLOW,
    REG_STACK_UNDERFLOW,
    DATA_STACK_OVERFLOW,
    DATA_STACK_UNDERFLOW,
    CALL_STACK_OVERFLOW,
    CALL_EMPTY,
    CALL_EMPTY_NATIVE
  } VMStatus;
};

#endif
