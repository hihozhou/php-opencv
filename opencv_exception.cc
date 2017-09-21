/*
 +----------------------------------------------------------------------+
 | PHP-OpenCV                                                           |
 +----------------------------------------------------------------------+
 | This source file is subject to version 2.0 of the Apache license,    |
 | that is bundled with this package in the file LICENSE, and is        |
 | available through the world-wide-web at the following url:           |
 | http://www.apache.org/licenses/LICENSE-2.0.html                      |
 | If you did not receive a copy of the Apache2.0 license and are unable|
 | to obtain it through the world-wide-web, please send a note to       |
 | hihozhou@gmail.com so we can mail you a copy immediately.            |
 +----------------------------------------------------------------------+
 | Author: HaiHao Zhou  <hihozhou@gmail.com>                            |
 +----------------------------------------------------------------------+
 */


/* $Id$ */


#include "php_opencv.h"
#include "zend_exceptions.h"
#include "opencv_exception.h"

zend_class_entry *opencv_exception_ce;

void opencv_exception_init(void)
{
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce, OPENCV_NS, "Exception", NULL);
    opencv_exception_ce = zend_register_internal_class_ex(&ce, zend_exception_get_default());
}


PHP_OPENCV_API void opencv_throw_exception(const char *error_message)
{
    int status = 1;
    zend_throw_exception(opencv_exception_ce, error_message, status);
    return;
}