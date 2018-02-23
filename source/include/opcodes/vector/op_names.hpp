// Vector Opcode names for debugging

  // LEVEL 0

  // Scalar to Vector Fill
  //
  // vd[i] = x
  "vfill.8  rS, rD, rC", //_VFILL_8,
  "vfill.16 rS, rD, rC", //_VFILL_16,
  "vfill.32 rS, rD, rC", //_VFILL_32,

  // Scalar minimum in vector v = min(vs[])
  "vsmin.u8 ", //_VSMIN_U8,
  "vsmin.u16", //_VSMIN_U16,
  "vsmin.u32", //_VSMIN_U32,
  "vsmin.s8", //_VSMIN_S8,
  "vsmin.s16", //_VSMIN_S16,
  "vsmin.s32", //_VSMIN_S32,

  // Scalar maximum in vector v = max(vs[])
  "vsmax.u8", //_VSMAX_U8,
  "vsmax.u16", //_VSMAX_U16,
  "vsmax.u32", //_VSMAX_U32,
  "vsmax.s8", //_VSMAX_S8,
  "vsmax.s16", //_VSMAX_S16,
  "vsmax.s32", //_VSMAX_S32,

  // Scalar sum v = sum(vs[])
  "vssum.u8", //_VSSUM_U8,
  "vssum.u16", //_VSSUM_U16,
  "vssum.u32", //_VSSUM_U32,
  "vssum.s8", //_VSSUM_S8,
  "vssum.s16", //_VSSUM_S16,
  "vssum.s32", //_VSSUM_S32,

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //
  // Implementation Level 0 : Two Vector functions (one vector source, one vector destination)
  //
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // Vector negate (integer)
  //
  // vd[i] = -vs[i]
  "vneg.s8", //_VNEG_S8,
  "vneg.s16", //_VNEG_S16,
  "vneg.s32", //_VNEG_S32,

  // Vector absolute (signed integer)
  //
  // vd[i] = |vs[i]|
  "vabs.s8", //_VABS_S8,
  "vabs.s16", //_VABS_S16,
  "vabs.s32", //_VABS_S32,

  // Vector inverse (int)
  //
  // vd[i] = ~vs[i]
  "vinv.8", //_VINV_8,

  // Scalar on Vector addition (integer)
  //
  // vd[i] = vs[i] + x
  "vsadd.i8", //_VSADD_I8,
  "vsadd.i16", //_VSADD_I16,
  "vsadd.i32", //_VSADD_I32,

  // Scalar on Vector addition (unsigned integer, saturated)
  //
  // vd[i] = vs[i] + x
  "vsadds.u8", //_VSADDS_U8,
  "vsadds.u16", //_VSADDS_U16,
  "vsadds.u32", //_VSADDS_U32,

  // Scalar on Vector addition (signed integer, saturated)
  //
  // vd[i] = vs[i] + x
  "vsadds.u8", //_VSADDS_S8,
  "vsadds.u16", //_VSADDS_S16,
  "vsadds.u32", //_VSADDS_S32,

  // Scalar on Vector subtraction (integer)
  //
  // vd[i] = vs[i] + x
  "vssub.i8", //_VSSUB_I8,
  "vssub.i16", //_VSSUB_I16,
  "vssub.i32", //_VSSUB_I32,

  // Scalar on Vector subtraction (unsigned integer, saturated)
  //
  // vd[i] = vs[i] - x
  "vssubs.u8", //_VSSUBS_U8,
  "vssubs.u16", //_VSSUBS_U16,
  "vssubs.u32", //_VSSUBS_U32,

  // Scalar on Vector subtraction (signed integer, saturated)
  //
  // vd[i] = vs[i] - x
  "vssubs.s8", //_VSSUBS_S8,
  "vssubs.s16", //_VSSUBS_S16,
  "vssubs.s32", //_VSSUBS_S32,

  // Scalar Scalar Vector multiply (unsigned integer)
  //
  // vd[i] = vs[i] * x
  "vsmul.u8", //_VSMUL_U8,
  "vsmul.u16", //_VSMUL_U16,
  "vsmul.u32", //_VSMUL_U32,

  // Scalar on Vector multiply (signed integer)
  //
  // vd[i] = vs[i] * x
  "vsmul.s8", //_VSMUL_S8,
  "vsmul.s16", //_VSMUL_S16,
  "vsmul.s32", //_VSMUL_S32,

  // Scalar on Vector multiply (unsigned integer, saturated)
  //
  // vd[i] = vs[i] * x
  "vsmuls.u8", //_VSMULS_U8,
  "vsmuls.u16", //_VSMULS_U16,
  "vsmuls.u32", //_VSMULS_U32,

  // Scalar on Vector multiply (signed integer, saturated)
  //
  // vd[i] = vs[i] * x
  "vsmuls.s8", //_VSMULS_S8,
  "vsmuls.s16", //_VSMULS_S16,
  "vsmuls.s32", //_VSMULS_S32,

  // Scalar on Vector division (unsigned integer)
  //
  // vd[i] = vs[i] / x
  "vsdiv.u8", //_VSDIV_U8,
  "vsdiv.u16", //_VSDIV_U16,
  "vsdiv.u32", //_VSDIV_U32,

  // Scalar on Vector division (signed integer)
  //
  // vd[i] = vs[i] / x
  "vsdiv.s8", //_VSDIV_S8,
  "vsdiv.s16", //_VSDIV_S16,
  "vsdiv.s32", //_VSDIV_S32,

  // Scalar on Vector division (signed integer, saturated)
  //
  // vd[i] = vs[i] / x
  "vsdivs.s8", //_VSDIVS_S8,
  "vsdivs.s16", //_VSDIVS_S16,
  "vsdivs.s32", //_VSDIVS_S32,

  // Scalar on Vector modulus (unsigned integer)
  //
  // vd[i] = vs[i] % x
  "vsmod.u8", //_VSMOD_U8,
  "vsmod.u16", //_VSMOD_U16,
  "vsmod.u32", //_VSMOD_U32,

  // Scalar on Vector modulus (signed integer)
  //
  // vd[i] = vs[i] % x
  "vsmod.s8", //_VSMOD_S8,
  "vsmod.s16", //_VSMOD_S16,
  "vsmod.s32", //_VSMOD_S32,

  // Scalar on Vector bitwise AND
  //
  // vd[i] = vs[i] & x
  "vsand.8", //_VSAND_8,
  "vsand.16", //_VSAND_16,
  "vsand.32", //_VSAND_32,

  // Scalar on Vector bitwise OR
  //
  // vd[i] = vs[i] | x
  "vsor.8", //_VSOR_8,
  "vsor.16", //_VSOR_16,
  "vsor.32", //_VSOR_32,

  // Scalar on Vector XOR
  //
  // vd[i] = vs[i] ^ x
  "vsxor.8", //_VSXOR_8,
  "vsxor.16", //_VSXOR_16,
  "vsxor.32", //_VSXOR_32,

  // Scalar on Vector logical shift left
  //
  // vd[i] = vs[i] << x
  "vslsl.8", //_VSLSL_8,
  "vslsl.16", //_VSLSL_16,
  "vslsl.32", //_VSLSL_32,

  // Scalar on Vector logical shift right
  //
  // vd[i] = vs[i] >> x
  "vslsr.8", //_VSLSR_8,
  "vslsr.16", //_VSLSR_16,
  "vslsr.32", //_VSLSR_32,

  // Scalar on Vector arithmetic shift left
  //
  // vd[i] = vs[i] << x
  "vsasl.8", //_VSASL_8,
  "vsasl.16", //_VSASL_16,
  "vsasl.32", //_VSASL_32,

  // Scalar on Vector arithmetic shift right
  //
  // vd[i] = vs[i] >> x
  "vsasr.8", //_VSASR_8,
  "vsasr.16", //_VSASR_16,
  "vsasr.32", //_VSASR_32,

  // Scalar on Vector rotate left
  //
  // vd[i] = vs[i] <<@ x
  "vsrol.8", //_VSROL_8,
  "vsrol.16", //_VSROL_16,
  "vsrol.32", //_VSROL_32,

  // Scalar on Vector rotate right
  //
  // vd[i] = vs[i] @>> x
  "vsror.8", //_VSROR_8,
  "vsror.16", //_VSROR_16,
  "vsror.32", //_VSROR_32,

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //
  // Three vector functions (two vector sources, one vector destination)
  //
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // Vector addition (integer)
  //
  // vd[i] = va[i] + vb[i]
  "vadd.i8", //_VADD_I8,
  "vadd.i16", //_VADD_I16,
  "vadd.i32", //_VADD_I32,

  // Vector addition (unsigned integer, saturated)
  //
  // vd[i] = va[i] + vb[i]
  "vadds.u8", //_VADDS_U8,
  "vadds.u16", //_VADDS_U16,
  "vadds.u32", //_VADDS_U32,

  // Vector addition (signed integer, saturated)
  //
  // vd[i] = va[i] + vb[i]
  "vadds.s8", //_VADDS_S8,
  "vadds.s16", //_VADDS_S16,
  "vadds.s32", //_VADDS_S32,

  // Vector subtraction (integer)
  //
  // vd[i] = va[i] - vb[i]
  "vsub.i8", //_VSUB_I8,
  "vsub.i16", //_VSUB_I16,
  "vsub.i32", //_VSUB_I32,


  // Vector subtraction (unsigned integer, saturated)
  //
  // vd[i] = va[i] - vb[i]
  "vsubs.u8", //_VSUBS_U8,
  "vsubs.u16", //_VSUBS_U16,
  "vsubs.u32", //_VSUBS_U32,

  // Vector subtraction (signed integer, saturated)
  //
  // vd[i] = va[i] - vb[i]
  "vsubs.s8", //_VSUBS_S8,
  "vsubs.s16", //_VSUBS_S16,
  "vsubs.s32", //_VSUBS_S32,

  // Vector multiply (unsigned integer)
  //
  // vd[i] = va[i] * vb[i]
  "vmul.u8", //_VMUL_U8,
  "vmul.u16", //_VMUL_U16,
  "vmul.u32", //_VMUL_U32,

  // Vector multiply (signed integer)
  //
  // vd[i] = va[i] * vb[i]
  "vmul.s8", //_VMUL_S8,
  "vmul.s16", //_VMUL_S16,
  "vmul.s32", //_VMUL_S32,

  // Vector multiply (unsigned integer, saturated)
  //
  // vd[i] = va[i] * vb[i]
  "vmuls.u8", //_VMULS_U8,
  "vmuls.u16", //_VMULS_U16,
  "vmuls.u32", //_VMULS_U32,

  // Vector multiply (signed integer, saturated)
  //
  // vd[i] = va[i] * vb[i]
  "vmuls.s8", //_VMULS_S8,
  "vmuls.s16", //_VMULS_S16,
  "vmuls.s32", //_VMULS_S32,

  // Vector division (unsigned integer)
  //
  // vd[i] = va[i] / vb[i]
  "vdiv.u8", //_VDIV_U8,
  "vdiv.u16", //_VDIV_U16,
  "vdiv.u32", //_VDIV_U32,

  // Vector division (signed integer)
  //
  // vd[i] = va[i] / vb[i]
  "vdiv.s8", //_VDIV_S8,
  "vdiv.s16", //_VDIV_S16,
  "vdiv.s32", //_VDIV_S32,

  // Vector division (signed integer, saturated)
  //
  // vd[i] = va[i] / vb[i]
  "vdivs.s8", //_VDIVS_S8,
  "vdivs.s16", //_VDIVS_S16,
  "vdivs.s32", //_VDIVS_S32,

  // Vector modulus (unsigned integer)
  //
  // vd[i] = va[i] % vb[i]
  "vmod.u8", //_VMOD_U8,
  "vmod.u16", //_VMOD_U16,
  "vmod.u32", //_VMOD_U32,

  // Vector modulus (signed integer)
  //
  // vd[i] = va[i] % vb[i]
  "vmod.s8", //_VMOD_S8,
  "vmod.s16", //_VMOD_S16,
  "vmod.s32", //_VMOD_S32,

  // Vector AND/OR/XOR - All operate at a byte size since there is no behavioural differences for other word sizes.
  //
  // vd[i] = va[i] &|^ vb[i]
  "vand.8", //_VAND_8,
  "vor.8", //_VOR_8,
  "vxor.8", //_VXOR_8, // op_vec_vbitwise_impl.hpp

  // Vector mapping - convert an array of indexed values into values
  //
  // vd[i] = vm[vs[i]]
  "vmap8.16", //_VMAP_8_16,
  "vmap8.32", //_VMAP_8_32,
  "vmap16.32", //_VMAP_16_32,

  // LEVEL 1


  // Scalar to Vector Fill
  //
  // vd[i] = x
  "vsmin.f32", //_VSMIN_F32,

  // Scalar maximum in vector v = max(vs[])
  "vsmax.f32", //_VSMAX_F32,

  // Scalar sum v = sum(vs[])
  "vssum.f32", //_VSSUM_F32,

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //
  // Implementation Level 1 : Two Vector functions (one vector source, one vector destination)
  //
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // Vector negate (flaot)
  //
  // vd[i] = -vs[i]
  "vneg.f32", //_VNEG_F32,

  // Vector absolute (float)
  //
  // vd[i] = abs(vs[i])
  "vabs.f32", //_VABS_F32,

  // Scalar on Vector addition (float)
  //
  // vd[i] = vs[i] + x
  "vsadd.f32", //_VSADD_F32,

  // Scalar on Vector subtraction (float)
  //
  // vd[i] = vs[i] + x
  "vssub.f32", //_VSSUB_F32,

  // Scalar on Vector multiply (float)
  //
  // vd[i] = vs[i] * x
  "vsmul.f32", //_VSMUL_F32,

  // Scalar on Vector division (float)
  //
  // vd[i] = vs[i] / x
  "vsdiv.f32", //_VSDIV_F32,

  // Scalar on Vector modulus (float)
  //
  // vd[i] = vs[i] % x
  "vsmod.f32", //_VSMOD_F32,

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //
  // Implementation Level 1 : Three vector functions (two vector sources, one vector destination)
  //
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // Vector addition (float)
  //
  // vd[i] = va[i] + vb[i]
  "vadd.f32", //_VADD_F32,

  // Vector subtraction (float)
  //
  // vd[i] = va[i] - vb[i]
  "vsub.f32", //_VSUB_F32,

  // Vector multiply (float)
  //
  // vd[i] = va[i] * vb[i]
  "vmul.f32", //_VMUL_F32,

  // Vector division (float)
  //
  // vd[i] = va[i] / vb[i]
  "vdiv.f32", //_VDIV_F32,

  // Vector modulus (float)
  //
  // vd[i] = va[i] % vb[i]
  "vmod.f32", //_VMOD_F32,

  // Vector multiply-accumulate
  "vmac.f32", //_VMAC_F32,


  // Scalar to Vector Fill
  //
  // vd[i] = x
  "vfill.64", //_VFILL_64,

  // Scalar minimum in vector v = min(vs[])
  "vsmin.u64", //_VSMIN_U64,
  "vsmin.s64", //_VSMIN_S64,
  "vsmin.f64", //_VSMIN_F64,

  // Scalar maximum in vector v = max(vs[])
  "vsmax.u64", //_VSMAX_U64,
  "vsmax.s64", //_VSMAX_S64,
  "vsmax.f64", //_VSMAX_F64,

  // Scalar sum v = sum(vs[])
  "vssum.u64", //_VSSUM_U64,
  "vssum.s64", //_VSSUM_S64,
  "vssum.f64", //_VSSUM_F64,

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //
  // Implementation Level 2 : Two Vector functions (one vector source, one vector destination)
  //
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // Vector negate (integer)
  //
  // vd[i] = -vs[i]
  "vneg.s64", //_VNEG_S64,

  // Vector negate (flaot)
  //
  // vd[i] = -vs[i]
  "vneg.f64", //_VNEG_F64,

  // Vector absolute (signed integer)
  //
  // vd[i] = |vs[i]|
  "vabs.s64", //_VABS_S64,

  // Vector absolute (float)
  //
  // vd[i] = abs(vs[i])
  "vabs.f64", //_VABS_F64,

  // Scalar on Vector addition (integer)
  //
  // vd[i] = vs[i] + x
  "vsadd.i64", //_VSADD_I64,

  // Scalar on Vector addition (float)
  //
  // vd[i] = vs[i] + x
  "vsadd.f64", //_VSADD_F64,

  // Scalar on Vector addition (unsigned integer, saturated)
  //
  // vd[i] = vs[i] + x
  "vsadds.u64", //_VSADDS_U64,

  // Scalar on Vector addition (signed integer, saturated)
  //
  // vd[i] = vs[i] + x
  "vsadds.s64", //_VSADDS_S64,

  // Scalar on Vector subtraction (integer)
  //
  // vd[i] = vs[i] + x
  "vssub.i64", //_VSSUB_I64,

  // Scalar on Vector subtraction (float)
  //
  // vd[i] = vs[i] + x
  "vssub.f64", //_VSSUB_F64,

  // Scalar on Vector subtraction (unsigned integer, saturated)
  //
  // vd[i] = vs[i] - x
  "vssubs.u64", //_VSSUBS_U64,

  // Scalar on Vector subtraction (signed integer, saturated)
  //
  // vd[i] = vs[i] - x
  "vssubs.s64", //_VSSUBS_S64,

  // Scalar Scalar Vector multiply (unsigned integer)
  //
  // vd[i] = vs[i] * x
  "vsmul.u64", //_VSMUL_U64,

  // Scalar on Vector multiply (signed integer)
  //
  // vd[i] = vs[i] * x
  "vsmul.s64", //_VSMUL_S64,

  // Scalar on Vector multiply (float)
  //
  // vd[i] = vs[i] * x
  "vsmul.f64", //_VSMUL_F64,

  // Scalar on Vector multiply (unsigned integer, saturated)
  //
  // vd[i] = vs[i] * x
  "vsmuls.u64", //_VSMULS_U64,

  // Scalar on Vector multiply (signed integer, saturated)
  //
  // vd[i] = vs[i] * x
  "vsmuls.s64", //_VSMULS_S64,

  // Scalar on Vector division (unsigned integer)
  //
  // vd[i] = vs[i] / x
  "vsdiv.u64", //_VSDIV_U64,

  // Scalar on Vector division (signed integer)
  //
  // vd[i] = vs[i] / x
  "vsdiv.f64", //_VSDIV_S64,

  // Scalar on Vector division (float)
  //
  // vd[i] = vs[i] / x
  "vsdiv.f64", //_VSDIV_F64,

  // Scalar on Vector division (signed integer, saturated)
  //
  // vd[i] = vs[i] / x
  "vsdivs.s64", //_VSDIVS_S64,

  // Scalar on Vector modulus (unsigned integer)
  //
  // vd[i] = vs[i] % x
  "vsmod.u64", //_VSMOD_U64,

  // Scalar on Vector modulus (signed integer)
  //
  // vd[i] = vs[i] % x
  "vsmod.s64", //_VSMOD_S64,

  // Scalar on Vector modulus (float)
  //
  // vd[i] = vs[i] % x
  "vsmod.f64", //_VSMOD_F64,

  // Scalar on Vector bitwise AND
  //
  // vd[i] = vs[i] & x
  "vsand.64", //_VSAND_64,

  // Scalar on Vector bitwise OR
  //
  // vd[i] = vs[i] | x
  "vsor.64", //_VSOR_64,

  // Scalar on Vector XOR
  //
  // vd[i] = vs[i] ^ x
  "vxor.64", //_VSXOR_64,

  // Scalar on Vector logical shift left
  //
  // vd[i] = vs[i] << x
  "vslsl.64", //_VSLSL_64,

  // Scalar on Vector logical shift right
  //
  // vd[i] = vs[i] >> x
  "vslsr.64", //_VSLSR_64,

  // Scalar on Vector arithmetic shift left
  //
  // vd[i] = vs[i] << x
  "vsasl.s64", //_VSASL_64,

  // Scalar on Vector arithmetic shift right
  //
  // vd[i] = vs[i] >> x
  "vsasr.s64", //_VSASR_64,

  // Scalar on Vector rotate left
  //
  // vd[i] = vs[i] <<@ x
  "vsrol.64", //_VSROL_64,

  // Scalar on Vector rotate right
  //
  // vd[i] = vs[i] @>> x
  "vsror.64", //_VSROR_64,

  // LEVEL 2

  // Vector addition (integer)
  //
  // vd[i] = va[i] + vb[i]
  "vadd.i64", //_VADD_I64,

  // Vector addition (float)
  //
  // vd[i] = va[i] + vb[i]
  "vadd.f64", //_VADD_F64,

  // Vector addition (unsigned integer, saturated)
  //
  // vd[i] = va[i] + vb[i]
  "vadds.u64", //_VADDS_U64,

  // Vector addition (signed integer, saturated)
  //
  // vd[i] = va[i] + vb[i]
  "vadds.s64", //_VADDS_S64,

  // Vector subtraction (integer)
  //
  // vd[i] = va[i] - vb[i]
  "vsub.i64", //_VSUB_I64,

  // Vector subtraction (float)
  //
  // vd[i] = va[i] - vb[i]
  "vsub.f64", //_VSUB_F64,

  // Vector subtraction (unsigned integer, saturated)
  //
  // vd[i] = va[i] - vb[i]
  "vsubs.u64", //_VSUBS_U64,

  // Vector subtraction (signed integer, saturated)
  //
  // vd[i] = va[i] - vb[i]
  "vsubs.s64", //_VSUBS_S64,

  // Vector multiply (unsigned integer)
  //
  // vd[i] = va[i] * vb[i]
  "vmul.u64", //_VMUL_U64,

  // Vector multiply (signed integer)
  //
  // vd[i] = va[i] * vb[i]
  "vmul.s64", //_VMUL_S64,

  // Vector multiply (float)
  //
  // vd[i] = va[i] * vb[i]
  "vmul.f64", //_VMUL_F64,

  // Vector multiply (unsigned integer, saturated)
  //
  // vd[i] = va[i] * vb[i]
  "vmuls.u64", //_VMULS_U64,

  // Vector multiply (signed integer, saturated)
  //
  // vd[i] = va[i] * vb[i]
  "vmuls.s64", //_VMULS_S64,

  // Vector division (unsigned integer)
  //
  // vd[i] = va[i] / vb[i]
  "vdiv.u64", //_VDIV_U64,

  // Vector division (signed integer)
  //
  // vd[i] = va[i] / vb[i]
  "vdiv.s64", //_VDIV_S64,

  // Vector division (float)
  //
  // vd[i] = va[i] / vb[i]
  "vdiv.f64", //_VDIV_F64,

  // Vector division (signed integer, saturated)
  //
  // vd[i] = va[i] / vb[i]
  "vdivs.s64", //_VDIVS_S64,

  // Vector modulus (unsigned integer)
  //
  // vd[i] = va[i] % vb[i]
  "vmod.u64", //_VMOD_U64,

  // Vector modulus (signed integer)
  //
  // vd[i] = va[i] % vb[i]
  "vmod.s64", //_VMOD_S64,

  // Vector modulus (float)
  //
  // vd[i] = va[i] % vb[i]
  "vmod.f64", //_VMOD_F64,

  // Vector mapping - convert an array of indexed values into values
  //
  // vd[i] = vm[vs[i]]
  "vmap8.64", //_VMAP_8_64,
  "vmap16.64", //_VMAP_16_64,

  // Vector multiply-accumulate
  "vmac.f64", //_VMAC_F64,

