--TEST--
Type test
--SKIPIF--
<?php if (!extension_loaded("opencv")) print "skip"; ?>
--FILE--
<?php
use CV\Point;
use CV\Scalar;
use CV\Size;
use CV\Rect;
$point = new Point(10,8);
$point->x=20;
var_dump($point);
$point->print();

$scalar=new Scalar(2500,0,0);
var_dump($scalar);
$scalar->print();

$size=new Size(100,100);
var_dump($size);
$size->print();

$rect=new Rect(5,5,100,100);
var_dump($rect);
$rect->print();

var_dump($rect->tl());
var_dump($rect->br());
var_dump($rect->size());
var_dump($rect->area());

?>
--EXPECT--
object(CV\Point)#1 (2) {
  ["x"]=>
  int(20)
  ["y"]=>
  int(8)
}
[20, 8]
object(CV\Scalar)#2 (1) {
  ["val"]=>
  array(4) {
    [0]=>
    float(2500)
    [1]=>
    float(0)
    [2]=>
    float(0)
    [3]=>
    float(0)
  }
}
[2500, 0, 0, 0]
object(CV\Size)#3 (2) {
  ["width"]=>
  int(100)
  ["height"]=>
  int(100)
}
[100 x 100]
object(CV\Rect)#4 (4) {
  ["x"]=>
  int(5)
  ["y"]=>
  int(5)
  ["width"]=>
  int(100)
  ["height"]=>
  int(100)
}
[100 x 100 from (5, 5)]
object(CV\Point)#5 (2) {
  ["x"]=>
  int(5)
  ["y"]=>
  int(5)
}
object(CV\Point)#5 (2) {
  ["x"]=>
  int(105)
  ["y"]=>
  int(105)
}
object(CV\Size)#5 (2) {
  ["width"]=>
  int(100)
  ["height"]=>
  int(100)
}
int(10000)