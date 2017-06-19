#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php_opencv.h"
#include "source/opencv2/core/opencv_mat.h"
#include "opencv_exception.h"

zend_class_entry *opencv_cv_ce;

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

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s|l", &filename,&filename_len, &flags) == FAILURE) {
        RETURN_NULL();
    }
    zval instance;
    object_init_ex(&instance,opencv_mat_ce);
    mat_object *obj = Z_PHP_MAT_OBJ_P(&instance);

    Mat im = imread(filename,(int)flags);
    if(im.empty()){//check file exist
        char *error_message = (char*)malloc(strlen("Can not load image : ") + strlen(filename) + 1);
        strcpy(error_message,"Can not load image : ");
        strcat(error_message,filename);
        php_opencv_throw_exception(error_message);//throw exception
        free(error_message);
    }

    obj->mat=new Mat(im);

    //update php Mat object property
    zend_update_property_long(opencv_mat_ce, &instance, "rows", sizeof("rows")-1, obj->mat->rows);
    zend_update_property_long(opencv_mat_ce, &instance, "cols", sizeof("cols")-1, obj->mat->cols);
    zend_update_property_long(opencv_mat_ce, &instance, "type", sizeof("type")-1, obj->mat->type());

    //todo object_init_ex() memory leaks detected on RETURN_ZVAL(instance,1,0)
    RETURN_ZVAL(&instance,0,0); //return php Mat object

}

/**
 * //todo only cli can call this function
 * CV::imshow
 * @param execute_data
 * @param return_value
 */
PHP_METHOD(CV, imshow)
{
    char *window_name;
    long window_name_len;
    zval *object;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "sO", &window_name, &window_name_len, &object,opencv_mat_ce) == FAILURE) {
        RETURN_NULL();
    }
    mat_object *obj = Z_PHP_MAT_OBJ_P(object);
    namedWindow(window_name);
    imshow(window_name,*(obj->mat));
    RETURN_NULL();
}

/**
 * CV::waitKey
 * @param execute_data
 * @param return_value
 */
PHP_METHOD(CV,waitKey)
{
    long delay = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "|l", &delay) == FAILURE) {
        RETURN_NULL();
    }
    waitKey((int)(delay*1000));//seconds
    RETURN_NULL();
}

PHP_METHOD(CV,imwrite)
{
    char *filename;
    long filename_len;
    zval *object;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "sO", &filename,&filename_len, &object,opencv_mat_ce) == FAILURE) {
        RETURN_NULL();
    }
    mat_object *obj = Z_PHP_MAT_OBJ_P(object);
    //todo throw exception can't save
    imwrite(filename,*(obj->mat));
    RETURN_TRUE;
}

const zend_function_entry cv_methods[] = {
        PHP_ME(CV, imread, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(CV, imshow, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(CV, imwrite, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(CV, waitKey, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_FE_END
};

/**
 * register CV class
 */
void opencv_cv_init(void){
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce,"OpenCV", "CV", cv_methods);
    opencv_cv_ce = zend_register_internal_class(&ce);
}



