//
// Created by hiho on 17-6-28.
//

#ifndef OPENCV_CORE_H
#define OPENCV_CORE_H

#include "../../php_opencv.h"

extern void opencv_core_init(int module_number);

extern zend_class_entry *opencv_formatter_ce;

PHP_FUNCTION(opencv_add_weighted);

#endif //OPENCV_CORE_H
