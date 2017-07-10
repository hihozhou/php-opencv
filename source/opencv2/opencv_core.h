//
// Created by hiho on 17-6-28.
//

#ifndef OPENCV_CORE_H
#define OPENCV_CORE_H

#include "../../php_opencv.h"

extern void opencv_core_init(int module_number);

extern zend_class_entry *opencv_formatter_ce;

PHP_FUNCTION(opencv_add_weighted);

ZEND_BEGIN_ARG_INFO_EX(opencv_add_weighted_arginfo, 0, 0, 7)
                ZEND_ARG_INFO(0, src1)
                ZEND_ARG_INFO(0, alpha)
                ZEND_ARG_INFO(0, src2)
                ZEND_ARG_INFO(0, beta)
                ZEND_ARG_INFO(0, gamma)
                ZEND_ARG_INFO(1, dst)
                ZEND_ARG_INFO(0, dtype)
ZEND_END_ARG_INFO()
PHP_FUNCTION(opencv_split);

ZEND_BEGIN_ARG_INFO_EX(opencv_merge_arginfo, 0, 0, 2)
                ZEND_ARG_INFO(0, channels)
                ZEND_ARG_INFO(1, dst)
ZEND_END_ARG_INFO()
PHP_FUNCTION(opencv_merge);
PHP_FUNCTION(opencv_get_optimal_dft_size);

PHP_FUNCTION(opencv_copy_make_border);
ZEND_BEGIN_ARG_INFO_EX(opencv_copy_make_border_arginfo, 0, 0, 8)
                ZEND_ARG_INFO(0, src)
                ZEND_ARG_INFO(1, dst)
                ZEND_ARG_INFO(0, top)
                ZEND_ARG_INFO(0, bottom)
                ZEND_ARG_INFO(0, left)
                ZEND_ARG_INFO(0, right)
                ZEND_ARG_INFO(0, borderType)
                ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(opencv_dft_arginfo, 0, 0, 4)
                ZEND_ARG_INFO(0, src)
                ZEND_ARG_INFO(1, dst)
                ZEND_ARG_INFO(0, flags)
                ZEND_ARG_INFO(0, nonzeroRows)
ZEND_END_ARG_INFO()
PHP_FUNCTION(opencv_dft);

ZEND_BEGIN_ARG_INFO_EX(opencv_magnitude_arginfo, 0, 0, 3)
                ZEND_ARG_INFO(0, x)
                ZEND_ARG_INFO(0, y)
                ZEND_ARG_INFO(1, magnitude)
ZEND_END_ARG_INFO()
PHP_FUNCTION(opencv_magnitude);
ZEND_BEGIN_ARG_INFO_EX(opencv_add_arginfo, 0, 0, 5)
                ZEND_ARG_INFO(0, src1)
                ZEND_ARG_INFO(0, src2)
                ZEND_ARG_INFO(1, dst)
                ZEND_ARG_INFO(0, mask)
                ZEND_ARG_INFO(0, dtype)
ZEND_END_ARG_INFO()
PHP_FUNCTION(opencv_add);

#endif //OPENCV_CORE_H
