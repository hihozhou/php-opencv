--TEST--
CV\VideoCapture Class test
--SKIPIF--
<?php if (!extension_loaded("opencv")) print "skip"; ?>
--FILE--
<?php
use CV\VideoCapture;

$video=new VideoCapture();
var_dump($video->isOpened());
$video->open(0);
var_dump($video);
var_dump($video->isOpened());

?>
--EXPECT--
bool(false)
object(CV\VideoCapture)#1 (0) {
}
bool(true)