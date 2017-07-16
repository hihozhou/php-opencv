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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif


void opencv_border_types_init(int module_number){
    //! Various border types, image boundaries are denoted with `|`
    //! @see borderInterpolate, copyMakeBorde
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "BORDER_CONSTANT", BORDER_CONSTANT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "BORDER_REPLICATE", BORDER_REPLICATE, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "BORDER_REFLECT", BORDER_REFLECT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "BORDER_WRAP", BORDER_WRAP, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "BORDER_REFLECT_101", BORDER_REFLECT_101, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "BORDER_TRANSPARENT", BORDER_TRANSPARENT, CONST_CS | CONST_PERSISTENT);

    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "BORDER_REFLECT101", BORDER_REFLECT101, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "BORDER_DEFAULT", BORDER_DEFAULT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "BORDER_ISOLATED", BORDER_ISOLATED, CONST_CS | CONST_PERSISTENT);
}
