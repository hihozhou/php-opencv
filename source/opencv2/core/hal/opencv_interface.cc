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

#include "../../../../php_opencv.h"
#include "opencv_interface.h"
#include <opencv2/core/hal/interface.h>


void opencv_interface_init(int module_number)
{
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "CV_8U", CV_8U, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "CV_8S", CV_8S, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "CV_16U", CV_16U, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "CV_16S", CV_16S, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "CV_32S", CV_32S, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "CV_32F", CV_32F, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "CV_64F", CV_64F, CONST_CS | CONST_PERSISTENT);
    char *cv_usrtype1 = (char*)malloc(strlen("CV_USRTYPE1 support has been dropped in OpenCV 4.0") + 1);
    REGISTER_NS_STRING_CONSTANT(OPENCV_NS, "CV_USRTYPE1", cv_usrtype1, CONST_CS | CONST_PERSISTENT);

    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "CV_8UC1", CV_8UC1, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "CV_8UC2", CV_8UC2, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "CV_8UC3", CV_8UC3, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "CV_8UC4", CV_8UC4, CONST_CS | CONST_PERSISTENT);

    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "CV_8SC1", CV_8SC1, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "CV_8SC2", CV_8SC2, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "CV_8SC3", CV_8SC3, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "CV_8SC4", CV_8SC4, CONST_CS | CONST_PERSISTENT);

    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "CV_16UC1", CV_16UC1, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "CV_16UC2", CV_16UC2, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "CV_16UC3", CV_16UC3, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "CV_16UC4", CV_16UC4, CONST_CS | CONST_PERSISTENT);

    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "CV_16SC1", CV_16SC1, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "CV_16SC2", CV_16SC2, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "CV_16SC3", CV_16SC3, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "CV_16SC4", CV_16SC4, CONST_CS | CONST_PERSISTENT);

    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "CV_32SC1", CV_32SC1, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "CV_32SC2", CV_32SC2, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "CV_32SC3", CV_32SC3, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "CV_32SC4", CV_32SC4, CONST_CS | CONST_PERSISTENT);

    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "CV_32FC1", CV_32FC1, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "CV_32FC2", CV_32FC2, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "CV_32FC3", CV_32FC3, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "CV_32FC4", CV_32FC4, CONST_CS | CONST_PERSISTENT);

    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "CV_64FC1", CV_64FC1, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "CV_64FC2", CV_64FC2, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "CV_64FC3", CV_64FC3, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "CV_64FC4", CV_64FC4, CONST_CS | CONST_PERSISTENT);

}

PHP_FUNCTION(opencv_cv_8uc)
{
    long num;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "l", &num) == FAILURE) {
        return;
    }
    RETURN_LONG(CV_8UC(num));
}

PHP_FUNCTION(opencv_cv_8sc)
{
    long num;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "l", &num) == FAILURE) {
        return;
    }
    RETURN_LONG(CV_8SC(num));
}


PHP_FUNCTION(opencv_cv_16uc)
{
    long num;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "l", &num) == FAILURE) {
        return;
    }
    RETURN_LONG(CV_16UC(num));
}

PHP_FUNCTION(opencv_cv_16sc)
{
    long num;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "l", &num) == FAILURE) {
        return;
    }
    RETURN_LONG(CV_16SC(num));
}

PHP_FUNCTION(opencv_cv_32sc)
{
    long num;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "l", &num) == FAILURE) {
        return;
    }
    RETURN_LONG(CV_32SC(num));
}

PHP_FUNCTION(opencv_cv_32fc)
{
    long num;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "l", &num) == FAILURE) {
        return;
    }
    RETURN_LONG(CV_32FC(num));
}


PHP_FUNCTION(opencv_cv_64fc)
{
    long num;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "l", &num) == FAILURE) {
        return;
    }
    RETURN_LONG(CV_64FC(num));
}