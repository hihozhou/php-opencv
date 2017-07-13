#ifndef OPENCV_OPENCV_TYPE_H
#define OPENCV_OPENCV_TYPE_H

void opencv_type_init(int module_number);

extern zend_class_entry *opencv_point_ce;
extern zend_class_entry *opencv_scalar_ce;
extern zend_class_entry *opencv_size_ce;
extern zend_class_entry *opencv_rect_ce;


#define Z_PHP_POINT_OBJ_P(zv)  get_point_obj(Z_OBJ_P(zv))
#define Z_PHP_SCALAR_OBJ_P(zv)  get_scalar_obj(Z_OBJ_P(zv))
#define Z_PHP_SIZE_OBJ_P(zv)  get_size_obj(Z_OBJ_P(zv))
#define Z_PHP_RECT_OBJ_P(zv)  get_rect_obj(Z_OBJ_P(zv))


typedef struct _opencv_point_object{
    zend_object std;
    Point *point;
}opencv_point_object;

typedef struct _opencv_scalar_object{
    zend_object std;
    Scalar *scalar;
}opencv_scalar_object;

typedef struct _opencv_size_object{
    zend_object std;
    Size *size;
}opencv_size_object;

typedef struct _opencv_rect_object{
    zend_object std;
    Rect *rect;
}opencv_rect_object;


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

void opencv_rect_update_property_by_c_rect(zval *z, Rect *rect);

void opencv_scalar_update_property_by_c_scalar(zval *z,Scalar *scalar);
#endif //OPENCV_OPENCV_TYPE_H
