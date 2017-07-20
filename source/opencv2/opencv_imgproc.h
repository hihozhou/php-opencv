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

#ifndef PHP_OPENCV_IMGPROC_H
#define PHP_OPENCV_IMGPROC_H

void opencv_imgproc_init(int module_number);
void opencv_color_conversion_code_init(int module_number);
void opencv_line_type_init(int module_number);
PHP_FUNCTION(opencv_cv_t_color);
PHP_FUNCTION(opencv_ellipse);
PHP_FUNCTION(opencv_circle);
PHP_FUNCTION(opencv_fill_poly);//TODO fillPoly
PHP_FUNCTION(opencv_line);
PHP_FUNCTION(opencv_rectangle);
PHP_FUNCTION(opencv_rectangle_by_point);
PHP_FUNCTION(opencv_rectangle_by_rect);
ZEND_BEGIN_ARG_INFO_EX(opencv_equalize_hist_arginfo, 0, 0, 2)
                ZEND_ARG_INFO(0, src)
                ZEND_ARG_INFO(1, dst)
ZEND_END_ARG_INFO()
PHP_FUNCTION(opencv_equalize_hist);

#endif //OPENCV_OPENCV_IMGPROC_H
