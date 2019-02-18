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

#include "../../php_opencv.h"
//todo 如果需要引入core/opencv_mat.h文件必须在放在本文件头的前面，重复引用问题
#include "core/opencv_mat.h"
#include "opencv_ml.h"



void opencv_ml_init(int module_number){
    opencv_ml_constants_init(module_number);
    opencv_k_nearest_init(module_number);
}

void opencv_ml_constants_init(int module_number){
    opencv_ml_sample_types_init(module_number);
}

void opencv_ml_sample_types_init(int module_number){
    REGISTER_NS_LONG_CONSTANT(OPENCV_ML_NS, "ROW_SAMPLE", ROW_SAMPLE, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_ML_NS, "COL_SAMPLE", COL_SAMPLE, CONST_CS | CONST_PERSISTENT);
}

/****************************************************************************************\
*                          K-Nearest Neighbour Classifier                                *
\****************************************************************************************/

zend_class_entry *opencv_k_nearest_ce;


zend_object_handlers opencv_k_nearest_object_handlers;


/**
 * CV\ML\KNearest->create
 * @param execute_data
 * @param return_value
 */
PHP_METHOD(opencv_k_nearest, create)
{
    zval instance;
    object_init_ex(&instance, opencv_k_nearest_ce);
    opencv_k_nearest_object *object = Z_PHP_K_NEAREST_OBJ_P(&instance);
    object->KNearest = KNearest::create();
    RETURN_ZVAL(&instance,0,0);
}

/**
 * CV\ML\KNearest->getDefaultK
 * @param execute_data
 * @param return_value
 */
PHP_METHOD(opencv_k_nearest, get_default_k)
{
    opencv_k_nearest_object *obj = Z_PHP_K_NEAREST_OBJ_P(getThis());
    RETURN_LONG(obj->KNearest->getDefaultK());
}

/**
 * CV\ML\KNearest->setDefaultK
 * @param execute_data
 * @param return_value
 */
PHP_METHOD(opencv_k_nearest, set_default_k)
{
    long val;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "l", &val) == FAILURE) {
        RETURN_NULL();
    }
    opencv_k_nearest_object *obj = Z_PHP_K_NEAREST_OBJ_P(getThis());
    obj->KNearest->setDefaultK((int)val);
    RETURN_NULL();
}

PHP_METHOD(opencv_k_nearest, train)
{
    zval *samples_zval, *responses_zval;
    long layout;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "OlO",
                              &samples_zval, opencv_mat_ce,
                              &layout,
                              &responses_zval, opencv_mat_ce
    ) == FAILURE) {
        RETURN_NULL();
    }
    opencv_k_nearest_object *obj = Z_PHP_K_NEAREST_OBJ_P(getThis());
    opencv_mat_object *samples_obj = Z_PHP_MAT_OBJ_P(samples_zval);
    opencv_mat_object *responses_obj = Z_PHP_MAT_OBJ_P(responses_zval);

    RETURN_BOOL(obj->KNearest->train(*samples_obj->mat, (int)layout, *responses_obj->mat));
}



/**
 * opencv_k_nearest_methods[]
 */
const zend_function_entry opencv_k_nearest_methods[] = {
        PHP_ME(opencv_k_nearest, create, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_MALIAS(opencv_k_nearest, getDefaultK ,get_default_k, NULL, ZEND_ACC_PUBLIC)
        PHP_MALIAS(opencv_k_nearest, setDefaultK ,set_default_k, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(opencv_k_nearest, train, NULL, ZEND_ACC_PUBLIC)
        PHP_FE_END
};
/* }}} */

/**
 * @param type
 * @return
 */
zend_object* opencv_k_nearest_handler(zend_class_entry *type)
{
    size_t size = sizeof(opencv_k_nearest_object);
    opencv_k_nearest_object *obj = (opencv_k_nearest_object *)ecalloc(1,size);
    memset(obj, 0, sizeof(opencv_k_nearest_object));
    zend_object_std_init(&obj->std, type);
    object_properties_init(&obj->std, type);
    obj->std.ce = type;
    obj->std.handlers = &opencv_k_nearest_object_handlers;
    return &obj->std;
}

void opencv_k_nearest_free_obj(zend_object *object)
{
    opencv_k_nearest_object *obj;
    obj = get_opencv_k_nearest_object(object);
    delete obj->KNearest;
    zend_object_std_dtor(object);
}


void opencv_k_nearest_init(int module_number){
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce, OPENCV_ML_NS, "KNearest", opencv_k_nearest_methods);
    opencv_k_nearest_ce = zend_register_internal_class_ex(&ce, opencv_k_nearest_ce);

    opencv_k_nearest_ce->create_object = opencv_k_nearest_handler;
    memcpy(&opencv_k_nearest_object_handlers,
           zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    opencv_k_nearest_object_handlers.clone_obj = NULL;
    opencv_k_nearest_object_handlers.free_obj = opencv_k_nearest_free_obj;
}