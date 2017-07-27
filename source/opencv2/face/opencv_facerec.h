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


#ifndef PHP_OPENCV_FACEREC_H
#define PHP_OPENCV_FACEREC_H

#include "../../../php_opencv.h"

#include <opencv2/face.hpp>
using namespace cv::face;


/**
 * -----------------------------------【CV\LBPHFaceRecognizer】-------------------------
 *
 * -------------------------------------------------------------------------------------
 */
extern void opencv_lbph_face_recognizer_init(int module_number);

#define Z_PHP_LBPH_FACE_RECOGNIZER_OBJ_P(zv)  get_lbph_face_recognizer_obj(Z_OBJ_P(zv))

typedef struct _opencv_lbph_face_recognizer_object{
    zend_object std;
    Ptr<LBPHFaceRecognizer> faceRecognizer;
}opencv_lbph_face_recognizer_object;


/**
 * @param obj
 * @return
 */
static inline opencv_lbph_face_recognizer_object* get_lbph_face_recognizer_obj(zend_object *obj) {
    return (opencv_lbph_face_recognizer_object*)((char*)(obj) - XtOffsetOf(opencv_lbph_face_recognizer_object, std));
}


/**
 * -----------------------------------【CV\BaseFaceRecognizer】-------------------------
 *
 * -------------------------------------------------------------------------------------
 */
extern void opencv_base_face_recognizer_init(int module_number);


#endif //PHP_OPENCV_FACEREC_H
