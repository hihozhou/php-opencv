#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php_opencv.h"
#include "mat.h"

zend_class_entry *cv_ce;

/**
 * CV::imread
 * @param execute_data
 * @param return_value
 */
PHP_METHOD(CV, imread)
{
    long flags;
    char *filename;
    long filename_len;

    flags = IMREAD_COLOR;//flags default value
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s|l", &filename,filename_len, &flags) == FAILURE) {
        RETURN_NULL();
    }
    zval *instance,rv={{0}};
    object_init_ex(instance,mat_ce);
    mat_object *obj = Z_PHP_MAT_OBJ_P(instance);

    Mat im=imread(filename,(int)flags);
    obj->mat=new Mat(im);

    //TODO object_init_ex() memory leaks detected on RETURN_ZVAL(instance,1,0)
    RETURN_ZVAL(instance,0,0); //return php Mat object

}

PHP_METHOD(CV, imshow)
{
    Mat im;
    RETURN_NULL();
}

PHP_METHOD(CV,imsave)
{

}

const zend_function_entry cv_methods[] = {
        PHP_ME(CV, imread, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(CV, imshow, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_FE_END
};

/**
 * register CV class
 */
void cv_init(){
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce,"OpenCV", "CV", cv_methods);
    cv_ce = zend_register_internal_class(&ce);
}



