//
// Created by hiho on 17-6-28.
//

#ifndef OPENCV_CORE_H
#define OPENCV_CORE_H

#include "../../php_opencv.h"

extern void opencv_core_init(int module_number);

extern zend_class_entry *opencv_formatter_ce;

PHP_FUNCTION(opencv_add_weighted);

ZEND_BEGIN_ARG_INFO_EX(opencv_add_weighted_arginfo, 0, 0, 1)
                ZEND_ARG_INFO(0, src1)
                ZEND_ARG_INFO(0, alpha)
                ZEND_ARG_INFO(0, src2)
                ZEND_ARG_INFO(0, beta)
                ZEND_ARG_INFO(0, gamma)
                ZEND_ARG_INFO(1, dst)
                ZEND_ARG_INFO(0, dtype)
ZEND_END_ARG_INFO()
PHP_FUNCTION(opencv_split);

ZEND_BEGIN_ARG_INFO_EX(opencv_merge_arginfo, 0, 0, 1)
                ZEND_ARG_INFO(0, channels)
                ZEND_ARG_INFO(1, dst)
ZEND_END_ARG_INFO()
PHP_FUNCTION(opencv_merge);
PHP_FUNCTION(opencv_get_optimal_dft_size);

#endif //OPENCV_CORE_H
