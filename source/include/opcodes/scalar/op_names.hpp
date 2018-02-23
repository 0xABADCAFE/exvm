// Scalar Opcode names for debugging
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
