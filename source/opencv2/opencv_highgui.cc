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
//    namedWindow(window_name);
    imshow(window_name,*(obj->mat));
    RETURN_NULL();
}


/**
 * CV\waitKey
 * @param execute_data
 * @param return_value
 */
PHP_FUNCTION(opencv_wait_key){
    long delay = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "|l", &delay) == FAILURE) {
        RETURN_NULL();
    }
    waitKey((int)(delay*1000));//seconds
    RETURN_NULL();
}

/**
 * php namedWindow flags to c++ namedWindow flags
 * @param flags
 * @return
 */
int php_window_flags_to_c_flags(int flags){
    if(flags == 1){
        return WINDOW_NORMAL;
    }else if(flags==2){
        return WINDOW_AUTOSIZE;
    }else if(flags==3){
        return WINDOW_OPENGL;
    }else if(flags==4){
        return WINDOW_FULLSCREEN;
    }else if(flags==5){
        return WINDOW_FREERATIO;
    }else if(flags==6){
        return WINDOW_GUI_EXPANDED;
    }else if(flags==7){
        return WINDOW_GUI_NORMAL;
    }
    return WINDOW_AUTOSIZE;
}

/**
 * CV\namedWindow
 * @param execute_data
 * @param return_value
 */
PHP_FUNCTION(opencv_named_window){
    char *window_name;
    long window_name_len;
    long flags = 2;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s|l", &window_name, &window_name_len, &flags) == FAILURE) {
        RETURN_NULL();
    }
    namedWindow(window_name,php_window_flags_to_c_flags((int)flags));
    RETURN_NULL();
}





void opencv_highgui_init(int module_number)
{
    /**
     * ! ! Flags for CV\namedWindow
     */
    REGISTER_LONG_CONSTANT("WINDOW_NORMAL", 1, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("WINDOW_AUTOSIZE", 2, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("WINDOW_OPENGL", 3, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("WINDOW_FULLSCREEN", 4, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("WINDOW_FREERATIO", 5, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("WINDOW_GUI_EXPANDED", 6, CONST_CS | CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("WINDOW_GUI_NORMAL", 7, CONST_CS | CONST_PERSISTENT);
}