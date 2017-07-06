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
    opencv_mat_object *obj = Z_PHP_MAT_OBJ_P(object);
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
 * @param window_name
 * @param flags
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


/**
 * //todo c++ createTrackbar 跳转事件调用php传入的闭包
 * CV\createTrackbar
 * @param execute_data
 * @param return_value
 */
PHP_FUNCTION(opencv_create_trackbar){
    char *trackbarname, *winname;
    long value, count, trackbarname_len,winname_len;
    zval retval;
    zend_fcall_info fci;
    zend_fcall_info_cache fci_cache;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "ssll|f",
                              &trackbarname, &trackbarname_len,
                              &winname,&winname_len,
                              &value,&count,
                              &fci, &fci_cache) == FAILURE) {
        return;
    }
    int *trackbar_value_ptr = new int(value);
    createTrackbar(trackbarname, winname, trackbar_value_ptr, (int)count);
    std::cout<<*trackbar_value_ptr<<std::endl;
//    ContrastAndBright(*trackbar_value_ptr,0);

    RETURN_NULL();

//    zval args[1];
//    ZVAL_LONG(&args[0], 1);
//    fci.param_count = 1;
//    fci.params = args;
//    fci.retval = &retval;
//
//
//    if (zend_call_function(&fci, &fci_cache) == SUCCESS && Z_TYPE(retval) != IS_UNDEF) {
//        zval_ptr_dtor(&args[0]);
////        RETURN_ZVAL(&retval,1,1);
////        ZVAL_COPY_VALUE(return_value, &retval);
//    } else {
//        RETURN_FALSE;
//    }

}



void opencv_highgui_init(int module_number)
{
    /**
     * ! ! Flags for CV\namedWindow
     */
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "WINDOW_NORMAL", 1, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "WINDOW_AUTOSIZE", 2, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "WINDOW_OPENGL", 3, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "WINDOW_FULLSCREEN", 4, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "WINDOW_FREERATIO", 5, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "WINDOW_GUI_EXPANDED", 6, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "WINDOW_GUI_NORMAL", 7, CONST_CS | CONST_PERSISTENT);
}