<?php

namespace ExVM;

use \stdClass;
use \Exception;

class InvalidInstuctionSpecification extends Exception {}

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

  /**
   * Load up the assembler specification file.
   */
  private function loadAssemblerSpec(string $sSpecFile) {
    $oAssemblerSpec = json_decode(file_get_contents($sSpecFile));
    if (!$oAssemblerSpec) {
      throw new \Exception(
        'Unable to load "' . $sSpecFile . '", ' .
        json_last_error_msg()
      );
    }
    $this->aTypes     = [];
    $this->aOpcodeMap = [];
    $this->aReg       = (array)$oAssemblerSpec->regnames;

    foreach ($oAssemblerSpec->types as $key => $value) {
      $this->aTypes[(string)$key] = $value;
    }

    $this->aParams    = (array)$oAssemblerSpec->params;
    $this->aInstProps = (array)$oAssemblerSpec->instructions;
    $this->aOpcodeVal = array_flip(array_keys($this->aInstProps));
    $sTypeSep         = $oAssemblerSpec->params->type;

    foreach ($this->aInstProps as $sOpcode => $oProps) {
      $this->validateInstructionDefinition($sOpcode, $oProps);
      $sCode = $oProps->mnemonic;

      /* Build up the instruction map. Some instructions have different forms based on their parameters, which we represent here */
      if (isset($oProps->types)) {
        foreach ($oProps->types as $sType) {
          $sKey = $sCode . $sTypeSep . $sType;
          if (isset($this->aOpcodeMap[$sKey])) {
            $this->aOpcodeMap[$sKey][] = $sOpcode;
          } else {
            $this->aOpcodeMap[$sKey] = [$sOpcode];
          }
        }
      } else {
        if (isset($this->aOpcodeMap[$sCode])) {
          $this->aOpcodeMap[$sCode][] = $sOpcode;
        } else {
          $this->aOpcodeMap[$sCode] = [$sOpcode];
        }
      }
    }

    echo "Parsed ", count($this->aOpcodeMap), " assembler instruction variations based on ", count($this->aOpcodeVal), " discrete opcodes.\n";

    $aKnown = array_chunk(array_keys($this->aOpcodeMap), 8);
    foreach ($aKnown as $aInst) {
      echo "\t", implode(', ', $aInst), "\n";
    }
  }

  /**
   * Validate an instruction definition.
   */
  private function validateInstructionDefinition(string $sOpcode, stdClass $oProps) {
    if (empty($oProps->mnemonic)) {
      throw new InvalidInstuctionSpecification($sOpcode . ' lacks a mnemonic');
    }

    if (isset($oProps->types)) {
      if (!is_array($oProps->types)) {
        throw new InvalidInstuctionSpecification($sOpcode . ' types definition is not an array');
      }

      foreach ($oProps->types as $sType) {
        if (!isset($this->aTypes[$sType])) {
          throw new InvalidInstuctionSpecification($sOpcode . ' takes undefined type "' . $sType . '"');
        }
      }
    }

    if (isset($oProps->extension) && (!is_integer($oProps->extension) || $oProps->extension <= 0)) {
      throw new InvalidInstuctionSpecification($sOpcode . ' extension word count must be an integer greater than zero');
    } else {
      $oProps->extension = 0;
    }

    if (isset($oProps->params)) {
      if (!is_array($oProps->params)) {
        throw new InvalidInstuctionSpecification($sOpcode . ' params definition is not an array');
      }
      foreach ($oProps->params as $sParam) {
        if (!isset($this->aParams[$sParam])) {
          throw new InvalidInstuctionSpecification($sOpcode . ' takes undefined parameter type "' . $sParam . '"');
        }
      }
    }
  }

  private
    $aReg,
    $aTypes,
    $aParams,
    $aOpcodeVal,
    $aOpcodeMap,
    $aInstProps
  ;
}


$oAssembler = new Assembler();
//print_r($oAssembler);
