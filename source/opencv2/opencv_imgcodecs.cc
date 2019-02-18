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
#include "opencv_imgcodecs.h"
#include "core/opencv_mat.h"
#include "../../opencv_exception.h"
#include <opencv2/imgcodecs.hpp>

using namespace cv;



/**
 * CV\imread
 * @param execute_data
 * @param return_value
 */
PHP_FUNCTION(opencv_imread)
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
    opencv_mat_object *obj = Z_PHP_MAT_OBJ_P(&instance);

    Mat im = imread(filename, (int)flags);
    if(im.empty() || !im.data){//check file exist
        char *error_message = (char*)malloc(strlen("Can not load image : ") + strlen(filename) + 1);
        strcpy(error_message,"Can not load image : ");
        strcat(error_message,filename);
        opencv_throw_exception(error_message);//throw exception
        free(error_message);
    }

    obj->mat = new Mat(im);

    //update php Mat object property
    opencv_mat_update_property_by_c_mat(&instance, obj->mat);

    //todo object_init_ex() memory leaks detected on RETURN_ZVAL(instance,1,0)
    RETURN_ZVAL(&instance,0,0); //return php Mat object
}

/**
 * CV\imwrite
 * @param execute_data
 * @param return_value
 */
PHP_FUNCTION(opencv_imwrite){
    char *filename;
    long filename_len;
    zval *object;
    if (zend_parse_parameters_ex(ZEND_PARSE_PARAMS_THROW, ZEND_NUM_ARGS(), "sO", &filename,&filename_len, &object,opencv_mat_ce) == FAILURE) {
        RETURN_NULL();
    }
    opencv_mat_object *obj = Z_PHP_MAT_OBJ_P(object);
    try {
        imwrite(filename,*obj->mat);
    }catch (Exception e){
        opencv_throw_exception(e.what());
    }
    RETURN_TRUE;
}


void opencv_imgcodecs_init(int module_number)
{
    /**
     * imread const flags
     */
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "IMREAD_UNCHANGED", IMREAD_UNCHANGED, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "IMREAD_GRAYSCALE", IMREAD_GRAYSCALE, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "IMREAD_COLOR", IMREAD_COLOR, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "IMREAD_ANYDEPTH", IMREAD_ANYDEPTH, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "IMREAD_ANYCOLOR", IMREAD_ANYCOLOR, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "IMREAD_LOAD_GDAL", IMREAD_LOAD_GDAL, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "IMREAD_REDUCED_GRAYSCALE_2", IMREAD_REDUCED_GRAYSCALE_2, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "IMREAD_REDUCED_COLOR_2", IMREAD_REDUCED_COLOR_2, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "IMREAD_REDUCED_GRAYSCALE_4", IMREAD_REDUCED_GRAYSCALE_4, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "IMREAD_REDUCED_COLOR_4", IMREAD_REDUCED_COLOR_4, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "IMREAD_REDUCED_GRAYSCALE_8", IMREAD_REDUCED_GRAYSCALE_8, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "IMREAD_REDUCED_COLOR_8", IMREAD_REDUCED_COLOR_8, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "IMREAD_IGNORE_ORIENTATION", IMREAD_IGNORE_ORIENTATION, CONST_CS | CONST_PERSISTENT);
}