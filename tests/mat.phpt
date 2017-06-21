--TEST--
Mat __construct
--SKIPIF--
<?php if (!extension_loaded("opencv")) print "skip"; ?>
--FILE--
<?php
use OpenCV\Mat;
$mat = new Mat(5,5,1);
//$mat->rows=10;
var_dump($mat);
$mat->print();
?>
--EXPECT--
object(OpenCV\Mat)#1 (3) {
  ["type":"OpenCV\Mat":private]=>
  int(1)
  ["rows"]=>
  int(5)
  ["cols"]=>
  int(5)
}
[  0,   0,   0,   0,   0;
   0,   0,   0,   0,   0;
   0,   0,   0,   0,   0;
   0,   0,   0,   0,   0;
   0,   0,   0,   0,   0]