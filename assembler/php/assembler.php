<?php

namespace ExVM;

class Assembler {

  const
    DEFAULT_SPEC_FILE = 'asmspec.json'
  ;

  public function __construct(string $sSpecFile = null) {
    if (null == $sSpecFile) {
      $sSpecFile = self::DEFAULT_SPEC_FILE;
    }
    $this->loadAssemblerSpec($sSpecFile);
  }

  public function parseLine(string $sLine) {

  }

  private function loadAssemblerSpec(string $sSpecFile) {
     $oAssemblerSpec = json_decode(file_get_contents(self::OPCODE_DEF));
     if (!$oAssemblerSpec) {
       throw new \Exception(
         'Unable to load "' . self::SPEC_FILE . '", ' .
         json_last_error_msg()
       );
     }

     $this->aReg = (array)$oAssemblerSpec->reg;

     $this->aOpcodeProps = (array)$oAssemblerSpec->opcodes;
     $this->aOpcodeVal   = array_flip(array_keys($this->aOpcodeProps));
     $sTypeSep           = $oAssemblerSpec->param->type;
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
    $aOpcodeMap,
    $aOpcodeProps
  ;
}


$oAssembler = new Assembler();
print_r($oAssembler);
