#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php_opencv.h"

zend_class_entry *cv_ce;

const zend_function_entry cv_methods[] = {
        PHP_FE_END
};

void cv_init(){
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce,"OpenCV", "CV", cv_methods);
    cv_ce = zend_register_internal_class(&ce TSRMLS_CC);
}