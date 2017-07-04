<?php

namespace ExVM;

class Assembler {

  const
    OPCODE_DEF = 'opcodes.json'
  ;

  public function __construct() {
    $this->loadOpcodeDefs();
    print_r($this->aOpcodeMap);
  }

  private function loadOpcodeDefs() {
     $oOpcodeData = json_decode(file_get_contents(self::OPCODE_DEF));
     if (!$oOpcodeData) {
       throw new \Exception(
         'Unable to load "' . self::OPCODE_DEF . '", ' .
         json_last_error_msg()
       );
     }
     $this->oSyntax      = $oOpcodeData->syntax;
     $this->aOpcodeProps = (array)$oOpcodeData->opcodes;
     $this->aOpcodeVal   = array_flip(array_keys($this->aOpcodeProps));
     $sTypeSep           = $oOpcodeData->syntax->typsep;
     $this->aOpcodeMap = [];
     foreach ($this->aOpcodeProps as $sOpcode => $oProps) {
       $sCode = $oProps->mnemonic;
       if (isset($oProps->types)) {
         foreach ($oProps->types as $sType) {
           $this->aOpcodeMap[$sCode . $sTypeSep . $sType] = $sOpcode;
         }
       } else {
         $this->aOpcodeMap[$sCode] = $sOpcode;
       }
     }
  }
  
  private
    $aOpcodeVal,
    $aOpcodeProps,
    $aOpcodeMap
  ;
}

$oAssembler = new Assembler();
