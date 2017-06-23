#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "../../../php_opencv.h"
#include "opencv_type.h"

zend_class_entry *opencv_point_ce;
zend_class_entry *opencv_scalar_ce;
zend_class_entry *opencv_size_ce;
zend_class_entry *opencv_rect_ce;

/**
 * -----------------------------------【CV\Point】--------------------------------------
 *
 * -------------------------------------------------------------------------------------
 */

zend_object_handlers opencv_point_object_handlers;

/**
 * Mat __construct
 * @param execute_data
 * @param return_value
 */
PHP_METHOD(opencv_point, __construct)
{
    long x=0, y=0;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "|ll", &x, &y) == FAILURE) {
        RETURN_NULL();
    }
    opencv_point_object *obj = Z_PHP_POINT_OBJ_P(getThis());
    Point point = Point((int)x, (int)y);
    obj->point = new Point(point);

    zend_update_property_long(opencv_point_ce, getThis(), "x", sizeof("x")-1, x);
    zend_update_property_long(opencv_point_ce, getThis(), "y", sizeof("y")-1, y);
}


/**
 * opencv_point_methods[]
 */
const zend_function_entry opencv_point_methods[] = {
        PHP_ME(opencv_point, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
        PHP_FE_END
};
/* }}} */

zend_object* opencv_point_create_handler(zend_class_entry *type)
{
    int size = sizeof(opencv_point_object);
    opencv_point_object *obj = (opencv_point_object *)ecalloc(1,size);
    memset(obj, 0, sizeof(opencv_point_object));
    zend_object_std_init(&obj->std, type);
    object_properties_init(&obj->std, type);
    obj->std.ce = type;
    obj->std.handlers = &opencv_point_object_handlers;
    return &obj->std;
}

/**
 * Point Class write_property
 * @param object
 * @param member
 * @param value
 * @param cache_slot
 */
void opencv_point_write_property(zval *object, zval *member, zval *value, void **cache_slot){

    zend_string *str = zval_get_string(member);
    char *memberName=ZSTR_VAL(str);
    opencv_point_object *obj = Z_PHP_POINT_OBJ_P(object);

    if(strcmp(memberName, "x") == 0 && obj->point->x!=(int)zval_get_long(value)){
        obj->point->x=(int)zval_get_long(value);
    }else if(strcmp(memberName, "y") == 0 && obj->point->y!=(int)zval_get_long(value)){
        obj->point->y=(int)zval_get_long(value);
    }
    zend_string_release(str);//free zend_string not memberName(zend_string->val)
    std_object_handlers.write_property(object,member,value,cache_slot);

}

/**
 * Type Init
 */
void opencv_point_init(int module_number){
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce,OPENCV_NS, "Point", opencv_point_methods);
    opencv_point_ce = zend_register_internal_class(&ce);

    opencv_point_ce->create_object = opencv_point_create_handler;
    memcpy(&opencv_point_object_handlers,
           zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    opencv_point_object_handlers.clone_obj = NULL;
    opencv_point_object_handlers.write_property = opencv_point_write_property;

//    zend_declare_property_null(opencv_point_ce,"type",sizeof("type") - 1,ZEND_ACC_PRIVATE);//private Mat->type
//    mat_object_handlers.free_obj = mat_free_handler;
}





/**
 * -----------------------------------【CV\Scalar】--------------------------------------
 *
 * -------------------------------------------------------------------------------------
 */

//-----------------------------------【CV\Size】---------------------------------------
//
//-------------------------------------------------------------------------------------

//-----------------------------------【CV\Rect】---------------------------------------
//
//-------------------------------------------------------------------------------------


/**
 * Type Init
 */
void opencv_type_init(int module_number){
    opencv_point_init(module_number);
}