#ifndef OPENCV_OPENCV_HIGHGUI_H
#define OPENCV_OPENCV_HIGHGUI_H

extern void opencv_highgui_init(int module_number);

PHP_FUNCTION(opencv_imshow);
PHP_FUNCTION(opencv_wait_key);
PHP_FUNCTION(opencv_named_window);

#endif //OPENCV_OPENCV_HIGHGUI_H
