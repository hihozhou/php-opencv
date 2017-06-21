#include "../../php_opencv.h"
#include "opencv_highgui.h"
#include "core/opencv_mat.h"


#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

/**
 * //todo only cli can call this function
 * CV\imshow
 * @param execute_data
 * @param return_value
 */
PHP_FUNCTION(opencv_imshow){
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
 * CV\waitKey
 * @param execute_data
 * @param return_value
 */
PHP_FUNCTION(opencv_waitKey){
    long delay = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "|l", &delay) == FAILURE) {
        RETURN_NULL();
    }
    waitKey((int)(delay*1000));//seconds
    RETURN_NULL();
}



void opencv_highgui_init(int module_number)
{
    /**
     * ! Flags for CV::imshow
     */
//    REGISTER_LONG_CONSTANT("WINDOW_NORMAL", WINDOW_NORMAL, CONST_CS | CONST_PERSISTENT);
//    REGISTER_LONG_CONSTANT("WINDOW_AUTOSIZE", WINDOW_AUTOSIZE, CONST_CS | CONST_PERSISTENT);
//    REGISTER_LONG_CONSTANT("WINDOW_OPENGL", WINDOW_OPENGL, CONST_CS | CONST_PERSISTENT);
//    REGISTER_LONG_CONSTANT("WINDOW_FULLSCREEN", WINDOW_FULLSCREEN, CONST_CS | CONST_PERSISTENT);
//    REGISTER_LONG_CONSTANT("WINDOW_FREERATIO", WINDOW_FREERATIO, CONST_CS | CONST_PERSISTENT);
//    REGISTER_LONG_CONSTANT("WINDOW_GUI_EXPANDED", WINDOW_GUI_EXPANDED, CONST_CS | CONST_PERSISTENT);
//    REGISTER_LONG_CONSTANT("WINDOW_GUI_NORMAL", WINDOW_GUI_NORMAL, CONST_CS | CONST_PERSISTENT);
}