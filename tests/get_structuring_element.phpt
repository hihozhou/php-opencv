--TEST--
get_structuring_element function test
--SKIPIF--
<?php if (!extension_loaded("opencv")) print "skip"; ?>
--FILE--
<?php
namespace CV;

$morph_elem = 2;
$morph_size = 3;
$element = getStructuringElement($morph_elem, new Size(2*$morph_size + 1, 2*$morph_size+1), new Point($morph_size, $morph_size));

var_dump($element);
$element->print();

--EXPECT--
object(CV\Mat)#3 (4) {
  ["type":"CV\Mat":private]=>
  int(0)
  ["rows"]=>
  int(7)
  ["cols"]=>
  int(7)
  ["dims"]=>
  int(2)
}
[  0,   0,   0,   1,   0,   0,   0;
   0,   1,   1,   1,   1,   1,   0;
   1,   1,   1,   1,   1,   1,   1;
   1,   1,   1,   1,   1,   1,   1;
   1,   1,   1,   1,   1,   1,   1;
   0,   1,   1,   1,   1,   1,   0;
   0,   0,   0,   1,   0,   0,   0]