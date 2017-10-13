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

#ifndef _VM_DEF_VECTOR_OPCODES_L2_HPP_
#define _VM_DEF_VECTOR_OPCODES_L2_HPP_


  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //
  // Implementation Level 2 : Single Vector functions (vector is destination only)
  //
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // Scalar to Vector Fill
  //
  // vd[i] = x
  _VFILL_64,

  // Scalar minimum in vector v = min(vs[])
  _VSMIN_U64,
  _VSMIN_S64,
  _VSMIN_F64,

  // Scalar maximum in vector v = max(vs[])
  _VSMAX_U64,
  _VSMAX_S64,
  _VSMAX_F64,

  // Scalar sum v = sum(vs[])
  _VSSUM_U64,
  _VSSUM_S64,
  _VSSUM_F64,

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //
  // Implementation Level 2 : Two Vector functions (one vector source, one vector destination)
  //
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // Vector negate (integer)
  //
  // vd[i] = -vs[i]
  _VNEG_S64,

  // Vector negate (flaot)
  //
  // vd[i] = -vs[i]
  _VNEG_F64,

  // Vector absolute (signed integer)
  //
  // vd[i] = |vs[i]|
  _VABS_S64,

  // Vector absolute (float)
  //
  // vd[i] = abs(vs[i])
  _VABS_F64,

  // Scalar on Vector addition (integer)
  //
  // vd[i] = vs[i] + x
  _VSADD_I64,

  // Scalar on Vector addition (float)
  //
  // vd[i] = vs[i] + x
  _VSADD_F64,

  // Scalar on Vector addition (unsigned integer, saturated)
  //
  // vd[i] = vs[i] + x
  _VSADDS_U64,

  // Scalar on Vector addition (signed integer, saturated)
  //
  // vd[i] = vs[i] + x
  _VSADDS_S64,

  // Scalar on Vector subtraction (integer)
  //
  // vd[i] = vs[i] + x
  _VSSUB_I64,

  // Scalar on Vector subtraction (float)
  //
  // vd[i] = vs[i] + x
  _VSSUB_F64,

  // Scalar on Vector subtraction (unsigned integer, saturated)
  //
  // vd[i] = vs[i] - x
  _VSSUBS_U64,

  // Scalar on Vector subtraction (signed integer, saturated)
  //
  // vd[i] = vs[i] - x
  _VSSUBS_S64,

  // Scalar Scalar Vector multiply (unsigned integer)
  //
  // vd[i] = vs[i] * x
  _VSMUL_U64,

  // Scalar on Vector multiply (signed integer)
  //
  // vd[i] = vs[i] * x
  _VSMUL_S64,

  // Scalar on Vector multiply (float)
  //
  // vd[i] = vs[i] * x
  _VSMUL_F64,

  // Scalar on Vector multiply (unsigned integer, saturated)
  //
  // vd[i] = vs[i] * x
  _VSMULS_U64,

  // Scalar on Vector multiply (signed integer, saturated)
  //
  // vd[i] = vs[i] * x
  _VSMULS_S64,

  // Scalar on Vector division (unsigned integer)
  //
  // vd[i] = vs[i] / x
  _VSDIV_U64,

  // Scalar on Vector division (signed integer)
  //
  // vd[i] = vs[i] / x
  _VSDIV_S64,

  // Scalar on Vector division (float)
  //
  // vd[i] = vs[i] / x
  _VSDIV_F64,

  // Scalar on Vector division (signed integer, saturated)
  //
  // vd[i] = vs[i] / x
  _VSDIVS_S64,

  // Scalar on Vector modulus (unsigned integer)
  //
  // vd[i] = vs[i] % x
  _VSMOD_U64,

  // Scalar on Vector modulus (signed integer)
  //
  // vd[i] = vs[i] % x
  _VSMOD_S64,

  // Scalar on Vector modulus (float)
  //
  // vd[i] = vs[i] % x
  _VSMOD_F64,

  // Scalar on Vector bitwise AND
  //
  // vd[i] = vs[i] & x
  _VSAND_64,

  // Scalar on Vector bitwise OR
  //
  // vd[i] = vs[i] | x
  _VSOR_64,

  // Scalar on Vector XOR
  //
  // vd[i] = vs[i] ^ x
  _VSXOR_64,

  // Scalar on Vector logical shift left
  //
  // vd[i] = vs[i] << x
  _VSLSL_64,

  // Scalar on Vector logical shift right
  //
  // vd[i] = vs[i] >> x
  _VSLSR_64,

  // Scalar on Vector arithmetic shift left
  //
  // vd[i] = vs[i] << x
  _VSASL_64,

  // Scalar on Vector arithmetic shift right
  //
  // vd[i] = vs[i] >> x
  _VSASR_64,

  // Scalar on Vector rotate left
  //
  // vd[i] = vs[i] <<@ x
  _VSROL_64,

  // Scalar on Vector rotate right
  //
  // vd[i] = vs[i] @>> x
  _VSROR_64,

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //
  // Implementation Level 2 : Three vector functions (two vector sources, one vector destination)
  //
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // Vector addition (integer)
  //
  // vd[i] = va[i] + vb[i]
  _VADD_I64,

  // Vector addition (float)
  //
  // vd[i] = va[i] + vb[i]
  _VADD_F64,

  // Vector addition (unsigned integer, saturated)
  //
  // vd[i] = va[i] + vb[i]
  _VADDS_U64,

  // Vector addition (signed integer, saturated)
  //
  // vd[i] = va[i] + vb[i]
  _VADDS_S64,

  // Vector subtraction (integer)
  //
  // vd[i] = va[i] - vb[i]
  _VSUB_I64,

  // Vector subtraction (float)
  //
  // vd[i] = va[i] - vb[i]
  _VSUB_F64,

  // Vector subtraction (unsigned integer, saturated)
  //
  // vd[i] = va[i] - vb[i]
  _VSUBS_U64,

  // Vector subtraction (signed integer, saturated)
  //
  // vd[i] = va[i] - vb[i]
  _VSUBS_S64,

  // Vector multiply (unsigned integer)
  //
  // vd[i] = va[i] * vb[i]
  _VMUL_U64,

  // Vector multiply (signed integer)
  //
  // vd[i] = va[i] * vb[i]
  _VMUL_S64,

  // Vector multiply (float)
  //
  // vd[i] = va[i] * vb[i]
  _VMUL_F64,

  // Vector multiply (unsigned integer, saturated)
  //
  // vd[i] = va[i] * vb[i]
  _VMULS_U64,

  // Vector multiply (signed integer, saturated)
  //
  // vd[i] = va[i] * vb[i]
  _VMULS_S64,

  // Vector division (unsigned integer)
  //
  // vd[i] = va[i] / vb[i]
  _VDIV_U64,

  // Vector division (signed integer)
  //
  // vd[i] = va[i] / vb[i]
  _VDIV_S64,

  // Vector division (float)
  //
  // vd[i] = va[i] / vb[i]
  _VDIV_F64,

  // Vector division (signed integer, saturated)
  //
  // vd[i] = va[i] / vb[i]
  _VDIVS_S64,

  // Vector modulus (unsigned integer)
  //
  // vd[i] = va[i] % vb[i]
  _VMOD_U64,

  // Vector modulus (signed integer)
  //
  // vd[i] = va[i] % vb[i]
  _VMOD_S64,

  // Vector modulus (float)
  //
  // vd[i] = va[i] % vb[i]
  _VMOD_F64,

  // Vector mapping - convert an array of indexed values into values
  //
  // vd[i] = vm[vs[i]]
  _VMAP_8_64,
  _VMAP_16_64,

  // Vector multiply-accumulate
  _VMAC_F64,


#endif

