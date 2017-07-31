--TEST--
CV test
--SKIPIF--
<?php if (!extension_loaded("opencv")) print "skip"; ?>
--FILE--
<?php
use function CV\imread;
use CV\Mat;
use const CV\{IMREAD_COLOR};
$im = imread('./tests/cv.png',IMREAD_COLOR);
var_dump($im);
//$im->print();
//CV::imwrite('2222.png',$im);
?>
--EXPECT--
object(CV\Mat)#1 (4) {
  ["type":"CV\Mat":private]=>
  int(16)
  ["rows"]=>
  int(50)
  ["cols"]=>
  int(50)
  ["dims"]=>
  int(2)
}