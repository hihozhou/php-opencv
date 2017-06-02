--TEST--
Check for opencv constant
--SKIPIF--
<?php if (!extension_loaded("opencv")) print "skip"; ?>
--FILE--
<?php 
var_dump(CV_8U);
var_dump(CV_8S);
var_dump(CV_16U);
var_dump(CV_16S);
var_dump(CV_32S);
var_dump(CV_32F);
var_dump(CV_64F);
var_dump(CV_USRTYPE1);

?>
--EXPECT--
int(0)
int(1)
int(2)
int(3)
int(4)
int(5)
int(6)
int(7)
