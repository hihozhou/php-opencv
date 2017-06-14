#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php_opencv.h"
#include "mat.h"

zend_object_handlers mat_object_handlers;

zend_class_entry *mat_ce;

/**
 * @param type
 * @return
 */
zend_object* mat_create_handler(zend_class_entry *type)
{
    int size = sizeof(mat_object);
    mat_object *obj = (mat_object *)ecalloc(1,size);
    memset(obj, 0, sizeof(mat_object));
    zend_object_std_init(&obj->std, type);
    object_properties_init(&obj->std, type);
    obj->std.ce = type;
    obj->std.handlers = &mat_object_handlers;
    return &obj->std;
}


void mat_free_handler(zend_object *object)
{
    mat_object *obj;
    obj = get_mat_obj(object);
    delete obj->mat;
    zend_object_std_dtor(object);
}

/**
 * Mat __construct
 * @param execute_data
 * @param return_value
 */
PHP_METHOD(Mat, __construct)
{
    long rows, cols, type;
    //获取请求的参数
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "lll", &rows, &cols, &type) == FAILURE) {
        RETURN_NULL();
    }
    mat_object *obj = Z_PHP_MAT_OBJ_P(getThis());
    obj->mat = new Mat((int)rows, (int)cols, (int)type, Scalar(0));
    //obj->mat = new Mat((int)rows, (int)cols, (int)type); //TODO Why Mat array not correct
    zend_update_property_long(mat_ce, getThis(), "rows", sizeof("rows")-1, rows);
    zend_update_property_long(mat_ce, getThis(), "cols", sizeof("cols")-1, cols);
    zend_update_property_long(mat_ce, getThis(), "type", sizeof("type")-1, type);
}

/**
 * print Mat data
 * @param execute_data
 * @param return_value
 */
PHP_METHOD(Mat, print)
{
    mat_object *obj = Z_PHP_MAT_OBJ_P(getThis());
    std::cout <<*(obj->mat)<< std::endl;
    RETURN_NULL();
}

/**
 * mat_methods[]
 */
const zend_function_entry mat_methods[] = {
        PHP_ME(Mat, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
        PHP_ME(Mat, print, NULL, ZEND_ACC_PUBLIC)
        PHP_FE_END
};
/* }}} */



/**
 * Mat Class write_property
 * @param object
 * @param member
 * @param value
 * @param cache_slot
 */
void mat_write_property(zval *object, zval *member, zval *value, void **cache_slot){
    zend_string *str = zval_get_string(member);
    char *memberName=ZSTR_VAL(str);
    if(strcmp(memberName, "cols") == 0){
        mat_object *obj = Z_PHP_MAT_OBJ_P(object);
        obj->mat->cols=(int)zval_get_long(value);
    }else if(strcmp(memberName, "rows") == 0){
        mat_object *obj = Z_PHP_MAT_OBJ_P(object);
        obj->mat->rows=(int)zval_get_long(value);
    }
    zend_string_release(str);//free zend_string not memberName(zend_string->val)
    std_object_handlers.write_property(object,member,value,cache_slot);

}

/**
 * Mat Init
 */
void mat_init(){
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce,"OpenCV", "Mat", mat_methods);
    mat_ce = zend_register_internal_class(&ce);
//    zend_declare_property_long(mat_ce,"rows",sizeof("rows") - 1,0,ZEND_ACC_PUBLIC);
    mat_ce->create_object = mat_create_handler;
    memcpy(&mat_object_handlers,
           zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    mat_object_handlers.clone_obj = NULL;
    mat_object_handlers.write_property = mat_write_property;
//    mat_object_handlers.free_obj = mat_free_handler;
}






