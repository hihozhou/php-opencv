--TEST--
Check for opencv constant
--SKIPIF--
<?php if (!extension_loaded("opencv")) print "skip"; ?>
--FILE--
<?php 
var_dump(CV_8UC1);
var_dump(CV_8SC1);
var_dump(CV_16UC1);
var_dump(CV_16SC1);
var_dump(CV_32SC1);
var_dump(CV_32FC1);
var_dump(CV_64FC1);
var_dump(cv_8uc_n(1));

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
