--TEST--
LBPHFaceRecognizer
--SKIPIF--
<?php if (!extension_loaded("opencv")) print "skip"; ?>
--FILE--
<?php
use CV\Face\LBPHFaceRecognizer;
use function CV\{imread, cvtColor, equalizeHist};
use const CV\{COLOR_BGR2GRAY};

$faceRecognizer = LBPHFaceRecognizer::create();

//hihozhou
$src = imread("./tests/face_recognizer.jpg");
$gray = cvtColor($src, COLOR_BGR2GRAY);
equalizeHist($gray, $gray);

$faceRecognizer->train([$gray], [1]);

//Obama
$src = imread("./tests/Obama.png");
$gray = cvtColor($src, COLOR_BGR2GRAY);
equalizeHist($gray, $gray);

//Obama grey
$faceRecognizer->train([$gray], [41]);

$src = imread("./tests/Obama_gray.png");
$gray = cvtColor($src, COLOR_BGR2GRAY);
equalizeHist($gray, $gray);

$faceLabel = $faceRecognizer->predict($gray);

$faceConfidence = $faceRecognizer->predictConfidence($gray);
echo "{$faceLabel}";
?>
--EXPECT--
41
