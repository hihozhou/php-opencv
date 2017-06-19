/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php_opencv.h"
#include "zend_exceptions.h"
#include "opencv_exception.h"

zend_class_entry *opencv_exception_ce;

void opencv_exception_init(void)
{
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce, "OpenCV", "Exception", NULL);
    opencv_exception_ce = zend_register_internal_class_ex(&ce, zend_exception_get_default());
}


PHP_OPENCV_API void php_opencv_throw_exception(char *error_message)
{
//    char * error_message;
//    int status = cvGetErrStatus();
//
//    if (status >= 0) {
//        return;
//    }
    int status = 1;
//    error_message = estrdup(cvErrorStr(status));
    zend_throw_exception(opencv_exception_ce, error_message, status TSRMLS_CC);
//    efree(error_message);
    return;
}