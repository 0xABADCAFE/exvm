//****************************************************************************//
//**                                                                        **//
//** File:         vm_debug.cpp                                             **//
//** Description:  Debugging definitions                                    **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2017-07-18                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

#include "include/vm.hpp"

#ifdef VM_DEBUG

const char* ExVM::debugLevel(uint32 level) {
  const char* errorLevels[] = {
    "ERR",
    "WRN",
    "INF",
    "DBG"
  };
  if (level < sizeof(errorLevels)/sizeof(const char*)) {
    return errorLevels[level];
  }
  return "---";
}

#endif

#include <cstdio>
#include <cstring>
#include "include/vm_core.hpp"
#include "include/vm_inline.hpp"
#include "include/vm_linker.hpp"
#include <new>

#if _VM_INTERPRETER == _VM_INTERPRETER_SWITCH_CASE
  #include "include/vm_interpreter_switch_case.hpp"
#elif _VM_INTERPRETER == _VM_INTERPRETER_CUSTOM
  #include "include/vm_interpreter_custom.hpp"
#endif

using std::nothrow;
using namespace ExVM;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// DebuggingInterpreter
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "include/vm_interpreter_debugging.hpp"

const char* DebuggingInterpreter::statusCodes[] = {
  "Running",
  "Initialised",
  "Completed",
  "Breakpoint",
  "Change instruction set",
  "Illegal opcode",
  "Integer divide by zero",
  "Register stack overflow",
  "Register stack underflow",
  "Data stack overflow",
  "Data stack underflow",
  "Call stack overflow",
  "Call empty address",
  "Call empty native address",
  "Unknown code symbol",
  "Unknown data symbol",
  "Unknown native code symbol",
};

