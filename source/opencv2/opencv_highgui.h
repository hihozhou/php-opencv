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


#ifndef PHP_OPENCV_HIGHGUI_H
#define PHP_OPENCV_HIGHGUI_H

extern void opencv_highgui_init(int module_number);
extern void opencv_highgui_mouse_event_types_init(int module_number);
extern void opencv_highgui_mouse_event_flags_init(int module_number);

PHP_FUNCTION(opencv_imshow);
PHP_FUNCTION(opencv_wait_key);
PHP_FUNCTION(opencv_move_window);
PHP_FUNCTION(opencv_named_window);
ZEND_BEGIN_ARG_INFO_EX(opencv_create_trackbar_arginfo, 0, 0, 5)
                ZEND_ARG_INFO(0, trackbarname)
                ZEND_ARG_INFO(0, winname)
                ZEND_ARG_INFO(1, value)
                ZEND_ARG_INFO(0, count)
                ZEND_ARG_INFO(0, onChange)
ZEND_END_ARG_INFO()
PHP_FUNCTION(opencv_create_trackbar);
PHP_FUNCTION(opencv_destroy_window);
PHP_FUNCTION(opencv_get_track_bar_pos);
PHP_FUNCTION(opencv_set_mouse_callback);

#endif //OPENCV_OPENCV_HIGHGUI_H
