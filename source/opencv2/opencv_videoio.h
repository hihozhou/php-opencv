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

#ifndef PHP_OPENCV_VIDEOIO_H
#define PHP_OPENCV_VIDEOIO_H

#include <opencv2/videoio.hpp>

extern zend_class_entry *opencv_video_capture_ce;

#define Z_PHP_VIDEO_CAPTURE_P(zv)  get_video_capture_obj(Z_OBJ_P(zv))

typedef struct _opencv_video_capture_object{
    zend_object std;
    VideoCapture *videoCapture;
}opencv_video_capture_object;

extern void opencv_videoio_init(int module_number);

static inline opencv_video_capture_object* get_video_capture_obj(zend_object *obj) {
    return (opencv_video_capture_object*)((char*)(obj) - XtOffsetOf(opencv_video_capture_object, std));
}

#endif //PHP_OPENCV_VIDEOIO_H
