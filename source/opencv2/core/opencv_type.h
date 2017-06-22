#ifndef OPENCV_OPENCV_TYPE_H
#define OPENCV_OPENCV_TYPE_H


extern zend_class_entry *opencv_point_ce;
extern zend_class_entry *opencv_scalar_ce;
extern zend_class_entry *opencv_size_ce;
extern zend_class_entry *opencv_rect_ce;


#define Z_PHP_POINT_OBJ_P(zv)  get_point_obj(Z_OBJ_P(zv))
#define Z_PHP_SCALAR_OBJ_P(zv)  get_scalar_obj(Z_OBJ_P(zv))
#define Z_PHP_SIZE_OBJ_P(zv)  get_size_obj(Z_OBJ_P(zv))
#define Z_PHP_RECT_OBJ_P(zv)  get_rect_obj(Z_OBJ_P(zv))


typedef struct _point_object{
    zend_object std;
    Point *point;
}point_object;

typedef struct _scalar_object{
    zend_object std;
    Scalar *scalar;
}scalar_object;

typedef struct _size_object{
    zend_object std;
    Size *size;
}size_object;

typedef struct _rect_object{
    zend_object std;
    Rect *rect;
}rect_object;


/**
 * @param obj
 * @return
 */
static inline point_object* get_point_obj(zend_object *obj) {
    return (point_object*)((char*)(obj) - XtOffsetOf(point_object, std));
}


static inline scalar_object* get_scalar_obj(zend_object *obj) {
    return (scalar_object*)((char*)(obj) - XtOffsetOf(scalar_object, std));
}


static inline size_object* get_size_obj(zend_object *obj) {
    return (size_object*)((char*)(obj) - XtOffsetOf(size_object, std));
}


static inline rect_object* get_rect_obj(zend_object *obj) {
    return (rect_object*)((char*)(obj) - XtOffsetOf(rect_object, std));
}


#endif //OPENCV_OPENCV_TYPE_H
