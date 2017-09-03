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


#ifndef PHP_OPENCV_CORE_H
#define PHP_OPENCV_CORE_H

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
ZEND_BEGIN_ARG_INFO_EX(opencv_log_arginfo, 0, 0, 2)
                ZEND_ARG_INFO(0, src)
                ZEND_ARG_INFO(1, dst)
ZEND_END_ARG_INFO()
PHP_FUNCTION(opencv_log);
ZEND_BEGIN_ARG_INFO_EX(opencv_normalize_arginfo, 0, 0, 6)
                ZEND_ARG_INFO(0, src)
                ZEND_ARG_INFO(1, dst)
                ZEND_ARG_INFO(0, alpha)
                ZEND_ARG_INFO(0, beta)
                ZEND_ARG_INFO(0, norm_type)
                ZEND_ARG_INFO(0, dtype)
ZEND_END_ARG_INFO()
PHP_FUNCTION(opencv_normalize);
ZEND_BEGIN_ARG_INFO_EX(opencv_absdiff_arginfo, 0, 0, 3)
                ZEND_ARG_INFO(0, src1)
                ZEND_ARG_INFO(0, src2)
                ZEND_ARG_INFO(1, dst)
ZEND_END_ARG_INFO()
PHP_FUNCTION(opencv_absdiff);

ZEND_BEGIN_ARG_INFO_EX(opencv_lut_arginfo, 0, 0, 3)
                ZEND_ARG_INFO(0, src)
                ZEND_ARG_INFO(0, lut)
                ZEND_ARG_INFO(1, dst)
ZEND_END_ARG_INFO()
PHP_FUNCTION(opencv_lut);

#endif //OPENCV_CORE_H
