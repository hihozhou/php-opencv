--TEST--
CV magnitude function test
--SKIPIF--
<?php if (!extension_loaded("opencv")) print "skip"; ?>
--FILE--
<?php
use function CV\{magnitude};
use const CV\{CV_32FC1};
use CV\{Mat,Scalar};

$mat1 = new Mat(5,5,CV_32FC1,new Scalar(3));
$mat2 = new Mat(5,5,CV_32FC1,new Scalar(4));
$mat3 = null;
magnitude($mat1,$mat2,$mat3);
$mat1->print();
$mat2->print();
$mat3->print();


?>
--EXPECT--
[3, 3, 3, 3, 3;
 3, 3, 3, 3, 3;
 3, 3, 3, 3, 3;
 3, 3, 3, 3, 3;
 3, 3, 3, 3, 3]
[4, 4, 4, 4, 4;
 4, 4, 4, 4, 4;
 4, 4, 4, 4, 4;
 4, 4, 4, 4, 4;
 4, 4, 4, 4, 4]
[5, 5, 5, 5, 5;
 5, 5, 5, 5, 5;
 5, 5, 5, 5, 5;
 5, 5, 5, 5, 5;
 5, 5, 5, 5, 5]