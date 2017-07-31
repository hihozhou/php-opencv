--TEST--
absdiff function test
--SKIPIF--
<?php if (!extension_loaded("opencv")) print "skip"; ?>
--FILE--
<?php
use CV\{Mat, Scalar};
use function CV\{absdiff};
use const CV\{CV_8UC1,CV_8UC3};

$mat1 = new Mat(3,3,CV_8UC1,new Scalar(0));
$mat2 = new Mat(3,3,CV_8UC1,new Scalar(10));
$dst = null;
absdiff($mat1, $mat2, $dst);
var_dump($dst);
$dst->print();
absdiff(new Scalar(0), new Scalar(0), $dst);
var_dump($dst);
$dst->print();
absdiff(new Mat(3,3,CV_8UC3,new Scalar(0)), new Scalar(0), $dst);
var_dump($dst);
$dst->print();

--EXPECT--
object(CV\Mat)#3 (4) {
  ["type":"CV\Mat":private]=>
  int(0)
  ["rows"]=>
  int(3)
  ["cols"]=>
  int(3)
  ["dims"]=>
  int(2)
}
[ 10,  10,  10;
  10,  10,  10;
  10,  10,  10]
object(CV\Scalar)#3 (1) {
  ["val"]=>
  array(4) {
    [0]=>
    float(0)
    [1]=>
    float(0)
    [2]=>
    float(0)
    [3]=>
    float(0)
  }
}
[0, 0, 0, 0]
object(CV\Mat)#3 (4) {
  ["type":"CV\Mat":private]=>
  int(16)
  ["rows"]=>
  int(3)
  ["cols"]=>
  int(3)
  ["dims"]=>
  int(2)
}
[  0,   0,   0,   0,   0,   0,   0,   0,   0;
   0,   0,   0,   0,   0,   0,   0,   0,   0;
   0,   0,   0,   0,   0,   0,   0,   0,   0]