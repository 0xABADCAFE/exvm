<?php

$oAsmSpec  = json_decode(file_get_contents('asmspec.json'));
$aOpcodes  = (array)json_decode(file_get_contents('opcode.json'));
$aInstDefs = (array)$oAsmSpec->instructions;
$aRemap    = [];

foreach ($aInstDefs as $sKey => $oProperty) {
  $sOpcodeKey = '_' . $sKey;
  if (isset($aOpcodes[$sOpcodeKey])) {
    $iCode = $aOpcodes[$sOpcodeKey];
    if ($oProperty->code != $iCode) {
      echo "Opcode ", $sKey, " has changed value from ", $oProperty->code, " to ", $iCode, "\n";
      $aRemap[$oProperty->code] = $iCode;
      $oProperty->code = $iCode;
    }
  } else {
    echo "'", $sKey, "'\n";
  }
}

if (count($aRemap)) {
  foreach ($aInstDefs as $sKey => $oProperty) {
    $sOpcodeKey = '_' . $sKey;
    if (!isset($aOpcodes[$sOpcodeKey])) {
      if (isset($aRemap[$oProperty->code])) {
        echo "Aliased entry ", $sKey, " refered to remapped opcode ", $oProperty->code, ", which is was renumbered to ", $aRemap[$oProperty->code], "\n";
        $oProperty->code = $aRemap[$oProperty->code];
      }
    }
  }
}

file_put_contents(
  'asmspec_renumbered.json',
  json_encode($oAsmSpec, JSON_PRETTY_PRINT) . "\n"
);
