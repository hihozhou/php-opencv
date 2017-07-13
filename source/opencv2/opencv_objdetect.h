#ifndef OPENCV_OBJDETECT_H
#define OPENCV_OBJDETECT_H

#include "../../php_opencv.h"
#include <opencv2/objdetect.hpp>

extern zend_class_entry *opencv_cascade_classifier_ce;

#define Z_PHP_CASCADE_CLASSIFIER_OBJ_P(zv)  get_cascade_classifier_obj(Z_OBJ_P(zv))

typedef struct _opencv_cascade_classifier_object{
    zend_object std;
    CascadeClassifier *cascadeClassifier;
}opencv_cascade_classifier_object;

extern void opencv_objdetect_init(int module_number);

static inline opencv_cascade_classifier_object* get_cascade_classifier_obj(zend_object *obj) {
    return (opencv_cascade_classifier_object*)((char*)(obj) - XtOffsetOf(opencv_cascade_classifier_object, std));
}

#endif //OPENCV_OBJDETECT_H
