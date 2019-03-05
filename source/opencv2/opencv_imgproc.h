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

#ifndef PHP_OPENCV_IMGPROC_H
#define PHP_OPENCV_IMGPROC_H

void opencv_imgproc_init(int module_number);
void opencv_color_conversion_code_init(int module_number);
void opencv_line_type_init(int module_number);
void opencv_morph_shapes_init(int module_number);
void opencv_morph_types_init(int module_number);
void opencv_flood_fill_flags_init(int module_number);
void opencv_threshold_types_init(int module_number);
void opencv_adaptive_threshold_types_init(int module_number);
void opencv_retrieval_modes_init(int module_number);
void opencv_contour_approximation_modes_init(int module_number);

PHP_FUNCTION(opencv_cv_t_color);
PHP_FUNCTION(opencv_ellipse);
PHP_FUNCTION(opencv_circle);
ZEND_BEGIN_ARG_INFO_EX(opencv_fill_poly_arginfo, 0, 0, 7)
                ZEND_ARG_INFO(0, img)
                ZEND_ARG_INFO(0, pts)//point array
                ZEND_ARG_INFO(0, ncontours)
                ZEND_ARG_INFO(0, color)
                ZEND_ARG_INFO(0, lineType)
                ZEND_ARG_INFO(0, shift)
                ZEND_ARG_INFO(1, offset)
ZEND_END_ARG_INFO()
PHP_FUNCTION(opencv_fill_poly);

PHP_FUNCTION(opencv_line);
PHP_FUNCTION(opencv_rectangle);
PHP_FUNCTION(opencv_rectangle_by_point);
PHP_FUNCTION(opencv_rectangle_by_rect);

ZEND_BEGIN_ARG_INFO_EX(opencv_equalize_hist_arginfo, 0, 0, 2)
                ZEND_ARG_INFO(0, src)
                ZEND_ARG_INFO(1, dst)
ZEND_END_ARG_INFO()
PHP_FUNCTION(opencv_equalize_hist);

ZEND_BEGIN_ARG_INFO_EX(opencv_resize_arginfo, 0, 0, 6)
                ZEND_ARG_INFO(0, src)
                ZEND_ARG_INFO(1, dst)
                ZEND_ARG_INFO(0, dsize_zval)
                ZEND_ARG_INFO(0, fx)
                ZEND_ARG_INFO(0, fy)
                ZEND_ARG_INFO(0, interpolation)
ZEND_END_ARG_INFO()
PHP_FUNCTION(opencv_resize);
PHP_FUNCTION(opencv_put_text);

ZEND_BEGIN_ARG_INFO_EX(opencv_blur_arginfo, 0, 0, 5)
                ZEND_ARG_INFO(0, src)
                ZEND_ARG_INFO(1, dst)
                ZEND_ARG_INFO(0, ksize)
                ZEND_ARG_INFO(0, anchor)
                ZEND_ARG_INFO(0, borderType)
ZEND_END_ARG_INFO()
PHP_FUNCTION(opencv_blur);
ZEND_BEGIN_ARG_INFO_EX(opencv_gaussian_blur_arginfo, 0, 0, 6)
                ZEND_ARG_INFO(0, src)
                ZEND_ARG_INFO(1, dst)
                ZEND_ARG_INFO(0, ksize)
                ZEND_ARG_INFO(0, sigmaX)
                ZEND_ARG_INFO(0, sigmaY)
                ZEND_ARG_INFO(0, borderType)
ZEND_END_ARG_INFO()
PHP_FUNCTION(opencv_gaussian_blur);
ZEND_BEGIN_ARG_INFO_EX(opencv_median_blur_arginfo, 0, 0, 3)
                ZEND_ARG_INFO(0, src)
                ZEND_ARG_INFO(1, dst)
                ZEND_ARG_INFO(0, ksize)
ZEND_END_ARG_INFO()
PHP_FUNCTION(opencv_median_blur);
ZEND_BEGIN_ARG_INFO_EX(opencv_bilateral_filter_arginfo, 0, 0, 6)
                ZEND_ARG_INFO(0, src)
                ZEND_ARG_INFO(1, dst)
                ZEND_ARG_INFO(0, d)
                ZEND_ARG_INFO(0, sigmaColor)
                ZEND_ARG_INFO(0, sigmaSpace)
                ZEND_ARG_INFO(0, borderType)
ZEND_END_ARG_INFO()
PHP_FUNCTION(opencv_bilateral_filter);

ZEND_BEGIN_ARG_INFO_EX(opencv_dilate_arginfo, 0, 0, 7)
                ZEND_ARG_INFO(0, src)
                ZEND_ARG_INFO(1, dst)
                ZEND_ARG_INFO(0, kernel)
                ZEND_ARG_INFO(0, anchor)
                ZEND_ARG_INFO(0, iterations)
                ZEND_ARG_INFO(0, borderType)
                ZEND_ARG_INFO(0, borderValue)
