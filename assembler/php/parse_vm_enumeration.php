<?php

/**
 * Quick utility script that parses the vm_opcodes C++ header to extract the expected enumeration values so that
 * we can export them into a definitions file.
 */

$aSource = explode("\n", file_get_contents('../../source/include/vm_opcodes.hpp'));

$sMatch = '';
foreach ($aSource as $sSource) {
  if (preg_match('<^\s*_>', $sSource)) {
    $sMatch .= $sSource;
  }
}

$aMatch = array_flip(explode(
  ',',
  rtrim(
    preg_replace(
      ['<//.*?$>m', '<\s*#.*?$>m','<\s+>','<=0>'],
      [''],
      $sMatch
    ),
    ','
  )
));

echo json_encode($aMatch, JSON_PRETTY_PRINT), "\n";
