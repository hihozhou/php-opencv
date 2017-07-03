#ifndef OPENCV_INTERFACE_H
#define OPENCV_INTERFACE_H

extern void opencv_interface_init(int module_number);
extern PHP_FUNCTION(opencv_cv_8uc);
extern PHP_FUNCTION(opencv_cv_8sc);
extern PHP_FUNCTION(opencv_cv_16uc);
extern PHP_FUNCTION(opencv_cv_16sc);
extern PHP_FUNCTION(opencv_cv_32sc);
extern PHP_FUNCTION(opencv_cv_32fc);
extern PHP_FUNCTION(opencv_cv_64fc);
#endif //OPENCV_INTERFACE_H
