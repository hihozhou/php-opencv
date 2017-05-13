#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php_opencv.h"

zend_class_entry *mat_ce;

#define Z_PHP7OBJ_P(zv)  get_mat_obj(Z_OBJ_P((zv)))

zend_object_handlers mat_object_handlers;

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

/**
 * @param type
 * @return
 */
zend_object* mat_create_handler(zend_class_entry *type TSRMLS_DC)
{

    int size = sizeof(mat_object);
    mat_object *obj = (mat_object *)ecalloc(1,size);
    memset(obj, 0, sizeof(mat_object));
    zend_object_std_init(&obj->std, type TSRMLS_CC);
    object_properties_init(&obj->std, type);
    obj->std.ce = type;
    obj->std.handlers = &mat_object_handlers;
    return &obj->std;
}

PHP_METHOD(Mat, __construct)
{
    long rows, cols, type;
    Mat *mat = NULL;
    zval *object = getThis();
    //获取请求的参数
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lll", &rows, &cols, &type) == FAILURE) {
        RETURN_NULL();
    }
    mat = new Mat(rows, cols, type);
    mat_object *obj = Z_PHP7OBJ_P(object);
    //    car_object *obj = (car_object *)zend_object_store_get_object(object TSRMLS_CC);
    obj->mat = mat;
//        zend_update_property_long(mat_ce, getThis(), "speed", sizeof("speed")-1, obj->car->speed TSRMLS_CC);
}

/**
 * mat_methods[]
 */
const zend_function_entry mat_methods[] = {
        PHP_ME(Mat, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
        {NULL, NULL, NULL}
};
/* }}} */


/* {{{ PHP_MINIT_FUNCTION */
//PHP_MINIT_FUNCTION(mat)
//{
//    zend_class_entry ce;
//    INIT_NS_CLASS_ENTRY(ce,"OpenCV", "Mat", mat_methods);
//    mat_ce = zend_register_internal_class(&ce TSRMLS_CC);
//    zend_declare_property_null(mat_ce,"speed",sizeof("speed") - 1,ZEND_ACC_PUBLIC);
//    mat_ce->create_object = mat_create_handler;
//    memcpy(&mat_object_handlers,
//           zend_get_std_object_handlers(), sizeof(zend_object_handlers));
//    mat_object_handlers.clone_obj = NULL;
//
//    return SUCCESS;
//}


/**
 * Mat Init
 */
void mat_init(){
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce,"OpenCV", "Mat", mat_methods);
    mat_ce = zend_register_internal_class(&ce TSRMLS_CC);
    zend_declare_property_null(mat_ce,"speed",sizeof("speed") - 1,ZEND_ACC_PUBLIC);
    mat_ce->create_object = mat_create_handler;
    memcpy(&mat_object_handlers,
           zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    mat_object_handlers.clone_obj = NULL;
}