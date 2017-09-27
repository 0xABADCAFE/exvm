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

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //
  // Single Vector functions (vector is destination only)
  //
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // Scalar to Vector Fill
  //
  // vd[i] = x

  _VFILL_8,  _VFILL_16,  _VFILL_32,  _VFILL_64, // op_vec_fill_impl.hpp

  // Scalar minimum in vector v = min(vs[])
  _VSMIN_U8, _VSMIN_U16, _VSMIN_U32, _VSMIN_U64, // op_vec_smin_impl.hpp
  _VSMIN_S8, _VSMIN_S16, _VSMIN_S32, _VSMIN_S64,
  _VSMIN_F32,_VSMIN_F64,

  // Scalar maximum in vector v = max(vs[])
  _VSMAX_U8, _VSMAX_U16, _VSMAX_U32, _VSMAX_U64, // op_vec_smax_impl.hpp
  _VSMAX_S8, _VSMAX_S16, _VSMAX_S32, _VSMAX_S64,
  _VSMAX_F32,_VSMAX_F64,

  // Scalar sum v = sum(vs[])
  _VSSUM_U8, _VSSUM_U16, _VSSUM_U32, _VSSUM_U64, // op_vec_ssum_impl.hpp
  _VSSUM_S8, _VSSUM_S16, _VSSUM_S32, _VSSUM_S64,
  _VSSUM_F32,_VSSUM_F64,

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

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // Vector multiply-accumulate

  _VMAC_F32, _VMAC_F64,

  MAX_VEC
} VectorOp;

#endif

