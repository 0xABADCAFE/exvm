<?php

$aEnum = [
  'advanced' => [
    0 => [
      'op_adv_load_impl_l0.hpp',
      'op_adv_store_impl_l0.hpp',
    ],
    1 => [
      'op_adv_const_impl_l1.hpp',
      'op_adv_madd_impl_l1.hpp',
      'op_adv_roots_impl_l1.hpp',
      'op_adv_trig_impl_l1.hpp',
      'op_adv_powers_impl_l1.hpp',
      'op_adv_logs_impl_l1.hpp',
      'op_adv_trunc_impl_l1.hpp',
      'op_adv_lerp_impl_l1.hpp',
      'op_adv_vec3_f32_impl_l1.hpp'
    ],
    2 => [
    'op_adv_load_impl_l2.hpp',
    'op_adv_store_impl_l2.hpp',
    'op_adv_const_impl_l2.hpp',
    'op_adv_madd_impl_l2.hpp',
    'op_adv_roots_impl_l2.hpp',
    'op_adv_trig_impl_l2.hpp',
    'op_adv_powers_impl_l2.hpp',
    'op_adv_logs_impl_l2.hpp',
    'op_adv_trunc_impl_l2.hpp',
    'op_adv_lerp_impl_l2.hpp',
    ]

  ],
  'scalar' => [
    0 => [
      'op_control_impl_l0.hpp',
      'op_load_impl_l0.hpp',
      'op_store_impl_l0.hpp',
      'op_move_impl_l0.hpp',
      'op_jump_impl_l0.hpp',
      'op_convert_impl_l0.hpp',
      'op_arithmetic_impl_l0.hpp',
      'op_logic_impl_l0.hpp',
    ],
    1 => [
      'op_jump_impl_l1.hpp',
      'op_convert_impl_l1.hpp',
      'op_arithmetic_impl_l1.hpp',
    ],
    2 => [
      'op_load_impl_l2.hpp',
      'op_store_impl_l2.hpp',
      'op_move_impl_l2.hpp',
      'op_jump_impl_l2.hpp',
      'op_convert_impl_l2.hpp',
      'op_arithmetic_impl_l2.hpp',
      'op_logic_impl_l2.hpp',
    ]
  ],
  'vector' => [
    0 => [
      'op_vec_fill_impl_l0.hpp',
      'op_vec_smin_impl_l0.hpp',
      'op_vec_smax_impl_l0.hpp',
      'op_vec_ssum_impl_l0.hpp',
      'op_vec_neg_impl_l0.hpp',
      'op_vec_abs_impl_l0.hpp',
      'op_vec_inv_impl_l0.hpp',
      'op_vec_sadd_impl_l0.hpp',
      'op_vec_sadd_saturated_impl_l0.hpp',
      'op_vec_ssub_impl_l0.hpp',
      'op_vec_ssub_saturated_impl_l0.hpp',
      'op_vec_smul_impl_l0.hpp',
      'op_vec_smul_saturated_impl_l0.hpp',
      'op_vec_sdiv_impl_l0.hpp',
      'op_vec_sdiv_saturated_impl_l0.hpp',
      'op_vec_smod_impl_l0.hpp',
      'op_vec_sand_impl_l0.hpp',
      'op_vec_sor_impl_l0.hpp',
      'op_vec_sxor_impl_l0.hpp',
      'op_vec_slsl_impl_l0.hpp',
      'op_vec_slsr_impl_l0.hpp',
      'op_vec_sasl_impl_l0.hpp',
      'op_vec_sasr_impl_l0.hpp',
      'op_vec_srol_impl_l0.hpp',
      'op_vec_sror_impl_l0.hpp',
      'op_vec_vadd_impl_l0.hpp',
      'op_vec_vadd_saturated_impl_l0.hpp',
      'op_vec_vsub_impl_l0.hpp',
      'op_vec_vsub_saturated_impl_l0.hpp',
      'op_vec_vmul_impl_l0.hpp',
      'op_vec_vmul_saturated_impl_l0.hpp',
      'op_vec_vdiv_impl_l0.hpp',
      'op_vec_vdiv_saturated_impl_l0.hpp',
      'op_vec_vmod_impl_l0.hpp',
      'op_vec_vbitwise_impl_l0.hpp',
      'op_vec_vmap_impl_l0.hpp',
    ],
    1 => [
      'op_vec_smin_impl_l1.hpp',
      'op_vec_smax_impl_l1.hpp',
      'op_vec_ssum_impl_l1.hpp',
      'op_vec_neg_impl_l1.hpp',
      'op_vec_abs_impl_l1.hpp',
      'op_vec_sadd_impl_l1.hpp',
      'op_vec_ssub_impl_l1.hpp',
      'op_vec_smul_impl_l1.hpp',
      'op_vec_sdiv_impl_l1.hpp',
      'op_vec_smod_impl_l1.hpp',
      'op_vec_vadd_impl_l1.hpp',
      'op_vec_vsub_impl_l1.hpp',
      'op_vec_vmul_impl_l1.hpp',
      'op_vec_vdiv_impl_l1.hpp',
      'op_vec_vmod_impl_l1.hpp',
      'op_vec_vmac_impl_l1.hpp',
    ],
    2 => [
      'op_vec_fill_impl_l2.hpp',
      'op_vec_smin_impl_l2.hpp',
      'op_vec_smax_impl_l2.hpp',
      'op_vec_ssum_impl_l2.hpp',
      'op_vec_neg_impl_l2.hpp',
      'op_vec_abs_impl_l2.hpp',
      'op_vec_sadd_impl_l2.hpp',
      'op_vec_sadd_saturated_impl_l2.hpp',
      'op_vec_ssub_impl_l2.hpp',
      'op_vec_ssub_saturated_impl_l2.hpp',
      'op_vec_smul_impl_l2.hpp',
      'op_vec_smul_saturated_impl_l2.hpp',
      'op_vec_sdiv_impl_l2.hpp',
      'op_vec_sdiv_saturated_impl_l2.hpp',
      'op_vec_smod_impl_l2.hpp',
      'op_vec_sand_impl_l2.hpp',
      'op_vec_sor_impl_l2.hpp',
      'op_vec_sxor_impl_l2.hpp',
      'op_vec_slsl_impl_l2.hpp',
      'op_vec_slsr_impl_l2.hpp',
      'op_vec_sasl_impl_l2.hpp',
      'op_vec_sasr_impl_l2.hpp',
      'op_vec_srol_impl_l2.hpp',
      'op_vec_sror_impl_l2.hpp',
      'op_vec_vadd_impl_l2.hpp',
      'op_vec_vadd_saturated_impl_l2.hpp',
      'op_vec_vsub_impl_l2.hpp',
      'op_vec_vsub_saturated_impl_l2.hpp',
      'op_vec_vmul_impl_l2.hpp',
      'op_vec_vmul_saturated_impl_l2.hpp',
      'op_vec_vdiv_impl_l2.hpp',
      'op_vec_vdiv_saturated_impl_l2.hpp',
      'op_vec_vmod_impl_l2.hpp',
      'op_vec_vmap_impl_l2.hpp',
      'op_vec_vmac_impl_l2.hpp',
    ]
  ]
];

