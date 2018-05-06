--TEST--
Check for opencv presence
--SKIPIF--
<?php if (!extension_loaded("opencv")) print "skip"; ?>
--FILE--
<?php
use CV\Face\FacemarkLBF;

$facemark = FacemarkLBF::create();
var_export($facemark);
?>
--EXPECT--
CV\Face\FacemarkLBF::__set_state(array(
))
