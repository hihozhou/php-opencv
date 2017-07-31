--TEST--
ROI test
--SKIPIF--
<?php if (!extension_loaded("opencv")) print "skip"; ?>
--FILE--
<?php
use CV\{Mat,Rect,Formatter};
use const CV\{CV_8UC1};

$mat = new Mat(10,10,CV_8UC1);
$rect = new Rect(0,0,5,5);
try{
    $roi = $mat->getImageROI($rect);
}catch(CV\Exception $e){
    var_dump($e);
    exit;
}
var_dump($roi);
$roi->print(Formatter::FMT_PYTHON);

?>
--EXPECT--
object(CV\Mat)#3 (4) {
  ["type":"CV\Mat":private]=>
  int(0)
  ["rows"]=>
  int(5)
  ["cols"]=>
  int(5)
  ["dims"]=>
  int(2)
}
[[  0,   0,   0,   0,   0],
 [  0,   0,   0,   0,   0],
 [  0,   0,   0,   0,   0],
 [  0,   0,   0,   0,   0],
 [  0,   0,   0,   0,   0]]