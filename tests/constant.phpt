--TEST--
Check for opencv constant
--SKIPIF--
<?php if (!extension_loaded("opencv")) print "skip"; ?>
--FILE--
<?php
use function CV\{CV_8UC};
use const CV\{CV_8UC1,CV_8SC1,CV_16UC1,CV_16SC1,CV_32SC1,CV_32FC1,CV_64FC1};
var_dump(CV_8UC1);
var_dump(CV_8SC1);
var_dump(CV_16UC1);
var_dump(CV_16SC1);
var_dump(CV_32SC1);
var_dump(CV_32FC1);
var_dump(CV_64FC1);
var_dump(CV_8UC(1));

?>
--EXPECT--
int(0)
int(1)
int(2)
int(3)
int(4)
int(5)
int(6)
int(0)