ZEND_END_ARG_INFO()
PHP_FUNCTION(opencv_dilate);

ZEND_BEGIN_ARG_INFO_EX(opencv_erode_arginfo, 0, 0, 7)
                ZEND_ARG_INFO(0, src)
                ZEND_ARG_INFO(1, dst)
                ZEND_ARG_INFO(0, kernel)
                ZEND_ARG_INFO(0, anchor)
                ZEND_ARG_INFO(0, iterations)
                ZEND_ARG_INFO(0, borderType)
                ZEND_ARG_INFO(0, borderValue)
ZEND_END_ARG_INFO()
PHP_FUNCTION(opencv_erode);

ZEND_BEGIN_ARG_INFO_EX(opencv_filter2D_arginfo, 0, 0, 7)
                ZEND_ARG_INFO(0, src)
                ZEND_ARG_INFO(1, dst)
                ZEND_ARG_INFO(0, ddepth)
                ZEND_ARG_INFO(0, kernel)
                ZEND_ARG_INFO(0, anchor)
                ZEND_ARG_INFO(0, delta)
                ZEND_ARG_INFO(0, border_type)
ZEND_END_ARG_INFO()
PHP_FUNCTION(opencv_filter2D);

ZEND_BEGIN_ARG_INFO_EX(opencv_sobel_arginfo, 0, 0, 9)
                ZEND_ARG_INFO(0, src)
                ZEND_ARG_INFO(1, dst)
                ZEND_ARG_INFO(0, ddepth)
                ZEND_ARG_INFO(0, dx)
                ZEND_ARG_INFO(0, dy)
                ZEND_ARG_INFO(0, ksize)
                ZEND_ARG_INFO(0, scale)
                ZEND_ARG_INFO(0, delta)
                ZEND_ARG_INFO(0, border_type)
ZEND_END_ARG_INFO()
PHP_FUNCTION(opencv_sobel);

ZEND_BEGIN_ARG_INFO_EX(opencv_scharr_arginfo, 0, 0, 8)
                ZEND_ARG_INFO(0, src)
                ZEND_ARG_INFO(1, dst)
                ZEND_ARG_INFO(0, ddepth)
                ZEND_ARG_INFO(0, dx)
                ZEND_ARG_INFO(0, dy)
                ZEND_ARG_INFO(0, scale)
                ZEND_ARG_INFO(0, delta)
                ZEND_ARG_INFO(0, border_type)
ZEND_END_ARG_INFO()
PHP_FUNCTION(opencv_scharr);

ZEND_BEGIN_ARG_INFO_EX(opencv_laplacian_arginfo, 0, 0, 7)
                ZEND_ARG_INFO(0, src)
                ZEND_ARG_INFO(1, dst)
                ZEND_ARG_INFO(0, ddepth)
                ZEND_ARG_INFO(0, ksize)
                ZEND_ARG_INFO(0, scale)
                ZEND_ARG_INFO(0, delta)
                ZEND_ARG_INFO(0, border_type)
ZEND_END_ARG_INFO()
PHP_FUNCTION(opencv_laplacian);

ZEND_BEGIN_ARG_INFO_EX(opencv_convert_scale_abs_arginfo, 0, 0, 4)
                ZEND_ARG_INFO(0, src)
                ZEND_ARG_INFO(1, dst)
                ZEND_ARG_INFO(0, alpha)
                ZEND_ARG_INFO(0, beta)
ZEND_END_ARG_INFO()
PHP_FUNCTION(opencv_convert_scale_abs);

ZEND_BEGIN_ARG_INFO_EX(opencv_get_structuring_element_arginfo, 0, 0, 3)
                ZEND_ARG_INFO(0, shape)
                ZEND_ARG_INFO(0, ksize)
                ZEND_ARG_INFO(0, anchor)
ZEND_END_ARG_INFO()
PHP_FUNCTION(opencv_get_structuring_element);

ZEND_BEGIN_ARG_INFO_EX(opencv_threshold_arginfo, 0, 0, 5)
                ZEND_ARG_INFO(0, src)
                ZEND_ARG_INFO(1, dst)
                ZEND_ARG_INFO(0, thresh)
                ZEND_ARG_INFO(0, maxval)
                ZEND_ARG_INFO(0, type)
ZEND_END_ARG_INFO()
PHP_FUNCTION(opencv_threshold);

ZEND_BEGIN_ARG_INFO_EX(opencv_adaptive_threshold_arginfo, 0, 0, 7)
                ZEND_ARG_INFO(0, src)
                ZEND_ARG_INFO(1, dst)
                ZEND_ARG_INFO(0, maxValue)
                ZEND_ARG_INFO(0, adaptiveMethod)
                ZEND_ARG_INFO(0, thresholdType)
                ZEND_ARG_INFO(0, blockSize)
                ZEND_ARG_INFO(0, C)
