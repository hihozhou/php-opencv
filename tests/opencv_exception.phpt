--TEST--
Mat __construct
--SKIPIF--
<?php if (!extension_loaded("opencv")) print "skip"; ?>
--FILE--
<?php
use OpenCV\CV;
//CV::imread('non-existent.png');
try{
    CV::imread('non-existent.png');
}catch(OpenCV\Exception $e){
    echo $e->getMessage();
    exit;
}

?>
--EXPECT--
Can not load image : non-existent.png