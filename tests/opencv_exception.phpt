--TEST--
Exception
--SKIPIF--
<?php if (!extension_loaded("opencv")) print "skip"; ?>
--FILE--
<?php
use function CV\imread;
try{
    imread('non-existent.png');
}catch(CV\Exception $e){
    echo $e->getMessage();
    exit;
}

?>
--EXPECT--
Can not load image : non-existent.png