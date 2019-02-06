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

#ifndef PHP_OPENCV_MAT_H
#define PHP_OPENCV_MAT_H

#include "../../../php_opencv.h"
#include <opencv2/core.hpp>

using namespace cv;

//todo Mat object noly unchar,need to support double,int,float

extern void opencv_mat_init(int module_number);

extern zend_class_entry *opencv_mat_ce;

#define Z_PHP_MAT_OBJ_P(zv)  get_mat_obj(Z_OBJ_P(zv))

typedef struct _opencv_mat_object{
    zend_object std;
    Mat *mat;
}opencv_mat_object;


/**
 * @param obj
 * @return
 */
static inline opencv_mat_object* get_mat_obj(zend_object *obj) {
    return (opencv_mat_object*)((char*)(obj) - XtOffsetOf(opencv_mat_object, std));
}

void opencv_mat_update_property_by_c_mat(zval *z,Mat *mat);

#endif //OPENCV_MAT_H
