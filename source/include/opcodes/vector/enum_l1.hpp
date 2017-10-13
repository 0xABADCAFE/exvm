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

#ifndef _VM_DEF_VECTOR_OPCODES_L1_HPP_
#define _VM_DEF_VECTOR_OPCODES_L1_HPP_

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //
  // Implementation Level 1 : Single Vector functions (vector is destination only)
  //
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // Scalar to Vector Fill
  //
  // vd[i] = x
  _VSMIN_F32,

  // Scalar maximum in vector v = max(vs[])
  _VSMAX_F32,

  // Scalar sum v = sum(vs[])
  _VSSUM_F32,

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //
  // Implementation Level 1 : Two Vector functions (one vector source, one vector destination)
  //
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // Vector negate (flaot)
  //
  // vd[i] = -vs[i]
  _VNEG_F32,

  // Vector absolute (float)
  //
  // vd[i] = abs(vs[i])
  _VABS_F32,

  // Scalar on Vector addition (float)
  //
  // vd[i] = vs[i] + x
  _VSADD_F32,

  // Scalar on Vector subtraction (float)
  //
  // vd[i] = vs[i] + x
  _VSSUB_F32,

  // Scalar on Vector multiply (float)
  //
  // vd[i] = vs[i] * x
  _VSMUL_F32,

  // Scalar on Vector division (float)
  //
  // vd[i] = vs[i] / x
  _VSDIV_F32,

  // Scalar on Vector modulus (float)
  //
  // vd[i] = vs[i] % x
  _VSMOD_F32,

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //
  // Implementation Level 1 : Three vector functions (two vector sources, one vector destination)
  //
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // Vector addition (float)
  //
  // vd[i] = va[i] + vb[i]
  _VADD_F32,

  // Vector subtraction (float)
  //
  // vd[i] = va[i] - vb[i]
  _VSUB_F32,

  // Vector multiply (float)
  //
  // vd[i] = va[i] * vb[i]
  _VMUL_F32,

  // Vector division (float)
  //
  // vd[i] = va[i] / vb[i]
  _VDIV_F32,

  // Vector modulus (float)
  //
  // vd[i] = va[i] % vb[i]
  _VMOD_F32,

  // Vector multiply-accumulate
  _VMAC_F32,

#endif

