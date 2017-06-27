--TEST--
Ellipse test
--SKIPIF--
<?php if (!extension_loaded("opencv")) print "skip"; ?>
--FILE--
<?php

use CV\{Mat,Scalar,Point,Size};
use function CV\{ellipse,imwrite,waitKey};
use const CV\{CV_8UC3};

$windowWidth=600;
$thickness=2;
$lineType=8;
$matScalar=new Scalar(0,0,0);
$mat = new Mat($windowWidth,$windowWidth,CV_8UC3,$matScalar);
$point=new Point($windowWidth/2,$windowWidth/2);
$size=new Size($windowWidth/4,$windowWidth/16);
$scalar=new Scalar(255,129,0);
for($i = 0;$i<=360;$i+=45){
    ellipse($mat,$point,$size,$i,0,360,$scalar,$thickness,$lineType);
}
imwrite('./tests/ellipse.png',$mat);
--EXPECT--

