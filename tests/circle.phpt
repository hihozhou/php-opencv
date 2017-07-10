--TEST--
Draw circle test
--SKIPIF--
<?php if (!extension_loaded("opencv")) print "skip"; ?>
--FILE--
<?php
use CV\{Mat,Scalar,Point,Size};
use function CV\{imshow,waitKey,circle};
use const CV\{CV_8UC3,LINE_AA};

$windowWidth=600;
$thickness=2;
$lineType=8;
$matScalar=new Scalar(0,0,0);
$mat = new Mat($windowWidth,$windowWidth,CV_8UC3,$matScalar);
$point=new Point($windowWidth/2,$windowWidth/2);
$scalar=new Scalar(255,129,0);
$circle = new Mat($windowWidth,$windowWidth,CV_8UC3,$matScalar);
circle($circle,$point,$windowWidth/4,$scalar,-1,LINE_AA);

--EXPECT--


