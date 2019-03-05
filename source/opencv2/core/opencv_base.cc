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

#include "../../../php_opencv.h"
#include "opencv_base.h"
#include <opencv2/core/base.hpp>
using namespace cv;


void opencv_border_types_init(int module_number){
    //! Various border types, image boundaries are denoted with `|`
    //! @see borderInterpolate, copyMakeBorde

    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "BORDER_CONSTANT", BorderTypes::BORDER_CONSTANT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "BORDER_REPLICATE", BorderTypes::BORDER_REPLICATE, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "BORDER_REFLECT", BorderTypes::BORDER_REFLECT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "BORDER_WRAP", BorderTypes::BORDER_WRAP, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "BORDER_REFLECT_101", BorderTypes::BORDER_REFLECT_101, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "BORDER_TRANSPARENT", BorderTypes::BORDER_TRANSPARENT, CONST_CS | CONST_PERSISTENT);

    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "BORDER_REFLECT101", BorderTypes::BORDER_REFLECT101, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "BORDER_DEFAULT", BorderTypes::BORDER_DEFAULT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "BORDER_ISOLATED", BorderTypes::BORDER_ISOLATED, CONST_CS | CONST_PERSISTENT);
}

void opencv_decomp_types_init(int module_number){

    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "DECOMP_LU", DecompTypes::DECOMP_LU, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "DECOMP_SVD", DecompTypes::DECOMP_SVD, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "DECOMP_EIG", DecompTypes::DECOMP_EIG, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "DECOMP_CHOLESKY", DecompTypes::DECOMP_CHOLESKY, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "DECOMP_QR", DecompTypes::DECOMP_QR, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "DECOMP_NORMAL", DecompTypes::DECOMP_NORMAL, CONST_CS | CONST_PERSISTENT);
}
