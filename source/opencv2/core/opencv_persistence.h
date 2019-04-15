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

#ifndef PHP_OPENCV_PERSISTENCE_H
#define PHP_OPENCV_PERSISTENCE_H

#include "../../../php_opencv.h"
#include <opencv2/core.hpp>

using namespace cv;

extern zend_class_entry *opencv_file_storage_ce;

typedef struct _opencv_file_storage_object{
    zend_object std;
    FileStorage *fileStorage;
}opencv_file_storage_object;

#define Z_PHP_FILE_STORAGE_OBJ_P(zv)  get_file_storage_obj(Z_OBJ_P(zv))

void opencv_file_storage_init(int module_number);

/**
 * @param obj
 * @return
 */
static inline opencv_file_storage_object* get_file_storage_obj(zend_object *obj) {
    return (opencv_file_storage_object*)((char*)(obj) - XtOffsetOf(opencv_file_storage_object, std));
}

#endif //OPENCV_OPENCV_PERSISTENCE_H
