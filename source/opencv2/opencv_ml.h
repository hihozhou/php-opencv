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

#ifndef PHP_OPENCV_ML_H
#define PHP_OPENCV_ML_H

#include <opencv2/ml.hpp>
using namespace cv::ml;

extern void opencv_ml_init(int module_number);
extern void opencv_k_nearest_init(int module_number);
extern void opencv_ml_constants_init(int module_number);
extern void opencv_ml_sample_types_init(int module_number);


/****************************************************************************************\
*                          K-Nearest Neighbour Classifier                                *
\****************************************************************************************/

extern zend_class_entry *opencv_k_nearest_ce;

typedef struct _opencv_k_nearest_object{
    zend_object std;
    Ptr<cv::ml::KNearest> KNearest;
}opencv_k_nearest_object;

#define Z_PHP_K_NEAREST_OBJ_P(zv)  get_opencv_k_nearest_object(Z_OBJ_P(zv))

static inline opencv_k_nearest_object* get_opencv_k_nearest_object(zend_object *obj) {
    return (opencv_k_nearest_object*)((char*)(obj) - XtOffsetOf(opencv_k_nearest_object, std));
}



#endif //PHP_OPENCV_ML_H
