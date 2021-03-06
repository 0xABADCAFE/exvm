//****************************************************************************//
//**                                                                        **//
//** File:         jump_table_defs.hpp                                      **//
//** Description:  Virtual Machine Core definitions                         **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2001-08-29                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//


// Implementation Level 0
_DECLARE_OP(VFILL_8)
_DECLARE_OP(VFILL_16)
_DECLARE_OP(VFILL_32)
_DECLARE_OP(VSMIN_U8)
_DECLARE_OP(VSMIN_U16)
_DECLARE_OP(VSMIN_U32)
_DECLARE_OP(VSMIN_S8)
_DECLARE_OP(VSMIN_S16)
_DECLARE_OP(VSMIN_S32)
_DECLARE_OP(VSMAX_U8)
_DECLARE_OP(VSMAX_U16)
_DECLARE_OP(VSMAX_U32)
_DECLARE_OP(VSMAX_S8)
_DECLARE_OP(VSMAX_S16)
_DECLARE_OP(VSMAX_S32)
_DECLARE_OP(VSSUM_U8)
_DECLARE_OP(VSSUM_U16)
_DECLARE_OP(VSSUM_U32)
_DECLARE_OP(VSSUM_S8)
_DECLARE_OP(VSSUM_S16)
_DECLARE_OP(VSSUM_S32)
_DECLARE_OP(VNEG_S8)
_DECLARE_OP(VNEG_S16)
_DECLARE_OP(VNEG_S32)
_DECLARE_OP(VABS_S8)
_DECLARE_OP(VABS_S16)
_DECLARE_OP(VABS_S32)
_DECLARE_OP(VINV_8)
_DECLARE_OP(VSADD_I8)
_DECLARE_OP(VSADD_I16)
_DECLARE_OP(VSADD_I32)
_DECLARE_OP(VSADDS_U8)
_DECLARE_OP(VSADDS_U16)
_DECLARE_OP(VSADDS_U32)
_DECLARE_OP(VSADDS_S8)
_DECLARE_OP(VSADDS_S16)
_DECLARE_OP(VSADDS_S32)
_DECLARE_OP(VSSUB_I8)
_DECLARE_OP(VSSUB_I16)
_DECLARE_OP(VSSUB_I32)
_DECLARE_OP(VSSUBS_U8)
_DECLARE_OP(VSSUBS_U16)
_DECLARE_OP(VSSUBS_U32)
_DECLARE_OP(VSSUBS_S8)
_DECLARE_OP(VSSUBS_S16)
_DECLARE_OP(VSSUBS_S32)
_DECLARE_OP(VSMUL_U8)
_DECLARE_OP(VSMUL_U16)
_DECLARE_OP(VSMUL_U32)
_DECLARE_OP(VSMUL_S8)
_DECLARE_OP(VSMUL_S16)
_DECLARE_OP(VSMUL_S32)
_DECLARE_OP(VSMULS_U8)
_DECLARE_OP(VSMULS_U16)
_DECLARE_OP(VSMULS_U32)
_DECLARE_OP(VSMULS_S8)
_DECLARE_OP(VSMULS_S16)
_DECLARE_OP(VSMULS_S32)
_DECLARE_OP(VSDIV_U8)
_DECLARE_OP(VSDIV_U16)
_DECLARE_OP(VSDIV_U32)
_DECLARE_OP(VSDIV_S8)
_DECLARE_OP(VSDIV_S16)
_DECLARE_OP(VSDIV_S32)
_DECLARE_OP(VSDIVS_S8)
_DECLARE_OP(VSDIVS_S16)
_DECLARE_OP(VSDIVS_S32)
_DECLARE_OP(VSMOD_U8)
_DECLARE_OP(VSMOD_U16)
_DECLARE_OP(VSMOD_U32)
_DECLARE_OP(VSMOD_S8)
_DECLARE_OP(VSMOD_S16)
_DECLARE_OP(VSMOD_S32)
_DECLARE_OP(VSAND_8)
_DECLARE_OP(VSAND_16)
_DECLARE_OP(VSAND_32)
_DECLARE_OP(VSOR_8)
_DECLARE_OP(VSOR_16)
_DECLARE_OP(VSOR_32)
_DECLARE_OP(VSXOR_8)
_DECLARE_OP(VSXOR_16)
_DECLARE_OP(VSXOR_32)
_DECLARE_OP(VSLSL_8)
_DECLARE_OP(VSLSL_16)
_DECLARE_OP(VSLSL_32)
_DECLARE_OP(VSLSR_8)
_DECLARE_OP(VSLSR_16)
_DECLARE_OP(VSLSR_32)
_DECLARE_OP(VSASL_8)
_DECLARE_OP(VSASL_16)
_DECLARE_OP(VSASL_32)
_DECLARE_OP(VSASR_8)
_DECLARE_OP(VSASR_16)
_DECLARE_OP(VSASR_32)
_DECLARE_OP(VSROL_8)
_DECLARE_OP(VSROL_16)
_DECLARE_OP(VSROL_32)
_DECLARE_OP(VSROR_8)
_DECLARE_OP(VSROR_16)
_DECLARE_OP(VSROR_32)
_DECLARE_OP(VADD_I8)
_DECLARE_OP(VADD_I16)
_DECLARE_OP(VADD_I32)
_DECLARE_OP(VADDS_U8)
_DECLARE_OP(VADDS_U16)
_DECLARE_OP(VADDS_U32)
_DECLARE_OP(VADDS_S8)
_DECLARE_OP(VADDS_S16)
_DECLARE_OP(VADDS_S32)
_DECLARE_OP(VSUB_I8)
_DECLARE_OP(VSUB_I16)
_DECLARE_OP(VSUB_I32)
_DECLARE_OP(VSUBS_U8)
_DECLARE_OP(VSUBS_U16)
_DECLARE_OP(VSUBS_U32)
_DECLARE_OP(VSUBS_S8)
_DECLARE_OP(VSUBS_S16)
_DECLARE_OP(VSUBS_S32)
_DECLARE_OP(VMUL_U8)
_DECLARE_OP(VMUL_U16)
_DECLARE_OP(VMUL_U32)
_DECLARE_OP(VMUL_S8)
_DECLARE_OP(VMUL_S16)
_DECLARE_OP(VMUL_S32)
_DECLARE_OP(VMULS_U8)
_DECLARE_OP(VMULS_U16)
_DECLARE_OP(VMULS_U32)
_DECLARE_OP(VMULS_S8)
_DECLARE_OP(VMULS_S16)
_DECLARE_OP(VMULS_S32)
_DECLARE_OP(VDIV_U8)
_DECLARE_OP(VDIV_U16)
_DECLARE_OP(VDIV_U32)
_DECLARE_OP(VDIV_S8)
_DECLARE_OP(VDIV_S16)
_DECLARE_OP(VDIV_S32)
_DECLARE_OP(VDIVS_S8)
_DECLARE_OP(VDIVS_S16)
_DECLARE_OP(VDIVS_S32)
_DECLARE_OP(VMOD_U8)
_DECLARE_OP(VMOD_U16)
_DECLARE_OP(VMOD_U32)
_DECLARE_OP(VMOD_S8)
_DECLARE_OP(VMOD_S16)
_DECLARE_OP(VMOD_S32)
_DECLARE_OP(VAND_8)
_DECLARE_OP(VOR_8)
_DECLARE_OP(VXOR_8)
_DECLARE_OP(VMAP_8_16)
_DECLARE_OP(VMAP_8_32)
_DECLARE_OP(VMAP_16_32)

