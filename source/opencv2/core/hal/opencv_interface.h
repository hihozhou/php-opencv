#ifndef OPENCV_INTERFACE_H
#define OPENCV_INTERFACE_H

extern void opencv_interface_init(int module_number);
extern PHP_FUNCTION(cv_8uc_n);
extern PHP_FUNCTION(cv_8sc_n);
extern PHP_FUNCTION(cv_16uc_n);
extern PHP_FUNCTION(cv_16sc_n);
extern PHP_FUNCTION(cv_32sc_n);
extern PHP_FUNCTION(cv_32fc_n);
extern PHP_FUNCTION(cv_64fc_n);
#endif //OPENCV_INTERFACE_H
