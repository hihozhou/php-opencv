//
// Created by hiho on 17-6-9.
//

#ifndef OPENCV_MAT_H
#define OPENCV_MAT_H

#endif //OPENCV_MAT_H
#include "../../../php_opencv.h"

extern zend_class_entry *mat_ce;

#define Z_PHP_MAT_OBJ_P(zv)  get_mat_obj(Z_OBJ_P(zv))

typedef struct _mat_object{
    zend_object std;
    Mat *mat;
}mat_object;


/**
 * @param obj
 * @return
 */
static inline mat_object* get_mat_obj(zend_object *obj) {
    return (mat_object*)((char*)(obj) - XtOffsetOf(mat_object, std));
}