// Implementation Level 1
_DECLARE_OP(VSMIN_F32)
_DECLARE_OP(VSMAX_F32)
_DECLARE_OP(VSSUM_F32)
_DECLARE_OP(VNEG_F32)
_DECLARE_OP(VABS_F32)
_DECLARE_OP(VSADD_F32)
_DECLARE_OP(VSSUB_F32)
_DECLARE_OP(VSMUL_F32)
_DECLARE_OP(VSDIV_F32)
_DECLARE_OP(VSMOD_F32)
_DECLARE_OP(VADD_F32)
_DECLARE_OP(VSUB_F32)
_DECLARE_OP(VMUL_F32)
_DECLARE_OP(VDIV_F32)
_DECLARE_OP(VMOD_F32)
_DECLARE_OP(VMAC_F32)

// Implementation Level 2
_DECLARE_OP(VFILL_64)
_DECLARE_OP(VSMIN_U64)
_DECLARE_OP(VSMIN_S64)
_DECLARE_OP(VSMIN_F64)
_DECLARE_OP(VSMAX_U64)
_DECLARE_OP(VSMAX_S64)
_DECLARE_OP(VSMAX_F64)
_DECLARE_OP(VSSUM_U64)
_DECLARE_OP(VSSUM_S64)
_DECLARE_OP(VSSUM_F64)
_DECLARE_OP(VNEG_S64)
_DECLARE_OP(VNEG_F64)
_DECLARE_OP(VABS_S64)
_DECLARE_OP(VABS_F64)
_DECLARE_OP(VSADD_I64)
_DECLARE_OP(VSADD_F64)
_DECLARE_OP(VSADDS_U64)
_DECLARE_OP(VSADDS_S64)
_DECLARE_OP(VSSUB_I64)
_DECLARE_OP(VSSUB_F64)
_DECLARE_OP(VSSUBS_U64)
_DECLARE_OP(VSSUBS_S64)
_DECLARE_OP(VSMUL_U64)
_DECLARE_OP(VSMUL_S64)
_DECLARE_OP(VSMUL_F64)
_DECLARE_OP(VSMULS_U64)
_DECLARE_OP(VSMULS_S64)
_DECLARE_OP(VSDIV_U64)
_DECLARE_OP(VSDIV_S64)
_DECLARE_OP(VSDIV_F64)
_DECLARE_OP(VSDIVS_S64)
_DECLARE_OP(VSMOD_U64)
_DECLARE_OP(VSMOD_S64)
_DECLARE_OP(VSMOD_F64)
_DECLARE_OP(VSAND_64)
_DECLARE_OP(VSOR_64)
_DECLARE_OP(VSXOR_64)
_DECLARE_OP(VSLSL_64)
_DECLARE_OP(VSLSR_64)
_DECLARE_OP(VSASL_64)
_DECLARE_OP(VSASR_64)
_DECLARE_OP(VSROL_64)
_DECLARE_OP(VSROR_64)
_DECLARE_OP(VADD_I64)
_DECLARE_OP(VADD_F64)
_DECLARE_OP(VADDS_U64)
_DECLARE_OP(VADDS_S64)
_DECLARE_OP(VSUB_I64)
_DECLARE_OP(VSUB_F64)
_DECLARE_OP(VSUBS_U64)
_DECLARE_OP(VSUBS_S64)
_DECLARE_OP(VMUL_U64)
_DECLARE_OP(VMUL_S64)
_DECLARE_OP(VMUL_F64)
_DECLARE_OP(VMULS_U64)
_DECLARE_OP(VMULS_S64)
_DECLARE_OP(VDIV_U64)
_DECLARE_OP(VDIV_S64)
_DECLARE_OP(VDIV_F64)
_DECLARE_OP(VDIVS_S64)
_DECLARE_OP(VMOD_U64)
_DECLARE_OP(VMOD_S64)
_DECLARE_OP(VMOD_F64)
_DECLARE_OP(VMAP_8_64)
_DECLARE_OP(VMAP_16_64)
_DECLARE_OP(VMAC_F64)

static const Handler vectorHandlers[256];   // vector handlers

