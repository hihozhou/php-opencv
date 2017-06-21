--TEST--
CV test
--SKIPIF--
<?php if (!extension_loaded("opencv")) print "skip"; ?>
--FILE--
<?php
use OpenCV\CV;
use OpenCV\Mat;
$im = CV::imread('./tests/cv.png');
var_dump($im);
//$im->print();
//CV::imwrite('2222.png',$im);
?>
--EXPECT--
object(OpenCV\Mat)#1 (3) {
  ["type":"OpenCV\Mat":private]=>
  int(16)
  ["rows"]=>
  int(50)
  ["cols"]=>
  int(50)
}