const INC_PATH = '../include/opcodes/';

foreach ($aEnum as $sClass => $aImpl) {

  $sIncPath = INC_PATH . $sClass . '/';
  foreach ($aImpl as $iLevel => $aFile) {

    $sEnumFile = $sIncPath . 'enum_l' . $iLevel . '.hpp';

    $sFileContent = file_get_contents($sEnumFile);

    preg_match_all(
      '/_(.*?),/',
      $sFileContent,
      $aEnumKeys
    );
    $aEnumKeys = $aEnumKeys[1];

    echo count($aEnumKeys), " enumerated operations in ", $sEnumFile, "...\n\n";
    echo "\t", implode(", ", $aEnumKeys), "\n";
    $sFileContent = '';

    foreach ($aFile as $sFile) {
      $sPath = $sIncPath . $sFile;

      echo "\tLoading ", $sPath, "...\n";
      $sFileContent .= file_get_contents($sPath);
    }

    preg_match_all(
      '/_DEFINE_OP\((.*?)\)/',
      $sFileContent,
      $aFileKeys
    );
    $aFileKeys = $aFileKeys[1];

    if ($aEnumKeys != $aFileKeys) {
      print_r($aEnumKeys);
      print_r($aFileKeys);
      die("Inconsistency found in implementation of $sEnumFile\n" );
    }
    echo "\tAll required implementation handlers are present and in correct sequence.\n\n";
  }
}

