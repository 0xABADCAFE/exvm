// Advanced Opcode names for debugging
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

  "xform_vec2.f32 rS, rM, rD, rC", //_M3X3_V2F32, // transform a set of vec2f using a 4x4 matrix

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

  "xform_vec3.f32 rS, rM, rD, rC", //_M4X4_V3F32, // transform a set of vec3f using a 4x4 matrix

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

  "xform_vec2.f64 rS, rM, rD, rC", //_M3X3_V2F64, // transform a set of vec2d using a 4x4 matrix

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

  "xform_vec3.f64 rS, rM, rD, rC", //_M4X4_V3F64, // transform a set of vec3d using a 4x4 matrix
