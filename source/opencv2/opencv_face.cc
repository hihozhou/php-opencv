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
#include "opencv_face.h"

zend_class_entry *opencv_face_recognizer_ce;

#ifdef HAVE_OPENCV_FACE

#include <opencv2/face.hpp>
using namespace face;

#include "face/opencv_facerec.h"


/**
 * opencv_face_recognizer_methods[]
 */
const zend_function_entry opencv_face_recognizer_methods[] = {
        PHP_FE_END
};
/* }}} */


void opencv_face_recognizer_init(int module_number){
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce,OPENCV_FACE_NS, "FaceRecognizer", opencv_face_recognizer_methods);
    opencv_face_recognizer_ce = zend_register_internal_class(&ce);
}

void opencv_face_init(int module_number){
    opencv_face_recognizer_init(module_number);
    opencv_lbph_face_recognizer_init(module_number);
    opencv_base_face_recognizer_init(module_number);
}

#else

void opencv_face_init(int module_number){

}

#endif

