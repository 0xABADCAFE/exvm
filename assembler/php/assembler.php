<?php

namespace ExVM;

class Assembler {

  const
    OPCODE_DEF = 'opcodes.json'
  ;

  public function __construct() {
    $this->loadOpcodeDefs();
    print_r($this);
  }

  private function loadOpcodeDefs() {
     $oOpcodeData = json_decode(file_get_contents(self::OPCODE_DEF));
     if (!$oOpcodeData) {
       throw new \Exception(
         'Unable to load "' . self::OPCODE_DEF . '", ' .
         json_last_error_msg()
       );
     }
     $this->aOpcodeProps = (array)$oOpcodeData->opcodes;
     $this->aOpcodeVal   = array_flip(array_keys($this->aOpcodeProps));
  }
  
  private
	$aOpcodeVal,
	$aOpcodeProps
  ;
}

$oAssembler = new Assembler();
