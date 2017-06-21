#ifndef OPENCV_OPENCV_EXCEPTION_H
#define OPENCV_OPENCV_EXCEPTION_H

#include "php_opencv.h"

extern zend_class_entry *opencv_exception_ce;

PHP_OPENCV_API extern void opencv_throw_exception(char *error_message);


#endif //OPENCV_OPENCV_EXCEPTION_H