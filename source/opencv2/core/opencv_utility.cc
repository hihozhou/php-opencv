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
#include "opencv_utility.h"
#include <opencv2/core.hpp>

using namespace cv;

void opencv_utility_init(int module_number){

}

/**
 * CV\getTickCount
 * @param execute_data
 * @param return_value
 */
PHP_FUNCTION(opencv_get_tick_count){
    long tick_count = getTickCount();
    RETURN_LONG(tick_count);
}


/**
 * getTickFrequency
 * @param execute_data
 * @param return_value
 */
PHP_FUNCTION(opencv_get_tick_frequency){
    double tick_frequency = getTickFrequency();
    RETURN_DOUBLE(tick_frequency);
}