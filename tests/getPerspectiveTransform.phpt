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
[1, 0, 0;
 0, 1, 0;
 -0, -0, 1]