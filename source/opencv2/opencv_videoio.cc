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
#include "opencv_videoio.h"

zend_class_entry *opencv_video_capture_ce;

zend_object_handlers opencv_video_capture_object_handlers;

zend_object* opencv_video_capture_create_handler(zend_class_entry *type)
{
    size_t size = sizeof(opencv_video_capture_object);
    opencv_video_capture_object *obj = (opencv_video_capture_object *)ecalloc(1,size);
    memset(obj, 0, sizeof(opencv_video_capture_object));
    zend_object_std_init(&obj->std, type);
    object_properties_init(&obj->std, type);
    obj->std.ce = type;
    obj->std.handlers = &opencv_video_capture_object_handlers;
    return &obj->std;
}

PHP_METHOD(opencv_video_capture, __construct)
{
    opencv_video_capture_object *obj = Z_PHP_VIDEO_CAPTURE_P(getThis());
    obj->videoCapture = new VideoCapture();
}

/**
 * opencv_video_capture_methods[]
 */
const zend_function_entry opencv_video_capture_methods[] = {
        PHP_ME(opencv_video_capture, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
        PHP_FE_END
};
/* }}} */

void opencv_video_capture_free_obj(zend_object *object)
{
    opencv_video_capture_object *obj;
    obj = get_video_capture_obj(object);
    delete obj->videoCapture;
    zend_object_std_dtor(object);
}

void opencv_video_capture_init(int module_number){
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce,OPENCV_NS, "VideoCapture", opencv_video_capture_methods);
    opencv_video_capture_ce = zend_register_internal_class(&ce);

    opencv_video_capture_ce->create_object = opencv_video_capture_create_handler;
    memcpy(&opencv_video_capture_object_handlers,
           zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    opencv_video_capture_object_handlers.clone_obj = NULL;
    opencv_video_capture_object_handlers.free_obj = opencv_video_capture_free_obj;
}

void opencv_videoio_init(int module_number){
    opencv_video_capture_init(module_number);
}