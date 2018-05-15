--TEST--
DNN::blobFromImage
--SKIPIF--
<?php if (!extension_loaded("opencv")) print "skip"; ?>
--FILE--
<?php
use CV\Scalar;
use function CV\{imread};

$src = imread("./tests/Obama_gray.png");

$blob = \CV\DNN\Net::blobFromImage($src, 1, new \CV\Size(48, 48), new Scalar(104, 177, 123));
var_export($blob);
?>
--EXPECT--
CV\Mat::__set_state(array(
   'type' => 5,
   'rows' => -1,
   'cols' => -1,
   'dims' => 4,
   'shape' => 
  array (
    0 => 1,
    1 => 3,
    2 => 48,
    3 => 48,
  ),
))