#ifndef OPENCV_OPENCV_PERSISTENCE_H
#define OPENCV_OPENCV_PERSISTENCE_H

#include "../../../php_opencv.h"

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
