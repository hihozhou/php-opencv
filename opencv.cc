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


/* $Id$ */

#ifdef HAVE_CONFIG_H
	#include "config.h"
#endif

extern "C" {
	#include "php.h"
}

#include "php_ini.h"
#include "ext/standard/info.h"

#include "php_opencv.h"
#include "source/opencv2/opencv_imgcodecs.h"
#include "source/opencv2/opencv_highgui.h"
#include "source/opencv2/opencv_imgproc.h"
#include "source/opencv2/core/opencv_type.h"
#include "source/opencv2/core/opencv_mat.h"
#include "source/opencv2/core/hal/opencv_interface.h"
#include "opencv_exception.h"
#include "source/opencv2/opencv_core.h"
#include "source/opencv2/core/opencv_base.h"
#include "source/opencv2/core/opencv_persistence.h"
#include "source/opencv2/opencv_objdetect.h"
#include "source/opencv2/opencv_videoio.h"
#include "source/opencv2/opencv_face.h"
#include "source/opencv2/core/opencv_utility.h"
#include "source/opencv2/opencv_ml.h"
#include "source/opencv2/core/opencv_cvdef.h"

#include <iostream>
//include opencv code
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;



/* If you declare any globals in php_opencv.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(opencv)
*/

/* True global resources - no need for thread safety here */
static int le_opencv;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("opencv.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_opencv_globals, opencv_globals)
    STD_PHP_INI_ENTRY("opencv.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_opencv_globals, opencv_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_opencv_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_opencv_compiled)
{
    char *arg = NULL;
	size_t arg_len, len;
	zend_string *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	strg = strpprintf(0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "opencv", arg);

	RETURN_STR(strg);
}


PHP_FUNCTION(opencv_test)
{
    std::cout<<"This C++ output!"<<std::endl;
    php_printf("This is opencv extension!");
    Mat mat = cv::imread("C:\\Users\\hiho\\Desktop\\test.jpg");
    cv::imshow("test",mat);
    cv::waitKey(0);
	RETURN_TRUE;
}


/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_opencv_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_opencv_init_globals(zend_opencv_globals *opencv_globals)
{
	opencv_globals->global_value = 0;
	opencv_globals->global_string = NULL;
}
*/
/* }}} */


/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(opencv)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/
	//module_number注册常量的宏需要，如：REGISTER_NS_LONG_CONSTANT
    opencv_interface_init(module_number);
    opencv_imgcodecs_init(module_number);
    opencv_highgui_init(module_number);
    opencv_exception_init(module_number);
    opencv_mat_init(module_number);//Opencv Mat 逻辑
    opencv_type_init(module_number);
    opencv_imgproc_init(module_number);
	opencv_core_init(module_number);
    opencv_border_types_init(module_number);
	opencv_decomp_types_init(module_number);
	opencv_file_storage_init(module_number);
	opencv_objdetect_init(module_number);
	opencv_videoio_init(module_number);
    opencv_face_init(module_number);
	opencv_ml_init(module_number);
    opencv_cvdef_init(module_number);

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(opencv)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(opencv)
{
#if defined(COMPILE_DL_OPENCV) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(opencv)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(opencv)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "opencv support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ opencv_functions[]
 *
 * Every user visible function must have an entry in opencv_functions[].
 */
const zend_function_entry opencv_functions[] = {
	PHP_FE(confirm_opencv_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE(opencv_test,	NULL)
    ZEND_NS_NAMED_FE(OPENCV_NS, CV_8UC, ZEND_FN(opencv_cv_8uc), NULL)
    ZEND_NS_NAMED_FE(OPENCV_NS, CV_8SC, ZEND_FN(opencv_cv_8sc), NULL)
    ZEND_NS_NAMED_FE(OPENCV_NS, CV_16UC, ZEND_FN(opencv_cv_16uc), NULL)
    ZEND_NS_NAMED_FE(OPENCV_NS, CV_16SC, ZEND_FN(opencv_cv_16sc), NULL)
    ZEND_NS_NAMED_FE(OPENCV_NS, CV_32SC, ZEND_FN(opencv_cv_32sc), NULL)
    ZEND_NS_NAMED_FE(OPENCV_NS, CV_32FC, ZEND_FN(opencv_cv_32fc), NULL)
    ZEND_NS_NAMED_FE(OPENCV_NS, CV_64FC, ZEND_FN(opencv_cv_64fc), NULL)
    ZEND_NS_NAMED_FE(OPENCV_NS, imread, ZEND_FN(opencv_imread), NULL)
    ZEND_NS_NAMED_FE(OPENCV_NS, imwrite, ZEND_FN(opencv_imwrite), NULL)
    ZEND_NS_NAMED_FE(OPENCV_NS, imshow, ZEND_FN(opencv_imshow), NULL)
    ZEND_NS_NAMED_FE(OPENCV_NS, waitKey, ZEND_FN(opencv_wait_key), NULL)
    ZEND_NS_NAMED_FE(OPENCV_NS, moveWindow, ZEND_FN(opencv_move_window), NULL)
    ZEND_NS_NAMED_FE(OPENCV_NS, namedWindow, ZEND_FN(opencv_named_window), NULL)
    ZEND_NS_NAMED_FE(OPENCV_NS, cvtColor, ZEND_FN(opencv_cv_t_color), NULL)
    ZEND_NS_NAMED_FE(OPENCV_NS, ellipse, ZEND_FN(opencv_ellipse), NULL)
    ZEND_NS_NAMED_FE(OPENCV_NS, circle, ZEND_FN(opencv_circle), NULL)
    ZEND_NS_NAMED_FE(OPENCV_NS, fillPoly, ZEND_FN(opencv_fill_poly), opencv_fill_poly_arginfo)
    ZEND_NS_NAMED_FE(OPENCV_NS, line, ZEND_FN(opencv_line), NULL)
    ZEND_NS_NAMED_FE(OPENCV_NS, rectangle, ZEND_FN(opencv_rectangle), NULL)
    ZEND_NS_NAMED_FE(OPENCV_NS, rectangleByPoint, ZEND_FN(opencv_rectangle_by_point), NULL)
    ZEND_NS_NAMED_FE(OPENCV_NS, rectangleByRect, ZEND_FN(opencv_rectangle_by_rect), NULL)
    ZEND_NS_NAMED_FE(OPENCV_NS, addWeighted, ZEND_FN(opencv_add_weighted), opencv_add_weighted_arginfo)
    ZEND_NS_NAMED_FE(OPENCV_NS, split, ZEND_FN(opencv_split), NULL)
    ZEND_NS_NAMED_FE(OPENCV_NS, merge, ZEND_FN(opencv_merge), opencv_merge_arginfo)
    ZEND_NS_NAMED_FE(OPENCV_NS, createTrackbar, ZEND_FN(opencv_create_trackbar), NULL)
    ZEND_NS_NAMED_FE(OPENCV_NS, destroyWindow, ZEND_FN(opencv_destroy_window), NULL)
    ZEND_NS_NAMED_FE(OPENCV_NS, getOptimalDFTSize, ZEND_FN(opencv_get_optimal_dft_size), NULL)
    ZEND_NS_NAMED_FE(OPENCV_NS, copyMakeBorder, ZEND_FN(opencv_copy_make_border), opencv_copy_make_border_arginfo)
    ZEND_NS_NAMED_FE(OPENCV_NS, dft, ZEND_FN(opencv_dft), opencv_dft_arginfo)
    ZEND_NS_NAMED_FE(OPENCV_NS, magnitude, ZEND_FN(opencv_magnitude), opencv_magnitude_arginfo)
    ZEND_NS_NAMED_FE(OPENCV_NS, add, ZEND_FN(opencv_add), opencv_add_arginfo)
    ZEND_NS_NAMED_FE(OPENCV_NS, log, ZEND_FN(opencv_log), opencv_log_arginfo)
    ZEND_NS_NAMED_FE(OPENCV_NS, normalize, ZEND_FN(opencv_normalize), opencv_normalize_arginfo)
    ZEND_NS_NAMED_FE(OPENCV_NS, equalizeHist, ZEND_FN(opencv_equalize_hist), opencv_equalize_hist_arginfo)
    ZEND_NS_NAMED_FE(OPENCV_NS, resize, ZEND_FN(opencv_resize), opencv_resize_arginfo)
    ZEND_NS_NAMED_FE(OPENCV_NS, putText, ZEND_FN(opencv_put_text), NULL)
    ZEND_NS_NAMED_FE(OPENCV_NS, absdiff, ZEND_FN(opencv_absdiff), opencv_absdiff_arginfo)
    ZEND_NS_NAMED_FE(OPENCV_NS, getTrackBarPos, ZEND_FN(opencv_get_track_bar_pos), NULL)
    ZEND_NS_NAMED_FE(OPENCV_NS, blur, ZEND_FN(opencv_blur), opencv_blur_arginfo)
    ZEND_NS_NAMED_FE(OPENCV_NS, GaussianBlur, ZEND_FN(opencv_gaussian_blur), opencv_gaussian_blur_arginfo)
    ZEND_NS_NAMED_FE(OPENCV_NS, medianBlur, ZEND_FN(opencv_median_blur), opencv_median_blur_arginfo)
    ZEND_NS_NAMED_FE(OPENCV_NS, bilateralFilter, ZEND_FN(opencv_bilateral_filter), opencv_bilateral_filter_arginfo)
    ZEND_NS_NAMED_FE(OPENCV_NS, dilate, ZEND_FN(opencv_dilate), opencv_dilate_arginfo)
    ZEND_NS_NAMED_FE(OPENCV_NS, erode, ZEND_FN(opencv_erode), opencv_erode_arginfo)
    ZEND_NS_NAMED_FE(OPENCV_NS, filter2D, ZEND_FN(opencv_filter2D), opencv_filter2D_arginfo)
    ZEND_NS_NAMED_FE(OPENCV_NS, Sobel, ZEND_FN(opencv_sobel), opencv_sobel_arginfo)
    ZEND_NS_NAMED_FE(OPENCV_NS, Scharr, ZEND_FN(opencv_scharr), opencv_scharr_arginfo)
    ZEND_NS_NAMED_FE(OPENCV_NS, Laplacian, ZEND_FN(opencv_laplacian), opencv_laplacian_arginfo)
    ZEND_NS_NAMED_FE(OPENCV_NS, convertScaleAbs, ZEND_FN(opencv_convert_scale_abs), opencv_convert_scale_abs_arginfo)
	ZEND_NS_NAMED_FE(OPENCV_NS, getStructuringElement, ZEND_FN(opencv_get_structuring_element), opencv_get_structuring_element_arginfo)
    ZEND_NS_NAMED_FE(OPENCV_NS, threshold, ZEND_FN(opencv_threshold), opencv_threshold_arginfo)
    ZEND_NS_NAMED_FE(OPENCV_NS, morphologyEx, ZEND_FN(opencv_morphology_ex), opencv_morphology_ex_arginfo)
    ZEND_NS_NAMED_FE(OPENCV_NS, LUT, ZEND_FN(opencv_lut), opencv_lut_arginfo)
    ZEND_NS_NAMED_FE(OPENCV_NS, getTickCount, ZEND_FN(opencv_get_tick_count), NULL)
    ZEND_NS_NAMED_FE(OPENCV_NS, getTickFrequency, ZEND_FN(opencv_get_tick_frequency), NULL)
    ZEND_NS_NAMED_FE(OPENCV_NS, floodFill, ZEND_FN(opencv_flood_fill), opencv_flood_fill_arginfo)
    ZEND_NS_NAMED_FE(OPENCV_NS, setMouseCallback, ZEND_FN(opencv_set_mouse_callback), NULL)
    ZEND_NS_NAMED_FE(OPENCV_NS, adaptiveThreshold, ZEND_FN(opencv_adaptive_threshold), opencv_adaptive_threshold_arginfo)
    ZEND_NS_NAMED_FE(OPENCV_NS, findContoursWithoutHierarchy, ZEND_FN(opencv_find_contours_without_hierarchy), opencv_find_contours_without_hierarchy_arginfo)
    ZEND_NS_NAMED_FE(OPENCV_NS, drawContours, ZEND_FN(opencv_draw_contours), opencv_draw_contours_arginfo)
    ZEND_NS_NAMED_FE(OPENCV_NS, boundingRect, ZEND_FN(opencv_bounding_rect), NULL)
    ZEND_NS_NAMED_FE(OPENCV_NS, getRotationMatrix2D, ZEND_FN(opencv_get_rotation_matrix2D), NULL)
    ZEND_NS_NAMED_FE(OPENCV_NS, warpAffine, ZEND_FN(opencv_warp_affine), opencv_warp_affine_arginfo)
    ZEND_NS_NAMED_FE(OPENCV_NS, getRectSubPix, ZEND_FN(opencv_get_rect_sub_pix), opencv_get_rect_sub_pix_arginfo)
    ZEND_NS_NAMED_FE(OPENCV_NS, getPerspectiveTransform, ZEND_FN(opencv_get_perspective_transform), opencv_get_perspective_transform_arginfo)
    ZEND_NS_NAMED_FE(OPENCV_NS, warpPerspective, ZEND_FN(opencv_warp_perspective), opencv_warp_perspective_arginfo)
	PHP_FE_END	/* Must be the last line in opencv_functions[] */
};
/* }}} */

/* {{{ opencv_module_entry
 */
zend_module_entry opencv_module_entry = {
	STANDARD_MODULE_HEADER,
	"opencv",
	opencv_functions,
	PHP_MINIT(opencv),
	PHP_MSHUTDOWN(opencv),
	PHP_RINIT(opencv),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(opencv),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(opencv),
	PHP_OPENCV_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_OPENCV
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(opencv)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