namespace {

const char* scalarNames[] = {

  // LEVEL 0

  // control group ////////////////////////////////////////
  "nop",
  "brk",

  // load group ///////////////////////////////////////////

  // immediate small literal, 0-15
  // ldq #n, rX
  // [opcode] [#n : rX]
  "ldq",

  // immediate 16-bit integer literal, -32768 to 32767
  // allowed for 8/16-bit destination operands,
  // values outside the 8-bit range are truncated for 8-bit.
  //
  // ld.i #n, rX
  // [opcode] [0 : rX]
  // [ literal data  ]
  "ld.i8  #<16>, rD",
  "ld.i16 #<16>, rD",
  "ld.i32 #<16>, rD",

  // immediate 32-bit literal, can be 32-bit integer or floating point.
  // allowed for 32/64-bit destination operands.
  //
  // ld.x #n, rX
  // [opcode] [0 : rX]
  // [ literal data  ]
  // [ literal data  ]
  "ld.32 #<32>, rD",

  // register indirect
  // ld.x (rS), rD
  // [opcode] [rS : rD]
  "ld.8  (rS), rD",
  "ld.16 (rs), rD",
  "ld.32 (rS), rD",

  // register indirect post increment
  // ld.x (rS)+, rD
  // [opcode] [rS : rD]
  "ld.8  (rS)+, rD",
  "ld.16 (rS)+, rD",
  "ld.32 (rS)+, rD",

  // register indirect pre decrement
  // ld.x -(rS), rD
  // [opcode] [rS : rD]
  "ld.8  -(rS), rD",
  "ld.16 -(rS), rD",
  "ld.32 -(rS), rD",

  // register indirect with displacement
  // ld.x (rS,#d), rD
  // [opcode] [rS : rD]
  // [ displacement16 ]
  "ld.8  #<16>(rS), rD",
  "ld.16 #<16>(rS), rD",
  "ld.32 #<16>(rS), rD",

  // load global reference
  // ld.x label,rX
  // [opcode] [ Data Symbol ID {16:19} : rX ]
  // [          Data Symbol ID {0:15}       ]
  "ld.8  @data, rD",
  "ld.16 @data, rD",
  "ld.32 @data, rD",

  // loads the address implied by the data symbol ID into the specified register:
  // lda label, rX
  // [opcode] [ Data Symbol ID {16:19} : rX ]
  // [          Data Symbol ID {0:15}       ]

  "lda @data, rD",

  // Load executable symbol reference into the specified register
  // ldc label, rX
  // [opcode] [ Code Symbol ID {16:19} : rX ]
  // [          Code Symbol ID {0:15}       ]
  "ldc @code, rD",

  // Load native symbol reference into the specified register
  // ldn label, rX
  // [opcode] [ Native Symbol ID {16:19} : rX ]
  // [          Native Symbol ID {0:15}       ]
  "ldn @native, rD",

  // store group ////////////////////////////////////////

  // register indirect
  // st.x rS, (rD)
  // [opcode] [rS : rD]
  "st.8  rS, (rD)",
  "st.16 rs, (rD)",
  "st.32 rS, (rD)",

  // register indirect post increment
  // st.x rS, (rD)+
  // [opcode] [rS : rD]
  "st.8  rS, (rD)+",
  "st.16 rs, (rD)+",
  "st.32 rS, (rD)+",

  // register indirect pre decrement
  // st.x rS, -(rD)
  // [opcode] [rS : rD]
  "st.8  rS, -(rD)",
  "st.16 rs, -(rD)",
  "st.32 rS, -(rD)",

  // register indirect with displacement
  // st.x rS, (rD,#d)
  // [opcode] [rS : rD]
  // [ displacement16 ]
  "ld.8  rS, #<16>(rD)",
  "ld.16 rS, #<16>(rD)",
  "ld.32 rS, #<16>(rD)",

  // store global reference
  // st.x rX,label
  // [opcode] [ Data Symbol ID {16:19} : rX ]
  // [          Data Symbol ID {0:15}       ]
  "st.8  rS, @data",
  "st.16 rS, @data",
  "st.32 rS, @data",

  // move group /////////////////////////////////////////

  // mv.x rS,rD
  "mv.8  rS, rD",
  "mv.16 rS, rD",
  "mv.32 rS, rD",

  // bswp.x rS,rD
  "bswp.16 rS, rD",
  "bswp.32 rS, rD",

  // exg rS,rD
  "exg rS, rD",

  // push / pop group ///////////////////////////////////

  // save multiple regs to register stack, save/restore

  // sv/rs.x rA,rB,rC...
  // [opcode] [0 : 0]
  // [#register mask]
  "sv rA, rB, ...",
  "rs rA, rB, ...",

  // Push values from register(s) to data stack
  // push.x rA,rB,rC...
  // [opcode] [0 : 0]
  // [#register mask]
  "push.8  rA, rB, ...",
  "push.16 rA, rB, ...",
  "push.32 rA, rB, ...",

  // Pop values from stack to register(s)
  // pop.x rA,rB,rC...
  // [opcode] [0 : 0]
  // [#register mask]
  "pop.8  rA, rB, ...",
  "pop.16 rA, rB, ...",
  "pop.32 rA, rB, ...",

  // Reserve space on the data stack
  // [opcode] [0 : rX]
  // [#size]
  "salloc #<16>, rD",

  // Free stack reserved space
  // [opcode] [0 : rX]
  "sfree rS",

  // jump/branch group //////////////////////////////////

  // Branch call. Call a PC relative displacement as a function.
  "bcall #<8>",
  "bcall #<16>",

  // call global reference
  // call label
  // calln label
  // [opcode] [ Code Symbol ID{16:24} ]
  // [          Code Symbol ID{0-15}  ]
  "call @code",
  "calln @native",

  // indirect calling. Assumes that the lower 32-bits of the register contains a code or native symbol ID
  // call rX
  // calln rX
  "icall (rD)",
  "icalln (rD)",
  "ret",

  // unconditional branches, max 16-bit pc relative displacement
  // bra(.8) label
  // [opcode] [ displacement8 ]
  // bra(.16) label
  // [opcode] [     0 ]
  // [ displacement16 ]
  // pc relative
  // assembler should resolve .8/.16 automatically
  "bra #<8>",
  "bra #<16>",

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
  "case rX",

  // conditional branches - max 16-bit pc relative displacement
  // [opcode] [rS : rD]
  // [ displacement16 ]
  // pc relative
  "bnz.8  rS, #<16>",
  "bnz.16 rS, #<16>",
  "bnz.32 rS, #<16>",

  // beq.x rS,rD,label
  // branch taken if rS == rD
  "beq.8  rS, rD, #<16>",
  "beq.16 rS, rD, #<16>",
  "beq.32 rS, rD, #<16>",

  // bgreq.x rS,rD,label
  // branch taken if rS => rD
  "bgreq.s8  rS, rD, #<16>",
  "bgreq.s16 rS, rD, #<16>",
  "bgreq.s32 rS, rD, #<16>",

  // bgr.x rS,rD,label
  // branch taken if rS > rD
  "bgr.s8  rS, rD, #<16>",
  "bgr.s16 rS, rD, #<16>",
  "bgr.s32 rS, rD, #<16>",

  // cast group /////////////////////////////////////////

  // widening

  // signed extension, signed to float
  "tos16.s8  rS, rD",
  "tos32.s8  rS, rD",
  "tos32.s16 rS, rD",

  // Arithmetic commands, data treat as signed integer / float
  // add.x rS,rD (rD += rS)
  "add.i8  rS, rD",
  "add.i16 rS, rD",
  "add.i32 rS, rD",

  // add immediate
  "addi.i8  #<8>, rD",
  "addi.i16 #<16>, rD",
  "addi.i32 #<32>, rD",

  // sub.x rS,rD (rD -= rS)
  "sub.i8  rS, rD",
  "sub.i16 rS, rD",
  "sub.i32 rS, rD",

  // mul.x rS,rD (rD *= rS)
  "mul.u8  rS, rD",
  "mul.u16 rS, rD",
  "mul.u32 rS, rD",
  "mul.s8  rS, rD",
  "mul.s16 rS, rD",
  "mul.s32 rS, rD",

  // div.x rS,rD (rD /= rS)
  "div.u8  rS, rD",
  "div.u16 rS, rD",
  "div.u32 rS, rD",
  "div.s8  rS, rD",
  "div.s16 rS, rD",
  "div.s32 rS, rD",

  // mod.x rS,rD (rD %= rS)
  "mod.u8  rS, rD",
  "mod.u16 rS, rD",
  "mod.u32 rS, rD",
  "mod.s8  rS, rD",
  "mod.s16 rS, rD",
  "mod.s32 rS, rD",

  // neg.x rS,rD (rD = -rS)
  "neg.s8  rS, rD",
  "neg.s16 rS, rD",
  "neg.s32 rS, rD",

  // asr.x rS,rD (rD >>= rS) - arithmetic, preserves sign
  "asr.s8  rS, rD",
  "asr.s16 rS, rD",
  "asr.s32 rS, rD",

  // min.x rS,RD
  "min.s8  rS, rD",
  "min.s16 rS, rD",
  "min.s32 rS, rD",

  // max.x rS,rD
  "max.s8  rS, rD",
  "max.s16 rS, rD",
  "max.s32 rS, rD",

  // Logic commands, data treat as unsigned binary

  // and.x rS,RD (rD &= rS)
  "and.8  rS, rD",
  "and.16 rS, rD",
  "and.32 rS, rD",

  // or.x rS,RD (rD |= rS)
  "or.8  rS, rD",
  "or.16 rS, rD",
  "or.32 rS, rD",

  // xor.x rS,RD (rD ^= rS)
  "xor.8  rS, rD",
  "xor.16 rS, rD",
  "xor.32 rS, rD",

  // inv.x rS,RD (rD = ~rS)
  "inv.8  rS, rD",
  "inv.16 rS, rD",
  "inv.32 rS, rD",

  // lsl.x rS,rD (rD <<= rS) - logical
  "lsl.8  rS, rD",
  "lsl.16 rS, rD",
  "lsl.32 rS, rD",

  // lsr.x rS,rD (rD >>= rS) - logical
  "lsr.8  rS, rD",
  "lsr.16 rS, rD",
  "lsr.32 rS, rD",

  // rol.x rS,rD (rD <@= rS) - rotate left
  "rol.8  rS, rD",
  "rol.16 rS, rD",
  "rol.32 rS, rD",

  // ror.x rS,rD (rD @>= rS) - rotate right
  "ror.8  rS, rD",
  "ror.16 rS, rD",
  "ror.32 rS, rD",

  // LEVEL 1
  // beq.x rS,rD,label
  // branch taken if rS == rD
  "beq.f32 rS, rD, #<16>",

  // bgreq.x rS,rD,label
  // branch taken if rS => rD
  "bgreq.f32 rS, rD, #<16>",

  // bgr.x rS,rD,label
  // branch taken if rS > rD
  "bgr.f32 rS, rD, #<16>",

  // cast group /////////////////////////////////////////

  // widening

  // signed extension, signed to float
  "tof32.s8  rS, rD",
  "tof32.s16 rS, rD",
  "tof32.s32 rS, rD",

  // unsigned to float
  // unsigned extension must be implemented in virtual code
  "tof32.u8  rS, rD",
  "tof32.u16 rS, rD",
  "tof32.u32 rS, rD",

  // narrowing, double to float / float to signed
  // double/float to unsigned must be implemented in virtual code
  "tos32.f32 rS, rD",
  "tos16.f32 rS, rD",
  "tos8.f32  rS, rD",

  // Arithmetic commands, data treat as signed integer / float
  // add.x rS,rD (rD += rS)
  "add.f32 rS, rD",

  // sub.x rS,rD (rD -= rS)
  "sub.f32 rS, rD",

  // mul.x rS,rD (rD *= rS)
  "mul.f32 rS, rD",

  // div.x rS,rD (rD /= rS)
  "div.f32 rS, rD",

  // mod.x rS,rD (rD %= rS)
  "mod.f32 rS, rD",

  // neg.x rS,rD (rD = -rS)
  "neg.f32 rS, rD",

  // min.x rS,RD
  "min.f32 rS, rD",

  // max.x rS,RD
  "max.f32 rS, rD",

  // LEVEL 2

  // immediate 16-bit integer literal, -32768 to 32767
  // allowed for 8/16-bit destination operands,
  // values outside the 8-bit range are truncated for 8-bit.
  //
  // ld.i #n, rX
  // [opcode] [0 : rX]
  // [ literal data  ]
  "ld.i64 #<16>, rD",

  // immediate 32-bit literal, can be 32-bit integer or floating point.
  // allowed for 32/64-bit destination operands.
  //
  // ld.x #n, rX
  // [opcode] [0 : rX]
  // [ literal data  ]
  // [ literal data  ]
  "ld.i64 #<32>, rD",
  "ld.f64 #<32>, rD",

  // register indirect
  // ld.x (rS), rD
  // [opcode] [rS : rD]
  "ld.64 (rS), rD",

  // register indirect post increment
  // ld.x (rS)+, rD
  // [opcode] [rS : rD]
  "ld.64 (rS)+, rD",

  // register indirect pre decrement
  // ld.x -(rS), rD
  // [opcode] [rS : rD]
  "ld.64 -(rS), rD",

  // register indirect with displacement
  // ld.x (rS,#d), rD
  // [opcode] [rS : rD]
  // [ displacement16 ]
  "ld.64 #<16>(rS), rD",

  // load global reference
  // ld.x label,rX
  // [opcode] [ Data Symbol ID {16:19} : rX ]
  // [          Data Symbol ID {0:15}       ]
  "ld.64 @data, rD",

  // store group ////////////////////////////////////////

  // register indirect
  // st.x rS, (rD)
  // [opcode] [rS : rD]
  "st.64 rS, (rD)",

  // register indirect post increment
  // st.x rS, (rD)+
  // [opcode] [rS : rD]
  "st.64 rS, (rD)+",

  // register indirect pre decrement
  // st.x rS, -(rD)
  // [opcode] [rS : rD]
  "st.64 rS, -(rD)",

  // register indirect with displacement
  // st.x rS, (rD,#d)
  // [opcode] [rS : rD]
  // [ displacement16 ]
  "st.64 rS, #<16>(rD)",

  // store global reference
  // st.x rX,label
  // [opcode] [ Data Symbol ID {16:19} : rX ]
  // [          Data Symbol ID {0:15}       ]
  "st.64 rS, @data",

  // move group /////////////////////////////////////////

  // mv.x rS,rD
  "mv.64 rS, rD",

  // bswp.x rS,rD
  "bswp.64 rS, rD",

  // push / pop group ///////////////////////////////////

  // Push values from register(s) to data stack
  // push.x rA,rB,rC...
  // [opcode] [0 : 0]
  // [#register mask]
  "push.64 rA, rB, ...",

  // Pop values from stack to register(s)
  // pop.x rA,rB,rC...
  // [opcode] [0 : 0]
  // [#register mask]
  "pop.64 rA, rB, ...",

  // jump/branch group //////////////////////////////////
  // conditional branches - max 16-bit pc relative displacement
  // [opcode] [rS : rD]
  // [ displacement16 ]
  // pc relative

  "bnz.64 rS, #<d16>",

  // beq.x rS,rD,label
  // branch taken if rS == rD
  "beq.i64 rS, rD, #<d16>",
  "beq.f64 rS, rD, #<d16>",

  // bgreq.x rS,rD,label
  // branch taken if rS => rD
  "bgreq.s64 rS, rD, #<d16>",
  "bgreq.f64 rS, rD, #<d16>",

  // bgr.x rS,rD,label
  // branch taken if rS > rD
  "bgr.s64 rS, rD, #<d16>",
  "bgr.f64 rS, rD, #<d16>",

  // cast group /////////////////////////////////////////

  // widening

  // signed extension, signed to float
  "tos64.s8  rS, rD",
  "tof64.s8  rs, rD",
  "tos64.s16 rS, rD",
  "tot64.s16 rS, rD",
  "tos64.s32 rS, rD",
  "tof64.s32 rs, rD",
  "tof32.s64 rS, rD",
  "tof64.s64 rS, rD",

  // unsigned to float
  // unsigned extension must be implemented in virtual code
  "tof64.u8  rS, rD", //_U8_2_F64,
  "tof64.u16 rS, rD", //_U16_2_F64,
  "tof64.u32 rS, rD", //_U32_2_F64,
  "tof32.u64 rS, rD", //_U64_2_F32,
  "tof64.u64 rS, rD", //_U64_2_F64,

  // float to double
  "tof64.f32 rS, rD", //_F32_2_F64,

  // narrowing, double to float / float to signed
  // double/float to unsigned must be implemented in virtual code
  "tof32.f64 rS, rD",//_F64_2_F32,
  "tos64.f64 rS, rD",//_F64_2_S64,
  "tos32.f64 rS, rD",//_F64_2_S32,
  "tos16.f64 rS, rD",//_F64_2_S16,
  "tos8.f64  rS, rD",//_F64_2_S8,
  "tos64.f32 rS, rD",//_F32_2_S64,

  // Arithmetic commands, data treat as signed integer / float
  // add.x rS,rD (rD += rS)
  "add.i64 rS, rD", //_ADD_I64,
  "add.f64 rS, rD", //_ADD_F64,

  // sub.x rS,rD (rD -= rS)
  "sub.i64 rS, rD", //_SUB_I64,
  "add.f64 rS, rD", //_SUB_F64,

  // mul.x rS,rD (rD *= rS)
  "mul.u64 rS, rD", //_MUL_U64,
  "mul.s64 rS, rD", //_MUL_S64,
  "mul.f64 rS, rD", //_MUL_F64,

  // div.x rS,rD (rD /= rS)
  "div.u64 rS, rD", //_DIV_U64,
  "div.s64 rS, rD", //_DIV_S64,
  "div.f64 rS, rD", //_DIV_F64,

  // mod.x rS,rD (rD %= rS)
  "mod.u64 rS, rD", //_MOD_U64,
  "mod.s64 rS, rD", //_MOD_S64,
  "add.f64 rS, rD", //_MOD_F64,

  // neg.x rS,rD (rD = -rS)
  "neg.s64 rS, rD", //_NEG_S64,
  "neg.f64 rS, rD", //_NEG_F64,

  // asr.x rS,rD (rD >>= rS) - arithmetic, preserves sign
  "asr.s64 rS, rD", //_ASR_S64,

  // min.x rS,RD
  "min.s64 rS, rD", //_MIN_S64,
  "min.f64 rS, rD", //_MIN_F64,

  // max.x rS,RD
  "max.s64 rS, rD", //_MAX_S64,
  "max.f64 rS, rD", //_MAX_F64,

  // Logic commands, data treat as unsigned binary

  // and.x rS,RD (rD &= rS)
  "and.64 rS, rD", //_AND_64,

  // or.x rS,RD (rD |= rS)
  "or.64 rS, rD", //_OR_64,

  // xor.x rS,RD (rD ^= rS)
  "xor.64 rS, rD", //_XOR_64,

  // inv.x rS,RD (rD = ~rS)
  "inv.64 rS, rD", //_INV_64,

  // lsl.x rS,rD (rD <<= rS) - logical
  "lsl.64 rS, rD", //_LSL_64,

  // lsr.x rS,rD (rD >>= rS) - logical
  "lsr.64 rS, rD", //_LSR_64,

  // rol.x rS,rD (rD <@= rS) - rotate left
  "rol.64 rS, rD", //_ROL_64,

  // ror.x rS,rD (rD @>= rS) - rotate right
  "ror.64 rS, rD", //_ROR_64,

  "adv-",
  "vec-",
};

const char* advancedNames[] = {
  // LEVEL 0
  // register indirect, scale indexed
  // ld.x (rS,rI,#s), rD
  "ld.8  (rS, rI, #<8>), rD", //_LD_RII_8,
  "ld.16 (rS, rI, #<8>), rD", //_LD_RII_16,
  "ld.32 (rS, rI, #<8>), rD", //_LD_RII_32,

  // register indirect, scale indexed
  // st.x rS, (rD,rI,#d)
  "ld.8  rS, (rD, rI, #<8>)", //_ST_RII_8,
  "ld.16 rS, (rD, rI, #<8>)", //_ST_RII_16,
  "ld.32 rS, (rD, rI, #<8>)", //_ST_RII_32,

  // Logically shift, with mask
  // lslm.32 rS,rB,rM,rD
  "lslm.32 rS, rB, rM, rD", //_LSLM_32,
  "lsrm.32 rS, rB, rM, rD", //_LSRM_32,

  // LEVEL 1

  // Load constants
  "ld_const.f32 <enum>, rD", //_LD_CONST_F32,

  // Multiply Add
  "madd.f32 rA, rB, rC, rD", //_MADD_F32,

  // Roots
  "sqrt.f32 rS, rD", //_SQRT_F32,
  "isqrt.f32 rS, rD",//_ISQRT_F32,

  // Trig - Arc
  "acos.f32 rS, rD", //_ACOS_F32,
  "asin.f32 rS, rD", //_ASIN_F32,
  "atan.f32 rS, rD", //_ATAN_F32,

  // Trig - Regular
  "cos.f32 rS, rD", //_COS_F32,
  "sin.f32 rS, rD", //_SIN_F32,
  "tan.f32 rS, rD", //_TAN_F32,

  // Trig - Hyperbolic
  "cosh.f32 rS, rD", //_COSH_F32,
  "sinh.f32 rS, rD", //_SINH_F32,
  "tanh.f32 rS, rD", //_TANH_F32,

  // Trig - Simultaneous sine and cosine
  "sincos.f32 rS, rD, rD", //_SINCOS_F32,

  // Exponentiation and powers
  "exp.f32 rS, rD", //_EXP_F32,
  "pow.f32 rS, rP, rD", //_POW_F32,

  // Logarithms
  "logn.f32  rS, rD", //_LOGN_F32,
  "log2.f32  rS, rD", //_LOG2_F32,
  "log10.f32 rS, rD", //_LOG10_F32,
  "logx.f32  rS, rX, rD", //_LOGX_F32,

  // Truncation and rounding
  "ceil.f32 rS, rD", //_CEIL_F32,
  "floor.f32 rS, rD", //_FLOOR_F32,

  // Interpolaton
  "lerp.f32 rA, rB, rL, rD", //_LERP_F32,

  // Fixed 2D vectors : float32[2]
  "splat_vec2.f32 rS, rD", //_SPLAT_V2F32, // splat fill, all elements set to the same value
  "copy_vec2.f32 rS, rD", //_COPY_V2F32,  // copy
  "add_vec2.f32 rS, rD", //_ADD_V2F32,   // add
  "sub_vec2.f32 rS, rD", //_SUB_V2F32,   // subtract
  "dot_vec2.f32 rA, rB, rD", //_DOT_V2F32,   // dot product
  "scale_vec2.f32 rS, rF, rD", //_SCALE_V2F32, // scale
  "magn_vec2.f32 rS, rD", //_MAGN_V2F32,  // magnitude
  "norm_vec2.f32 rS, rD", //_NORM_V2F32,  // normalise
  "lerp_vec2.f32 rA, rB, rL, rD", //_LERP_V2F32,  // interpolate

  "xform_vec2.f32", //_M3X3_V2F32, // transform a set of vec2f using a 4x4 matrix

  // Complex number oberations C2F32, extends the 2D vector operations

  "mul_cmpl.f32 rA, rB, rD", //_MUL_C2F32,    // Complex Multiply
  "div_cmpl.f32 rA, rB, rD", //_DIV_C2F32,    // Complex Divide

  // Fixed 3D vectors : float32[3]
  "splat_vec3.f32 rS, rD", //_SPLAT_V3F32, // splat fill, all elements set to the same value
  "copy_vec3.f32 rS, rD", //_COPY_V3F32,  // copy
  "add_vec3.f32 rA, rB, rD", //_ADD_V3F32,   // add
  "sub_vec3.f32 rA, rB, rD", //_SUB_V3F32,   // subtract
  "cross_vec3.f32 rA, rB, rD", //_CROSS_V3F32, // cross product
  "dot_vec3.f32 rA, rB, rD", //_DOT_V3F32,   // dot product
  "scale_vec3.f32 rS, rF, rD", //_SCALE_V3F32, // scale
  "magn_vec3.f32 rS, rD", //_MAGN_V3F32,  // magnitude
  "norm_vec3.f32 rS, rD", //_NORM_V3F32,  // normalise
  "lerp_vec3.f32 rA, rB, rL, rD", //_LERP_V3F32,  // interpolate

  "xform_vec3.f32", //_M4X4_V3F32, // transform a set of vec3f using a 4x4 matrix

  // LEVEL 2

  // register indirect, scale indexed
  // ld.x (rS,rI,#s), rD
  "ld.64 (rS, rI, #<8>), rD", //_LD_RII_64,

  // register indirect, scale indexed
  // st.x rS, (rD,rI,#d)
  "ld.64 rS, (rD, rI, #<8>)", //_ST_RII_64,

  // Logically shift, with mask
  // lslm.32 rS,rB,rM,rD
  "lslm.64 rS, rB, rM, rD", //_LSLM_64,
  "lsrm.64 rS, rB, rM, rD", //_LSRM_64,

  // Load constants
  "ld_const.f64 <enum>, rD", //_LD_CONST_F64,

  // Multiply Add
  "madd.f64 rA, rB, rC, rD", //_MADD_F64,

  // Roots
  "sqrt.f64 rS, rD", //_SQRT_F64,
  "isqrt.f64 rS, rD", //_ISQRT_F64,

  // Trig - Arc
  "acos.f64 rS, rD", //_ACOS_F64,
  "asin.f64 rS, rD", //_ASIN_F64,
  "atan.f64 rS, rD", //_ATAN_F64,

  // Trig - Regular
  "cos.f64 rS, rD", //_COS_F64,
  "sin.f64 rS, rD", //_SIN_F64,
  "tan.f64 rS, rD", //_TAN_F64,

  // Trig - Hyperbolic
  "cosh.f64 rS, rD", //_COSH_F64,
  "sinh.f64 rS, rD", //_SINH_F64,
  "tanh.f64 rS, rD", //_TANH_F64,

  // Trig - Simultaneous sine and cosine
  "sincos.f64 rS, rD, rD", //_SINCOS_F64,

  // Exponentiation and powers
  "exp.f64 rS, rD", //_EXP_F64,
  "pow.f64 rS, rP, rD", //_POW_F64,

  // Logarithms
  "logn.f64  rS, rD", //_LOGN_F64,
  "log2.f64  rS, rD", //_LOG2_F64,
  "log10.f64 rS, rD", //_LOG10_F64,
  "logx.f64  rS, rX, rD", //_LOGX_F64,

  // Truncation and rounding
  "ceil.f64 rS, rD", //_CEIL_F64,
  "floor.f64 rS, rD", //_FLOOR_F64,

  // Interpolaton
  "lerp.f64 rA, rB, rL, rD", //_LERP_F64,

  // Fixed 2D vectors : float64[2]
  "splat_vec2.f64 rS, rD", //_SPLAT_V2F64, // splat fill, all elements set to the same value
  "copy_vec2.f64 rS, rD", //_COPY_V2F64,  // copy
  "add_vec2.f64 rA, rB, rD", //_ADD_V2F64,   // add
  "sub_vec2.f64 rA, rB, rD", //_SUB_V2F64,   // subtract
  "dot_vec2.f64 rA, rB, rD", //_DOT_V2F64,   // dot product
  "scale_vec2.f64 rS, rF, rD", //_SCALE_V2F64, // scale
  "magn_vec2.f64 rS, rD", //_MAGN_V2F64,  // magnitude
  "norm_vec2.f64 rS, rD", //_NORM_V2F64,  // normalise
  "lerp_vec2.f64 rA, rB, rL, rD", //_LERP_V2F64,  // interpolate

  "xform_vec2.f64", //_M3X3_V2F64, // transform a set of vec2d using a 4x4 matrix

  // Complex number oberations C2F64, extends the 2D vector operations

  "mul_cmpl.f64 rA, rB, rD", //_MUL_C2F64,    // Complex Multiply
  "div_cmpl.f64 rA, rB, rD", //_DIV_C2F64,    // Complex Divide

  // Fixed 3D vectors : float64[3]
  "splat_vec3.f64 rS, rD", //_SPLAT_V3F64, // splat fill, all elements set to the same value
  "copy_vec3.f64 rS, rD", //_COPY_V3F64,  // copy
  "add_vec3.f64 rA, rB, rD", //_ADD_V3F64,   // add
  "sub_vec3.f64 rA, rB, rD", //_SUB_V3F64,   // subtract
  "cross_vec3.f64 rA, rB, rD", //_CROSS_V3F64, // cross product
  "dot_vec3.f64 rA, rB, rD", //_DOT_V3F64,   // dot product
  "scale_vec3.f64 rS, rF, rD", //_SCALE_V3F64, // scale
  "magn_vec3.f64 rS, rD", //_MAGN_V3F64,  // magnitude
  "norm_vec3.f64 rS, rD", //_NORM_V3F64,  // normalise
  "lerp_vec3.f64 rA, rB, rL, rD", //_LERP_V3F64,  // interpolate

  "xform_vec3.f64", //_M4X4_V3F64, // transform a set of vec3d using a 4x4 matrix
};

const char* vectorNames[] = {
  // LEVEL 0

  // LEVEL 1

  // LEVEL 2
};

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DebuggingInterpreter::DebuggingInterpreter(size_t rStackSize, size_t dStackSize, size_t cStackSize) :
Interpreter(rStackSize, dStackSize, cStackSize), debugFlags(0xFFFFFFFF) {
  debuglog(LOG_INFO, "VM compiled %d-bit native, gpr alignment is %d bytes", X_PTRSIZE, (int)(8 - (((long)gpr) & 7)) );
  debuglog(LOG_INFO, "There are presently %d scalar, %d advanced and %d stream instructions defined", VMDefs::MAX_OP, VMDefs::MAX_ADV, VMDefs::MAX_VEC);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DebuggingInterpreter::~DebuggingInterpreter() {
  debuglog(LOG_INFO, "Destroyed Interpreter");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void DebuggingInterpreter::dump() {
  std::printf("DebuggingInterpreter dump\n\n");
  std::printf("rX: %18s : %12s : %6s : %4s : c\n",
    "64-bit (hex dump)",
    "s32",
    "s16",
    "s8"
  );
  for (int i = 0; i < NUM_GPR; i++) {
    std::printf("%2d: 0x%08X%08X : %12d : %6d : %4d : %c : %.8f\n", i,
      (unsigned)gpr[i].getMSW(), (unsigned)gpr[i].getLSW(),
      (int)gpr[i].s32(),
      (int)gpr[i].s16(),
      (int)gpr[i].s8(),
      (int)((gpr[i].u8()>32 && gpr[i].u8() < 127) ? gpr[i].u8() : '.'),
      gpr[i].f32()
    );
  }
#if X_PTRSIZE == XA_PTRSIZE64
  std::printf("PC: %p\n",             pc.inst);
  std::printf("RS: %p (%td)\n",       regStack, (regStack-regStackBase));
  std::printf("DS: %p (%td)\n",       dataStack.u8, (dataStack.u8-dataStackBase));
  std::printf("CS: %p (%td)\n",       callStack, (callStack-callStackBase));
  std::printf("ST: 0x%08X (%s)\n\n",  (unsigned)status, statusCodes[status]);
#else
  std::printf("PC: 0x%08X\n",         (unsigned)pc.inst);
  std::printf("RS: 0x%08X (%d)\n",    (unsigned)regStack, (regStack-regStackBase));
  std::printf("DS: 0x%08X (%d)\n",    (unsigned)dataStack.u8, (dataStack.u8-dataStackBase));
  std::printf("CS: 0x%08X (%d)\n",    (unsigned)callStack, (callStack-callStackBase));
  std::printf("ST: 0x%08X (%s)\n\n",  (unsigned)status, statusCodes[status]);
#endif
  std::puts("Stats Collected:");
  std::printf(
    "\tInstructions Executed: %" FU64 "\n",
    totalStatements
  );
  std::printf(
    "\tFunction Calls : %" FU32 "\n"
    "\t   Normal (sym): %" FU32 "\n"
    "\t   Local (anon): %" FU32 "\n"
    "\t   Native      : %" FU32 "\n",
    (functionCalls + nativeFunctionCalls + branchCalls),
    functionCalls,
    branchCalls,
    nativeFunctionCalls
  );

  std::printf(
    "\tBranches         : %" FU32 "\n"
    "\t   Unconditional : %" FU32 "\n"
    "\t   Taken         : %" FU32 "\n"
    "\t   Not Taken     : %" FU32 "\n",
    (unconditionalBranches + conditionalBranchesTaken + conditionalBranchesNotTaken),
    unconditionalBranches,
    conditionalBranchesTaken,
    conditionalBranchesNotTaken
  );

  std::puts("\tScalar Opcode Execution Breakdown");
  for (uint32 i = 0; i<sizeof(scalarCount)/sizeof(uint32); i++) {
    if (scalarCount[i]) {
      std::printf(
        "\t   %02X %28s : %9" FU32 "\n",
        (unsigned)i,
        scalarNames[i],
        scalarCount[i]
      );
    }
  }
  std::puts("\tAdvanced Opcode Execution Breakdown");
  for (uint32 i = 0; i<sizeof(advancedCount)/sizeof(uint32); i++) {
    if (advancedCount[i]) {
      std::printf(
        "\t   %02X %28s : %9" FU32 "\n",
        (unsigned)i,
        advancedNames[i],
        advancedCount[i]
      );
    }
  }
  std::puts("\tVector Opcode Execution Breakdown");
  for (uint32 i = 0; i<sizeof(vectorCount)/sizeof(uint32); i++) {
    if (vectorCount[i]) {
      std::printf(
        "\t   %02X : %" FU32 "\n",
        (unsigned)i,
        vectorCount[i]
      );
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void DebuggingInterpreter::execute() {

  std::memset(scalarCount,   0, sizeof(scalarCount));
  std::memset(advancedCount, 0, sizeof(advancedCount));
  std::memset(vectorCount,   0, sizeof(vectorCount));

  MilliClock total;
#if X_PTRSIZE == XA_PTRSIZE64
  uint64 numStatements        = 0;
  #define FCNT FU64
#else
  uint32 numStatements        = 0;
  #define FCNT FU32
#endif
  totalTime                   = 0;
  nativeTime                  = 0;
  functionCalls               = 0;
  nativeFunctionCalls         = 0;
  branchCalls                 = 0;
  conditionalBranchesTaken    = 0;
  conditionalBranchesNotTaken = 0;
  unconditionalBranches       = 0;
  status                      = VMDefs::RUNNING;

#define CLASS DebuggingInterpreter
#define COUNT_STATEMENTS ++numStatements;
#define DEBUG_RETURN if (vm->debugFlags & FLAG_LOG_CALLS) { debuglog(LOG_INFO, "Returning"); }
#define DEBUG_BRANCH_UNCONDITIONAL ++unconditionalBranches;
#define DEBUG_BRANCH_TAKEN         ++conditionalBranchesTaken;
#define DEBUG_BRANCH_NOT_TAKEN     else { ++conditionalBranchesNotTaken; }
#define DEBUG_SCALAR_COUNT         ++scalarCount[op>>8];

#if _VM_INTERPRETER == _VM_INTERPRETER_SWITCH_CASE
  #include "include/vm_interpreter_switch_case_impl.hpp"
#elif _VM_INTERPRETER == _VM_INTERPRETER_CUSTOM
  #include "include/vm_interpreter_custom_impl.hpp"
#endif

#undef CLASS
#undef COUNT_STATEMENTS
#undef DEBUG_RETURN
#undef DEBUG_SCALAR_COUNT

  totalTime = total.elapsedFrac();
  totalStatements     = numStatements;
  debuglog(LOG_INFO, "Executed %" FCNT " statements\n", numStatements);
  float64 virtualTime = totalTime - nativeTime;
  float64 mips        = (0.001*numStatements)/virtualTime;
  debuglog(
    LOG_INFO,
    "Total: %.3f ms, native: %.3f ms, virtual: %.3f ms, %.3f MIPS",
    totalTime, nativeTime, virtualTime, mips
  );

}
