--TEST--
LBPHFaceRecognizer with Decode
--SKIPIF--
<?php if (!extension_loaded("opencv")) print "skip"; ?>
--FILE--
<?php
use CV\Face\LBPHFaceRecognizer;
use function CV\{imdecode, cvtColor, equalizeHist};
use const CV\{COLOR_BGR2GRAY};

$faceRecognizer = LBPHFaceRecognizer::create();

//hihozhou
$str = file_get_contents('./tests/face_recognizer.jpg');
$src = imdecode($str);
$gray = cvtColor($src, COLOR_BGR2GRAY);
equalizeHist($gray, $gray);

$faceRecognizer->train([$gray], [1]);

//Obama
$str = file_get_contents('./tests/Obama.png');
$src = imdecode($str);
$gray = cvtColor($src, COLOR_BGR2GRAY);
equalizeHist($gray, $gray);

//Obama grey
$faceRecognizer->train([$gray], [41]);

$str = file_get_contents('./tests/Obama_gray.png');
$src = imdecode($str);
$gray = cvtColor($src, COLOR_BGR2GRAY);
equalizeHist($gray, $gray);

$faceLabel = $faceRecognizer->predict($gray, $faceConfidence);

$faceLabel = $faceRecognizer->predict($gray);

echo "{$faceLabel}";
?>
--EXPECT--
41
