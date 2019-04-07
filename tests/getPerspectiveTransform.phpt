--TEST--
CV getPerspectiveTransform function test
--SKIPIF--
<?php if (!extension_loaded("opencv")) print "skip"; ?>
--FILE--
<?php
use function CV\{getPerspectiveTransform};
use CV\{Point};

$srcPoints = [
    new Point(165, 270),
    new Point(835, 270),
    new Point(360, 125),
    new Point(615, 125),
];
$dstPoints = [
    new Point(165, 270),
    new Point(835, 270),
    new Point(165, 200),
    new Point(835, 200),
];
$mat =  getPerspectiveTransform($srcPoints, $dstPoints, 1);

var_dump($mat);
$mat->print();


?>
--EXPECT--
object(CV\Mat)#9 (4) {
  ["type":"CV\Mat":private]=>
  int(6)
  ["rows"]=>
  int(3)
  ["cols"]=>
  int(3)
  ["dims"]=>
  int(2)
}
[-6.520134228187818, -13.36409395973132, 3608.305369127462;
 -9.880984919163893e-15, -8.718120805368972, 593.4563758389204;
 -3.209238430557093e-17, -0.0278523489932881, 1]