<?php

$iSize     = 1024;
$iMaxIters = 512;
$fBailout  = 16.0;

$fYMin = -1.25;
$fYMax = 1.25;
$fYTot = $fYMax - $fYMin;
$fXMax = 0.75;
$fXMin = $fXMax - $fYTot;
$fStep = $fYTot / $iSize;

$aPixels = new SPLFixedArray($iSize * $iSize);

$iPix = 0;
$fCY   = $fYMax;
for ($y = 0; $y<$iSize; $y++, $fCY -= $fStep) {
  $fCX = $fXMin;
  for ($x = 0; $x<$iSize; $x++, $fCX += $fStep) {
    $i   = $iMaxIters;
    $fZX = $fCX;
    $fZY = $fCY;
    $i   = $iMaxIters;
    do {
      $fZX2   = $fZX * $fZX;
      $fZY2   = $fZY * $fZY;
      $fTest  = $fZX2 + $fZY2;
      $fNewZX = $fZX2 - $fZY2 + $fCX;
      $fNewZY = 2 * $fZX * $fZY + $fCY;
      $fZY    = $fNewZY;
      $fZX    = $fNewZX;
    } while (--$i && $fTest < $fBailout);
    $aPixels[$iPix++] = ($i*$i)&0xFF;
  }
}

$f = fopen("php_out.ppm", "wb");
fprintf($f, "P5\n%d\n%d\n255\n", $iSize,$iSize);
$sBuff = '';
foreach ($aPixels as $iPix) {
  $sBuff .= chr($iPix);
}
fwrite($f, $sBuff);
fclose($f);
