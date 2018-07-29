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

#ifndef PHP_OPENCV_TYPE_H
#define PHP_OPENCV_TYPE_H

void opencv_type_init(int module_number);

extern zend_class_entry *opencv_point_ce;
extern zend_class_entry *opencv_scalar_ce;
extern zend_class_entry *opencv_size_ce;
extern zend_class_entry *opencv_rect_ce;
extern zend_class_entry *opencv_rotated_rect_ce;


#define Z_PHP_POINT_OBJ_P(zv)  get_point_obj(Z_OBJ_P(zv))
#define Z_PHP_SCALAR_OBJ_P(zv)  get_scalar_obj(Z_OBJ_P(zv))
#define Z_PHP_SIZE_OBJ_P(zv)  get_size_obj(Z_OBJ_P(zv))
#define Z_PHP_RECT_OBJ_P(zv)  get_rect_obj(Z_OBJ_P(zv))
#define Z_PHP_ROTATED_RECT_OBJ_P(zv)  get_rotated_rect_obj(Z_OBJ_P(zv))


typedef struct _opencv_point_object{
    Point *point;
    zend_object std;
}opencv_point_object;

typedef struct _opencv_scalar_object{
    Scalar *scalar;
    zend_object std;
}opencv_scalar_object;

typedef struct _opencv_size_object{
    Size *size;
    zend_object std;
}opencv_size_object;

typedef struct _opencv_rect_object{
    Rect *rect;
    zend_object std;
}opencv_rect_object;


typedef struct _opencv_rotated_rect_object{
    RotatedRect *rotatedRect;
    zend_object std;
}opencv_rotated_rect_object;

/**
 * @param obj
 * @return
 */
static inline opencv_point_object* get_point_obj(zend_object *obj) {
    return (opencv_point_object*)((char*)(obj) - XtOffsetOf(opencv_point_object, std));
}


static inline opencv_scalar_object* get_scalar_obj(zend_object *obj) {
    return (opencv_scalar_object*)((char*)(obj) - XtOffsetOf(opencv_scalar_object, std));
}


static inline opencv_size_object* get_size_obj(zend_object *obj) {
    return (opencv_size_object*)((char*)(obj) - XtOffsetOf(opencv_size_object, std));
}


static inline opencv_rect_object* get_rect_obj(zend_object *obj) {
    return (opencv_rect_object*)((char*)(obj) - XtOffsetOf(opencv_rect_object, std));
}

static inline opencv_rotated_rect_object* get_rotated_rect_obj(zend_object *obj) {
    return (opencv_rotated_rect_object*)((char*)(obj) - XtOffsetOf(opencv_rotated_rect_object, std));
}


void opencv_size_update_property_by_c_size(zval *z, Size *size);

void opencv_rect_update_property_by_c_rect(zval *z, Rect *rect);

void opencv_scalar_update_property_by_c_scalar(zval *z,Scalar *scalar);

void opencv_point_update_property_by_c_point(zval *z, Point *point);

void opencv_rotated_rect_update_property_by_c_rotated_rect(zval *z, RotatedRect *totatedRect);

#endif //OPENCV_OPENCV_TYPE_H
