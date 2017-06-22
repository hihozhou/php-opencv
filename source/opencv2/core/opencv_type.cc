#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "../../../php_opencv.h"
#include "opencv_type.h"

zend_class_entry *opencv_point_ce;
zend_class_entry *opencv_scalar_ce;
zend_class_entry *opencv_size_ce;
zend_class_entry *opencv_rect_ce;


zend_object_handlers point_object_handlers;

/**
 * opencv_point_methods[]
 */
const zend_function_entry opencv_point_methods[] = {
        PHP_FE_END
};
/* }}} */

zend_object* point_create_handler(zend_class_entry *type)
{
    int size = sizeof(point_object);
    point_object *obj = (point_object *)ecalloc(1,size);
    memset(obj, 0, sizeof(point_object));
    zend_object_std_init(&obj->std, type);
    object_properties_init(&obj->std, type);
    obj->std.ce = type;
    obj->std.handlers = &point_object_handlers;
    return &obj->std;
}


/**
 * Type Init
 */
void opencv_type_init(int module_number){
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce,OPENCV_NS, "Point", opencv_point_methods);
    opencv_point_ce = zend_register_internal_class(&ce);

    opencv_point_ce->create_object = point_create_handler;
    memcpy(&point_object_handlers,
           zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    point_object_handlers.clone_obj = NULL;
//    point_object_handlers.write_property = mat_write_property;

//    zend_declare_property_null(opencv_point_ce,"type",sizeof("type") - 1,ZEND_ACC_PRIVATE);//private Mat->type
//    mat_object_handlers.free_obj = mat_free_handler;
}