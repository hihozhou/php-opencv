
#include "../../php_opencv.h"
#include "opencv_imgcodecs.h"
#include "core/opencv_mat.h"
#include "../../opencv_exception.h"


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
        opencv_throw_exception(error_message);//throw exception
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