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

#ifndef _VM_DEF_VECTOR_OPCODES_L0_HPP_
#define _VM_DEF_VECTOR_OPCODES_L0_HPP_

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //
  // Implementation Level 0 : Single Vector functions (vector is destination only)
  //
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // Scalar to Vector Fill
  //
  // vd[i] = x
  _VFILL_8,
  _VFILL_16,
  _VFILL_32,

  // Scalar minimum in vector v = min(vs[])
  _VSMIN_U8,
  _VSMIN_U16,
  _VSMIN_U32,
  _VSMIN_S8,
  _VSMIN_S16,
  _VSMIN_S32,

  // Scalar maximum in vector v = max(vs[])
  _VSMAX_U8,
  _VSMAX_U16,
  _VSMAX_U32,
  _VSMAX_S8,
  _VSMAX_S16,
  _VSMAX_S32,

  // Scalar sum v = sum(vs[])
  _VSSUM_U8,
  _VSSUM_U16,
  _VSSUM_U32,
  _VSSUM_S8,
  _VSSUM_S16,
  _VSSUM_S32,

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //
  // Implementation Level 0 : Two Vector functions (one vector source, one vector destination)
  //
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // Vector negate (integer)
  //
  // vd[i] = -vs[i]
  _VNEG_S8,
  _VNEG_S16,
  _VNEG_S32,

  // Vector absolute (signed integer)
  //
  // vd[i] = |vs[i]|
  _VABS_S8,
  _VABS_S16,
  _VABS_S32,

  // Vector inverse (int)
  //
  // vd[i] = ~vs[i]
  _VINV_8,

  // Scalar on Vector addition (integer)
  //
  // vd[i] = vs[i] + x
  _VSADD_I8,
  _VSADD_I16,
  _VSADD_I32,

  // Scalar on Vector addition (unsigned integer, saturated)
  //
  // vd[i] = vs[i] + x
  _VSADDS_U8,
  _VSADDS_U16,
  _VSADDS_U32,

  // Scalar on Vector addition (signed integer, saturated)
  //
  // vd[i] = vs[i] + x
  _VSADDS_S8,
  _VSADDS_S16,
  _VSADDS_S32,

  // Scalar on Vector subtraction (integer)
  //
  // vd[i] = vs[i] + x
  _VSSUB_I8,
  _VSSUB_I16,
  _VSSUB_I32,

  // Scalar on Vector subtraction (unsigned integer, saturated)
  //
  // vd[i] = vs[i] - x
  _VSSUBS_U8,
  _VSSUBS_U16,
  _VSSUBS_U32,

  // Scalar on Vector subtraction (signed integer, saturated)
  //
  // vd[i] = vs[i] - x
  _VSSUBS_S8,
  _VSSUBS_S16,
  _VSSUBS_S32,

  // Scalar Scalar Vector multiply (unsigned integer)
  //
  // vd[i] = vs[i] * x
  _VSMUL_U8,
  _VSMUL_U16,
  _VSMUL_U32,

  // Scalar on Vector multiply (signed integer)
  //
  // vd[i] = vs[i] * x
  _VSMUL_S8,
  _VSMUL_S16,
  _VSMUL_S32,

  // Scalar on Vector multiply (unsigned integer, saturated)
  //
  // vd[i] = vs[i] * x
  _VSMULS_U8,
  _VSMULS_U16,
  _VSMULS_U32,

  // Scalar on Vector multiply (signed integer, saturated)
  //
  // vd[i] = vs[i] * x
  _VSMULS_S8,
  _VSMULS_S16,
  _VSMULS_S32,

  // Scalar on Vector division (unsigned integer)
  //
  // vd[i] = vs[i] / x
  _VSDIV_U8,
  _VSDIV_U16,
  _VSDIV_U32,

  // Scalar on Vector division (signed integer)
  //
  // vd[i] = vs[i] / x
  _VSDIV_S8,
  _VSDIV_S16,
  _VSDIV_S32,

  // Scalar on Vector division (signed integer, saturated)
  //
  // vd[i] = vs[i] / x
  _VSDIVS_S8,
  _VSDIVS_S16,
  _VSDIVS_S32,

  // Scalar on Vector modulus (unsigned integer)
  //
  // vd[i] = vs[i] % x
  _VSMOD_U8,
  _VSMOD_U16,
  _VSMOD_U32,

  // Scalar on Vector modulus (signed integer)
  //
  // vd[i] = vs[i] % x
  _VSMOD_S8,
  _VSMOD_S16,
  _VSMOD_S32,

  // Scalar on Vector bitwise AND
  //
  // vd[i] = vs[i] & x
  _VSAND_8,
  _VSAND_16,
  _VSAND_32,

  // Scalar on Vector bitwise OR
  //
  // vd[i] = vs[i] | x
  _VSOR_8,
  _VSOR_16,
  _VSOR_32,

  // Scalar on Vector XOR
  //
  // vd[i] = vs[i] ^ x
  _VSXOR_8,
  _VSXOR_16,
  _VSXOR_32,

  // Scalar on Vector logical shift left
  //
  // vd[i] = vs[i] << x
  _VSLSL_8,
  _VSLSL_16,
  _VSLSL_32,

  // Scalar on Vector logical shift right
  //
  // vd[i] = vs[i] >> x
  _VSLSR_8,
  _VSLSR_16,
  _VSLSR_32,

  // Scalar on Vector arithmetic shift left
  //
  // vd[i] = vs[i] << x
  _VSASL_8,
  _VSASL_16,
  _VSASL_32,

  // Scalar on Vector arithmetic shift right
  //
  // vd[i] = vs[i] >> x
  _VSASR_8,
  _VSASR_16,
  _VSASR_32,

  // Scalar on Vector rotate left
  //
  // vd[i] = vs[i] <<@ x
  _VSROL_8,
  _VSROL_16,
  _VSROL_32,

  // Scalar on Vector rotate right
  //
  // vd[i] = vs[i] @>> x
  _VSROR_8,
  _VSROR_16,
  _VSROR_32,

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //
  // Three vector functions (two vector sources, one vector destination)
  //
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // Vector addition (integer)
  //
  // vd[i] = va[i] + vb[i]
  _VADD_I8,
  _VADD_I16,
  _VADD_I32,

  // Vector addition (unsigned integer, saturated)
  //
  // vd[i] = va[i] + vb[i]
  _VADDS_U8,
  _VADDS_U16,
  _VADDS_U32,

  // Vector addition (signed integer, saturated)
  //
  // vd[i] = va[i] + vb[i]
  _VADDS_S8,
  _VADDS_S16,
  _VADDS_S32,

  // Vector subtraction (integer)
  //
  // vd[i] = va[i] - vb[i]
  _VSUB_I8,
  _VSUB_I16,
  _VSUB_I32,


  // Vector subtraction (unsigned integer, saturated)
  //
  // vd[i] = va[i] - vb[i]
  _VSUBS_U8,
  _VSUBS_U16,
  _VSUBS_U32,

  // Vector subtraction (signed integer, saturated)
  //
  // vd[i] = va[i] - vb[i]
  _VSUBS_S8,
  _VSUBS_S16,
  _VSUBS_S32,

  // Vector multiply (unsigned integer)
  //
  // vd[i] = va[i] * vb[i]
  _VMUL_U8,
  _VMUL_U16,
  _VMUL_U32,

  // Vector multiply (signed integer)
  //
  // vd[i] = va[i] * vb[i]
  _VMUL_S8,
  _VMUL_S16,
  _VMUL_S32,

  // Vector multiply (unsigned integer, saturated)
  //
  // vd[i] = va[i] * vb[i]
  _VMULS_U8,
  _VMULS_U16,
  _VMULS_U32,

  // Vector multiply (signed integer, saturated)
  //
  // vd[i] = va[i] * vb[i]
  _VMULS_S8,
  _VMULS_S16,
  _VMULS_S32,

  // Vector division (unsigned integer)
  //
  // vd[i] = va[i] / vb[i]
  _VDIV_U8,
  _VDIV_U16,
  _VDIV_U32,

  // Vector division (signed integer)
  //
  // vd[i] = va[i] / vb[i]
  _VDIV_S8,
  _VDIV_S16,
  _VDIV_S32,

  // Vector division (signed integer, saturated)
  //
  // vd[i] = va[i] / vb[i]
  _VDIVS_S8,
  _VDIVS_S16,
  _VDIVS_S32,

  // Vector modulus (unsigned integer)
  //
  // vd[i] = va[i] % vb[i]
  _VMOD_U8,
  _VMOD_U16,
  _VMOD_U32,

  // Vector modulus (signed integer)
  //
  // vd[i] = va[i] % vb[i]
  _VMOD_S8,
  _VMOD_S16,
  _VMOD_S32,

  // Vector AND/OR/XOR - All operate at a byte size since there is no behavioural differences for other word sizes.
  //
  // vd[i] = va[i] &|^ vb[i]
  _VAND_8,
  _VOR_8,
  _VXOR_8, // op_vec_vbitwise_impl.hpp

  // Vector mapping - convert an array of indexed values into values
  //
  // vd[i] = vm[vs[i]]
  _VMAP_8_16,
  _VMAP_8_32,
  _VMAP_16_32,

#endif

