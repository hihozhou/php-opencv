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

#ifndef PHP_OPENCV_INTERFACE_H
#define PHP_OPENCV_INTERFACE_H

extern void opencv_interface_init(int module_number);
extern PHP_FUNCTION(opencv_cv_8uc);
extern PHP_FUNCTION(opencv_cv_8sc);
extern PHP_FUNCTION(opencv_cv_16uc);
extern PHP_FUNCTION(opencv_cv_16sc);
extern PHP_FUNCTION(opencv_cv_32sc);
extern PHP_FUNCTION(opencv_cv_32fc);
extern PHP_FUNCTION(opencv_cv_64fc);
#endif //OPENCV_INTERFACE_H
