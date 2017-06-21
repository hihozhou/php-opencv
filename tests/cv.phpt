--TEST--
CV test
--SKIPIF--
<?php if (!extension_loaded("opencv")) print "skip"; ?>
--FILE--
<?php
use function CV\imread;
use CV\Mat;
$im = imread('./tests/cv.png',IMREAD_COLOR);
var_dump($im);
//$im->print();
//CV::imwrite('2222.png',$im);
?>
--EXPECT--
object(CV\Mat)#1 (3) {
  ["type":"CV\Mat":private]=>
  int(16)
  ["rows"]=>
  int(50)
  ["cols"]=>
  int(50)
}