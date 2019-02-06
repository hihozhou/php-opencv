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



#include "../../../php_opencv.h"
#include "opencv_cvdef.h"
#include <opencv2/core/cvdef.h>

void opencv_cvdef_init(int module_number){
    opencv_cvdef_fundamental_constants_init(module_number);
}


void opencv_cvdef_fundamental_constants_init(int module_number){
    REGISTER_NS_DOUBLE_CONSTANT(OPENCV_NS, "CV_PI", CV_PI, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_DOUBLE_CONSTANT(OPENCV_NS, "CV_2PI", CV_2PI, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_DOUBLE_CONSTANT(OPENCV_NS, "CV_LOG2", CV_LOG2, CONST_CS | CONST_PERSISTENT);
}

