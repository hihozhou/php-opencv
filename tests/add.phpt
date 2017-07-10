--TEST--
CV add function test
--SKIPIF--
<?php if (!extension_loaded("opencv")) print "skip"; ?>
--FILE--
<?php
use function CV\{add};
use const CV\{CV_8UC1};
use CV\{Mat,Scalar};

$mat1 = new Mat(5,5,CV_8UC1,new Scalar(3));
$mat3 = null;
$mat1->print();
add($mat1,new Scalar(1,1,1,1),$mat1);
$mat1->print();
add(new Scalar(1,1,1,1),$mat1,$mat1);
$mat1->print();
$scalar=null;
add(new Scalar(1,1,1,1),new Scalar(1,1,1,1),$scalar);
$scalar->print();
var_dump($scalar);

?>
--EXPECT--
[  3,   3,   3,   3,   3;
   3,   3,   3,   3,   3;
   3,   3,   3,   3,   3;
   3,   3,   3,   3,   3;
   3,   3,   3,   3,   3]
[  4,   4,   4,   4,   4;
   4,   4,   4,   4,   4;
   4,   4,   4,   4,   4;
   4,   4,   4,   4,   4;
   4,   4,   4,   4,   4]
[  5,   5,   5,   5,   5;
   5,   5,   5,   5,   5;
   5,   5,   5,   5,   5;
   5,   5,   5,   5,   5;
   5,   5,   5,   5,   5]
[2, 2, 2, 2]
object(CV\Scalar)#4 (1) {
  ["val"]=>
  array(4) {
    [0]=>
    float(2)
    [1]=>
    float(2)
    [2]=>
    float(2)
    [3]=>
    float(2)
  }
}