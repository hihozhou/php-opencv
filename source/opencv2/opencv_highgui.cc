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
#include "opencv_highgui.h"
#include "core/opencv_mat.h"
#include "../../opencv_exception.h"

#include <opencv2/highgui.hpp>
using namespace cv;


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
    int key = waitKey((int)delay);//millisecond
    RETURN_LONG(key);
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
 * CV\moveWindow
 * @param window_name
 * @param x
 * @param y
 */
PHP_FUNCTION(opencv_move_window){
    char *window_name;
    long window_name_len;
    long x;
    long y;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "sll", &window_name, &window_name_len, &x, &y) == FAILURE) {
        RETURN_NULL();
    }
    moveWindow(window_name,(int)x,(int)y);
    RETURN_NULL();
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

struct opencv_fcall_info_cb{
    zend_fcall_info *fci;
    zend_fcall_info_cache *fci_cache;
};


opencv_fcall_info_cb * opencv_fcall_info_cb_create(zend_fcall_info *fci_ptr, zend_fcall_info_cache *fci_cache_ptr) {
    opencv_fcall_info_cb *cb = new opencv_fcall_info_cb;
    cb->fci = new zend_fcall_info;
    cb->fci_cache = new zend_fcall_info_cache;
    memcpy(cb->fci, fci_ptr, sizeof(zend_fcall_info));
    memcpy(cb->fci_cache, fci_cache_ptr, sizeof(zend_fcall_info_cache));
    Z_TRY_ADDREF(cb->fci->function_name);//todo 滑动调或窗口销毁是释放内存
    cb->fci->param_count = 0;
    cb->fci->no_separation = 1;
    cb->fci->retval = nullptr;

    return cb;
}

void opencv_create_trackbar_callback(int pos, void* userdata){
    if(userdata != 0){
        opencv_fcall_info_cb *fci_s=(opencv_fcall_info_cb*)userdata;

        zval retval;
        zval args[1];
        ZVAL_LONG(&args[0], (long)pos);//将滑动条滑动的值传入到闭包参数中
        fci_s->fci->param_count = 1;
        fci_s->fci->params = args;
        fci_s->fci->retval = &retval;

        zend_call_function(fci_s->fci, fci_s->fci_cache);
        zval_ptr_dtor(&args[0]);
    }
}



/**
 * todo Total 1 memory leaks detected
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
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "ssll|f!",
                              &trackbarname, &trackbarname_len,
                              &winname,&winname_len,
                              &value,&count,
                              &fci, &fci_cache) == FAILURE) {
        return;
    }
    opencv_fcall_info_cb *cb = 0;
    if (fci.size > 0 && ZEND_NUM_ARGS() > 4) {//check callback param is valid
        cb = opencv_fcall_info_cb_create(&fci, &fci_cache);
    }
    int *trackbar_value_ptr = new int(value);
    createTrackbar(trackbarname, winname, trackbar_value_ptr, (int)count,opencv_create_trackbar_callback,cb);
    RETURN_NULL();
}

PHP_FUNCTION(opencv_destroy_window){
    char *winname;
    long winname_len;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &winname,&winname_len) == FAILURE) {
        return;
    }

    try{
        destroyWindow(winname);
    }catch (Exception e){
        opencv_throw_exception(e.what());
    }

    RETURN_NULL();
}

PHP_FUNCTION(opencv_get_track_bar_pos){
    char *trackbarname, *winname;
    long trackbarname_len, winname_len;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "ss", &trackbarname, &trackbarname_len, &winname, &winname_len) == FAILURE) {
        return;
    }
    RETURN_LONG(getTrackbarPos(trackbarname, winname))
}


void opencv_on_mouse_callback(int event, int x, int y, int flags, void* userdata){
    if(userdata != 0){
        opencv_fcall_info_cb *fci_s=(opencv_fcall_info_cb*)userdata;
        zval retval;
        zval args[4];
        ZVAL_LONG(&args[0], (long)event);
        ZVAL_LONG(&args[1], (long)x);
        ZVAL_LONG(&args[2], (long)y);
        ZVAL_LONG(&args[3], (long)flags);
        fci_s->fci->param_count = 4;
        fci_s->fci->params = args;
        fci_s->fci->retval = &retval;

        zend_call_function(fci_s->fci, fci_s->fci_cache);
        zval_ptr_dtor(&args[0]);
        zval_ptr_dtor(&args[1]);
        zval_ptr_dtor(&args[2]);
        zval_ptr_dtor(&args[3]);
    }
}

/**
 * CV\setMouseCallback
 * @param execute_data
 * @param return_value
 */
PHP_FUNCTION(opencv_set_mouse_callback){
    char *winname;
    long winname_len;

    zend_fcall_info fci;
    zend_fcall_info_cache fci_cache;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s|f!",
                              &winname,&winname_len,
                              &fci, &fci_cache) == FAILURE) {
        return;
    }
    opencv_fcall_info_cb *cb = 0;
    if (fci.size > 0 && ZEND_NUM_ARGS() > 1) {//check callback param is valid
        cb = opencv_fcall_info_cb_create(&fci, &fci_cache);
    }
    setMouseCallback(winname, opencv_on_mouse_callback, cb);
    RETURN_NULL();
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
    opencv_highgui_mouse_event_types_init(module_number);
    opencv_highgui_mouse_event_flags_init(module_number);
}

//! Mouse Events see cv::MouseCallback
void opencv_highgui_mouse_event_types_init(int module_number){
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "EVENT_MOUSEMOVE", EVENT_MOUSEMOVE, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "EVENT_LBUTTONDOWN", EVENT_LBUTTONDOWN, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "EVENT_RBUTTONDOWN", EVENT_RBUTTONDOWN, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "EVENT_MBUTTONDOWN", EVENT_MBUTTONDOWN, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "EVENT_LBUTTONUP", EVENT_LBUTTONUP, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "EVENT_RBUTTONUP", EVENT_RBUTTONUP, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "EVENT_MBUTTONUP", EVENT_MBUTTONUP, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "EVENT_LBUTTONDBLCLK", EVENT_LBUTTONDBLCLK, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "EVENT_RBUTTONDBLCLK", EVENT_RBUTTONDBLCLK, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "EVENT_MBUTTONDBLCLK", EVENT_MBUTTONDBLCLK, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "EVENT_MOUSEWHEEL", EVENT_MOUSEWHEEL, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "EVENT_MOUSEHWHEEL", EVENT_MOUSEHWHEEL, CONST_CS | CONST_PERSISTENT);
}

//! Mouse Event Flags see cv::MouseCallback
void opencv_highgui_mouse_event_flags_init(int module_number){
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "EVENT_FLAG_LBUTTON", EVENT_FLAG_LBUTTON, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "EVENT_FLAG_RBUTTON", EVENT_FLAG_RBUTTON, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "EVENT_FLAG_MBUTTON", EVENT_FLAG_MBUTTON, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "EVENT_FLAG_CTRLKEY", EVENT_FLAG_CTRLKEY, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "EVENT_FLAG_SHIFTKEY", EVENT_FLAG_SHIFTKEY, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "EVENT_FLAG_ALTKEY", EVENT_FLAG_ALTKEY, CONST_CS | CONST_PERSISTENT);
}