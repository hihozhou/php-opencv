#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php_opencv.h"
#include "source/opencv2/opencv_imgcodecs.h"
#include "source/opencv2/opencv_highgui.h"

zend_class_entry *opencv_cv_ce;

const zend_function_entry cv_methods[] = {
        PHP_ME(CV, imread, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(CV, imshow, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(CV, imwrite, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(CV, waitKey, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_FE_END
};

/**
 * register CV class
 */
void opencv_cv_init(void){
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce,"OpenCV", "CV", cv_methods);
    opencv_cv_ce = zend_register_internal_class(&ce);
}