ZEND_END_ARG_INFO()
PHP_FUNCTION(opencv_adaptive_threshold);

ZEND_BEGIN_ARG_INFO_EX(opencv_morphology_ex_arginfo, 0, 0, 8)
                ZEND_ARG_INFO(0, src)
                ZEND_ARG_INFO(1, dst)
                ZEND_ARG_INFO(0, op)
                ZEND_ARG_INFO(0, kernel)
                ZEND_ARG_INFO(0, anchor)
                ZEND_ARG_INFO(0, iterations)
                ZEND_ARG_INFO(0, borderType)
                ZEND_ARG_INFO(0, borderValue)
ZEND_END_ARG_INFO()
PHP_FUNCTION(opencv_morphology_ex);

ZEND_BEGIN_ARG_INFO_EX(opencv_flood_fill_arginfo, 0, 0, 8)
                ZEND_ARG_INFO(0, image)
                ZEND_ARG_INFO(0, seedPoint)
                ZEND_ARG_INFO(0, newVal)
                ZEND_ARG_INFO(0, mask)
                ZEND_ARG_INFO(0, rect)
                ZEND_ARG_INFO(0, loDiff)
                ZEND_ARG_INFO(0, upDiff)
                ZEND_ARG_INFO(0, flags)
ZEND_END_ARG_INFO()
PHP_FUNCTION(opencv_flood_fill);

ZEND_BEGIN_ARG_INFO_EX(opencv_find_contours_without_hierarchy_arginfo, 0, 0, 5)
                ZEND_ARG_INFO(0, image)
                ZEND_ARG_INFO(1, contours)
                ZEND_ARG_INFO(0, mode)
                ZEND_ARG_INFO(0, method)
                ZEND_ARG_INFO(1, offset)
ZEND_END_ARG_INFO()
PHP_FUNCTION(opencv_find_contours_without_hierarchy);

ZEND_BEGIN_ARG_INFO_EX(opencv_draw_contours_arginfo, 0, 0, 9)
                ZEND_ARG_INFO(0, image)
                ZEND_ARG_INFO(1, contours)
                ZEND_ARG_INFO(0, contourIdx)
                ZEND_ARG_INFO(0, color)
                ZEND_ARG_INFO(0, thickness)
                ZEND_ARG_INFO(0, lineType)
                ZEND_ARG_INFO(0, hierarchy)
                ZEND_ARG_INFO(0, maxLevel)
                ZEND_ARG_INFO(1, offset)
ZEND_END_ARG_INFO()
PHP_FUNCTION(opencv_draw_contours);
PHP_FUNCTION(opencv_bounding_rect);
PHP_FUNCTION(opencv_get_rotation_matrix2D);
ZEND_BEGIN_ARG_INFO_EX(opencv_warp_affine_arginfo, 0, 0, 7)
                ZEND_ARG_INFO(0, src)
                ZEND_ARG_INFO(1, dst)
                ZEND_ARG_INFO(0, M)
                ZEND_ARG_INFO(0, dsize)
                ZEND_ARG_INFO(0, flags)
                ZEND_ARG_INFO(0, borderMode)
                ZEND_ARG_INFO(0, borderValue)
ZEND_END_ARG_INFO()
PHP_FUNCTION(opencv_warp_affine);
ZEND_BEGIN_ARG_INFO_EX(opencv_get_rect_sub_pix_arginfo, 0, 0, 5)
                ZEND_ARG_INFO(0, image)
                ZEND_ARG_INFO(0, patchSize)
                ZEND_ARG_INFO(0, center)
                ZEND_ARG_INFO(1, patch)
                ZEND_ARG_INFO(0, patchType)
ZEND_END_ARG_INFO()
PHP_FUNCTION(opencv_get_rect_sub_pix);


ZEND_BEGIN_ARG_INFO_EX(opencv_get_perspective_transform_arginfo, 0, 0, 5)
                ZEND_ARG_INFO(0, src)
                ZEND_ARG_INFO(0, dst)
                ZEND_ARG_INFO(0, solveMethod)
ZEND_END_ARG_INFO()
PHP_FUNCTION(opencv_get_perspective_transform);

ZEND_BEGIN_ARG_INFO_EX(opencv_warp_perspective_arginfo, 0, 0, 7)
                ZEND_ARG_INFO(0, src)
                ZEND_ARG_INFO(1, dst)
                ZEND_ARG_INFO(0, M)
                ZEND_ARG_INFO(0, dsize)
                ZEND_ARG_INFO(0, flags)
                ZEND_ARG_INFO(0, borderMode)
                ZEND_ARG_INFO(0, borderValue)
ZEND_END_ARG_INFO()
PHP_FUNCTION(opencv_warp_perspective);


#endif //OPENCV_OPENCV_IMGPROC_H
