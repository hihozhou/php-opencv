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
#include "opencv_imgproc.h"
#include <opencv2/imgproc.hpp>
#include "core/opencv_mat.h"
#include "core/opencv_type.h"
#include "../../opencv_exception.h"
#include <opencv2/highgui.hpp>

using namespace cv;

void opencv_imgproc_init(int module_number) {
    opencv_color_conversion_code_init(module_number);
    opencv_line_type_init(module_number);
    opencv_morph_shapes_init(module_number);
    opencv_morph_types_init(module_number);
    opencv_flood_fill_flags_init(module_number);
    opencv_threshold_types_init(module_number);
    opencv_adaptive_threshold_types_init(module_number);
    opencv_retrieval_modes_init(module_number);
    opencv_contour_approximation_modes_init(module_number);
}

/**
 * CV\cvtColor
 * @param execute_data
 * @param return_value
 */
PHP_FUNCTION (opencv_cv_t_color) {
    long code, dstCn = 0;
    Mat dstImg;
    zval *mat_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "Ol|l", &mat_zval, opencv_mat_ce, &code, &dstCn) == FAILURE) {
        RETURN_NULL();
    }
    //get src mat object from mat_zval
    opencv_mat_object *src_obj = Z_PHP_MAT_OBJ_P(mat_zval);
    cvtColor(*(src_obj->mat), dstImg, (int) code, (int) dstCn);

    //new PHP Mat bing cv::cvtColor dstImg.
    zval instance;
    object_init_ex(&instance, opencv_mat_ce);
    opencv_mat_object *dst_obj = Z_PHP_MAT_OBJ_P(&instance);

    dst_obj->mat = new Mat(dstImg);

    opencv_mat_update_property_by_c_mat(&instance, dst_obj->mat);

    RETURN_ZVAL(&instance, 0, 0); //return php Mat object
}


/**
 * CV\ellipse
 * @param CV\Mat $img, Mat of original picture
 * @param CV\Point $center, Center Point of the ellipse
 * @param CV\Size $size, axes Half of the size of the ellipse main axes.
 * @param int $angle
 * @param int $startAngle
 * @param int $endAngle
 * @param Scalar $scalar
 * @param int thickness,
 * @param int lineType, line type:FILLED=-1,LINE_4=4,LINE_8=8,LINE_AA=16
 * @param int shift
 */
PHP_FUNCTION (opencv_ellipse) {

    long angle, startAngle, endAngle, thickness = 1, lineType = LINE_8, shift = 0;
    zval *mat_zval, *point_zval, *size_zval, *scalar_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "OOOlllO|lll",
                              &mat_zval, opencv_mat_ce,
                              &point_zval, opencv_point_ce,
                              &size_zval, opencv_size_ce,
                              &angle, &startAngle, &endAngle,
                              &scalar_zval, opencv_scalar_ce,
                              &thickness, &lineType, &shift) == FAILURE) {
        RETURN_NULL();
    }

    opencv_mat_object *mat_obj = Z_PHP_MAT_OBJ_P(mat_zval);
    opencv_point_object *point_obj = Z_PHP_POINT_OBJ_P(point_zval);
    opencv_size_object *size_obj = Z_PHP_SIZE_OBJ_P(size_zval);
    opencv_scalar_object *scalar_obj = Z_PHP_SCALAR_OBJ_P(scalar_zval);
    ellipse(*(mat_obj->mat), *(point_obj->point), *(size_obj->size), angle, startAngle, endAngle, *(scalar_obj->scalar),
            (int) thickness, (int) lineType, (int) shift);

    RETURN_NULL();
}

/**
 * CV\circle
 */
PHP_FUNCTION (opencv_circle) {

    long radius, thickness = 1, lineType = LINE_8, shift = 0;
    zval *mat_zval, *point_zval, *scalar_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "OOlO|lll",
                              &mat_zval, opencv_mat_ce,
                              &point_zval, opencv_point_ce,
                              &radius,
                              &scalar_zval, opencv_scalar_ce,
                              &thickness, &lineType, &shift) == FAILURE) {
        RETURN_NULL();
    }

    opencv_mat_object *mat_obj = Z_PHP_MAT_OBJ_P(mat_zval);
    opencv_point_object *point_obj = Z_PHP_POINT_OBJ_P(point_zval);
    opencv_scalar_object *scalar_obj = Z_PHP_SCALAR_OBJ_P(scalar_zval);

    circle(*(mat_obj->mat), *(point_obj->point), (int) radius, *(scalar_obj->scalar), (int) thickness, (int) lineType,
           (int) shift);

    RETURN_NULL();
}

/**
 * todo 传入二维数组
 * CV\fillPoly
 * @param execute_data
 * @param return_value
 */
PHP_FUNCTION (opencv_fill_poly) {

    long lineType = LINE_8, shift = 0;
    zval *img_zval, *color_zval, *offset_point_zval = NULL;
    zval *points_zval;
    opencv_point_object *offset_object;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "OaO|llz",
                              &img_zval, opencv_mat_ce,
                              &points_zval,
                              &color_zval, opencv_scalar_ce,
                              &lineType, &shift,
                              &offset_point_zval) == FAILURE) {
        RETURN_NULL();
    }

#ifdef PHP_WIN32
    //todo windwo报错问题
    opencv_throw_exception("fillPoly function not support Window system.");
    RETURN_NULL();
#else

    long ncontours = 1;
    unsigned long point_count = zend_hash_num_elements(Z_ARRVAL_P(points_zval));
    Point root_points[ncontours][point_count];
    opencv_point_object *point_object;
    zend_ulong _h;
    zval *array_val_zval;
    ZEND_HASH_FOREACH_NUM_KEY_VAL(Z_ARRVAL_P(points_zval), _h, array_val_zval)
                        {
                            again1:
                        if (Z_TYPE_P(array_val_zval) == IS_OBJECT && Z_OBJCE_P(array_val_zval) == opencv_point_ce) {
                                point_object = Z_PHP_POINT_OBJ_P(array_val_zval);
                                root_points[0][_h] = *point_object->point;
                            } else if (Z_TYPE_P(array_val_zval) == IS_REFERENCE) {
                                array_val_zval = Z_REFVAL_P(array_val_zval);
                                goto again1;
                            } else {
                                    opencv_throw_exception("points array value just Point object.");
                                    RETURN_NULL();
                            }
                        }
    ZEND_HASH_FOREACH_END();

    const Point *pts[ncontours];
    pts[0] = root_points[0];
    int npts[] = {(int) point_count};
    Point offset;
    zval *offset_point_real_zval;

    if (offset_point_zval != NULL) {
        offset_point_real_zval = Z_REFVAL_P(offset_point_zval);
        if (Z_TYPE_P(offset_point_real_zval) == IS_OBJECT && Z_OBJCE_P(offset_point_real_zval) == opencv_point_ce) {
            // is Point object
            offset_object = Z_PHP_POINT_OBJ_P(offset_point_real_zval);
        } else {
                // isn't Point object
                zval_ptr_dtor(offset_point_real_zval);
                zval instance;
                object_init_ex(&instance, opencv_point_ce);
                ZVAL_COPY_VALUE(offset_point_real_zval, &instance);// Cover dst_real_zval by Point object
                offset_object = Z_PHP_POINT_OBJ_P(offset_point_real_zval);
        }
    } else {
            offset = Point();
    }

    opencv_mat_object *mat_obj = Z_PHP_MAT_OBJ_P(img_zval);
    opencv_scalar_object *scalar_obj = Z_PHP_SCALAR_OBJ_P(color_zval);

    fillPoly(*(mat_obj->mat), pts, npts, (int) ncontours, *(scalar_obj->scalar), (int) lineType, (int) shift, offset);
    if (offset_point_zval != NULL) {
        offset_object->point = new Point(offset);
        opencv_point_update_property_by_c_point(offset_point_real_zval, offset_object->point);
    }

    RETURN_NULL();
#endif


}


/**
 * CV\line
 * @param execute_data
 * @param return_value
 */
PHP_FUNCTION (opencv_line) {

    long thickness = 1, lineType = LINE_8, shift = 0;
    zval *mat_zval, *start_point_zval, *end_point_zval, *scalar_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "OOOO|lll",
                              &mat_zval, opencv_mat_ce,
                              &start_point_zval, opencv_point_ce,
                              &end_point_zval, opencv_point_ce,
                              &scalar_zval, opencv_scalar_ce,
                              &thickness, &lineType, &shift) == FAILURE) {
        RETURN_NULL();
    }

    opencv_mat_object *mat_obj = Z_PHP_MAT_OBJ_P(mat_zval);
    opencv_point_object *start_point_obj = Z_PHP_POINT_OBJ_P(start_point_zval);
    opencv_point_object *end_point_obj = Z_PHP_POINT_OBJ_P(end_point_zval);
    opencv_scalar_object *scalar_obj = Z_PHP_SCALAR_OBJ_P(scalar_zval);

    line(*(mat_obj->mat), *(start_point_obj->point), *(end_point_obj->point),
         *(scalar_obj->scalar), (int) thickness, (int) lineType, (int) shift);

    RETURN_NULL();
}

/**
 * CV\rectangle
 * @param execute_data
 * @param return_value
 */
PHP_FUNCTION (opencv_rectangle) {

    long startX, startY, endX, endY;
    long thickness = 1, lineType = LINE_8, shift = 0;
    zval *mat_zval, *color_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "OllllO|lll",
                              &mat_zval, opencv_mat_ce,
                              &startX, &startY, &endX, &endY,
                              &color_zval, opencv_scalar_ce,
                              &thickness, &lineType, &shift) == FAILURE) {
        RETURN_NULL();
    }

    opencv_mat_object *mat_obj = Z_PHP_MAT_OBJ_P(mat_zval);
    opencv_scalar_object *scalar_obj = Z_PHP_SCALAR_OBJ_P(color_zval);

    rectangle(*(mat_obj->mat), Point((int) startX, (int) startY), Point((int) endX, (int) endY), *(scalar_obj->scalar),
              (int) thickness, (int) lineType, (int) shift);

    RETURN_NULL();
}

/**
 * CV\rectangleByPoint
 * @param execute_data
 * @param return_value
 */
PHP_FUNCTION (opencv_rectangle_by_point) {

    long thickness = 1, lineType = LINE_8, shift = 0;
    zval *mat_zval, *start_point_zval, *end_point_zval, *color_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "OOOO|lll",
                              &mat_zval, opencv_mat_ce,
                              &start_point_zval, opencv_point_ce,
                              &end_point_zval, opencv_point_ce,
                              &color_zval, opencv_scalar_ce,
                              &thickness, &lineType, &shift) == FAILURE) {
        RETURN_NULL();
    }

    opencv_mat_object *mat_obj = Z_PHP_MAT_OBJ_P(mat_zval);
    opencv_point_object *start_point_obj = Z_PHP_POINT_OBJ_P(start_point_zval);
    opencv_point_object *end_point_obj = Z_PHP_POINT_OBJ_P(end_point_zval);
    opencv_scalar_object *scalar_obj = Z_PHP_SCALAR_OBJ_P(color_zval);

    rectangle(*(mat_obj->mat), *(start_point_obj->point), *(end_point_obj->point), *(scalar_obj->scalar),
              (int) thickness, (int) lineType, (int) shift);

    RETURN_NULL();
}

/**
 * CV\rectangleByRect
 * @param execute_data
 * @param return_value
 */
PHP_FUNCTION (opencv_rectangle_by_rect) {

    long thickness = 1, lineType = LINE_8, shift = 0;
    zval *mat_zval, *rect_zval, *color_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "OOO|lll",
                              &mat_zval, opencv_mat_ce,
                              &rect_zval, opencv_rect_ce,
                              &color_zval, opencv_scalar_ce,
                              &thickness, &lineType, &shift) == FAILURE) {
        RETURN_NULL();
    }

    opencv_mat_object *mat_obj = Z_PHP_MAT_OBJ_P(mat_zval);
    opencv_rect_object *rect_object = Z_PHP_RECT_OBJ_P(rect_zval);
    opencv_scalar_object *scalar_obj = Z_PHP_SCALAR_OBJ_P(color_zval);

    rectangle(*(mat_obj->mat), *(rect_object->rect), *(scalar_obj->scalar), (int) thickness, (int) lineType,
              (int) shift);

    RETURN_NULL();
}


/**
 * CV\equalizeHist
 * @param execute_data
 * @param return_value
 */
PHP_FUNCTION (opencv_equalize_hist) {

    zval *src_zval, *dst_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "Oz",
                              &src_zval, opencv_mat_ce,
                              &dst_zval) == FAILURE) {
        RETURN_NULL();
    }

    opencv_mat_object *src_obj, *dst_object;
    src_obj = Z_PHP_MAT_OBJ_P(src_zval);
    zval *dst_real_zval = Z_REFVAL_P(dst_zval);
    if (Z_TYPE_P(dst_real_zval) == IS_OBJECT && Z_OBJCE_P(dst_real_zval) == opencv_mat_ce) {
        dst_object = Z_PHP_MAT_OBJ_P(dst_real_zval);
    } else {
        zval_ptr_dtor(dst_real_zval);
        zval instance;
        Mat dst;
        object_init_ex(&instance, opencv_mat_ce);
        ZVAL_COPY_VALUE(dst_real_zval, &instance);
        dst_object = Z_PHP_MAT_OBJ_P(dst_real_zval);
        dst_object->mat = new Mat(dst);
    }
    try {
        equalizeHist(*src_obj->mat, *dst_object->mat);
    } catch (Exception e) {
        opencv_throw_exception(e.what());
    }
    RETURN_NULL();
}


PHP_FUNCTION (opencv_resize) {

    zval *src_zval, *dst_zval, *dsize_zval;
    double fx = 0, fy = 0;
    long interpolation = INTER_LINEAR;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "OzO|ddl",
                              &src_zval, opencv_mat_ce,
                              &dst_zval,
                              &dsize_zval, opencv_size_ce,
                              &fx, &fy, &interpolation
    ) == FAILURE) {
        RETURN_NULL();
    }

    opencv_mat_object *src_obj, *dst_object;
    src_obj = Z_PHP_MAT_OBJ_P(src_zval);
    zval *dst_real_zval = Z_REFVAL_P(dst_zval);
    if (Z_TYPE_P(dst_real_zval) == IS_OBJECT && Z_OBJCE_P(dst_real_zval) == opencv_mat_ce) {
        dst_object = Z_PHP_MAT_OBJ_P(dst_real_zval);
    } else {
        zval_ptr_dtor(dst_real_zval);
        zval instance;
        Mat dst;
        object_init_ex(&instance, opencv_mat_ce);
        ZVAL_COPY_VALUE(dst_real_zval, &instance);
        dst_object = Z_PHP_MAT_OBJ_P(dst_real_zval);
        dst_object->mat = new Mat(dst);
    }
    opencv_size_object *dsize_obj = Z_PHP_SIZE_OBJ_P(dsize_zval);
    try {
        resize(*src_obj->mat, *dst_object->mat, *dsize_obj->size, fx, fy, (int) interpolation);
    } catch (Exception e) {
        opencv_throw_exception(e.what());
    }
    RETURN_NULL();
}

/**
 * CV\putText
 * @param execute_data
 * @param return_value
 */
PHP_FUNCTION (opencv_put_text) {

    zval *img_zval, *org_zval, *color_zval;
    char *text;
    long text_len = 0;
    long font_face, thickness = 1, line_type = LINE_8;
    double font_scale;
    zend_bool bottom_left_origin = 0;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "OsOldO|llb",
                              &img_zval, opencv_mat_ce,
                              &text, &text_len,
                              &org_zval, opencv_point_ce,
                              &font_face, &font_scale,
                              &color_zval, opencv_scalar_ce,
                              &thickness, &line_type,
                              &bottom_left_origin
    ) == FAILURE) {
        RETURN_NULL();
    }
    opencv_mat_object *img_object = Z_PHP_MAT_OBJ_P(img_zval);
    opencv_point_object *org_object = Z_PHP_POINT_OBJ_P(org_zval);
    opencv_scalar_object *color_object = Z_PHP_SCALAR_OBJ_P(color_zval);
    putText(*img_object->mat, text, *org_object->point, (int) font_face, (int) font_scale, *color_object->scalar,
            (int) thickness, (int) line_type, (bool) bottom_left_origin);
}

/**
 * CV\blur
 * @param execute_data
 * @param return_value
 */
PHP_FUNCTION (opencv_blur) {

    zval *src_zval, *dst_zval, *ksize_zval, *anchor_zval = NULL;
    long border_type = BORDER_DEFAULT;
    Point anchor = Point(-1, -1);
    opencv_mat_object *dst_object;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "OzO|Ol",
                              &src_zval, opencv_mat_ce,
                              &dst_zval,
                              &ksize_zval, opencv_size_ce,
                              &anchor_zval, opencv_point_ce,
                              &border_type) == FAILURE) {
        RETURN_NULL();
    }

    opencv_mat_object *src_object = Z_PHP_MAT_OBJ_P(src_zval);
    opencv_size_object *ksize_object = Z_PHP_SIZE_OBJ_P(ksize_zval);
    if (anchor_zval != NULL) {
        opencv_point_object *anchor_object = Z_PHP_POINT_OBJ_P(anchor_zval);
        anchor = *anchor_object->point;
    }

    zval *dst_real_zval = Z_REFVAL_P(dst_zval);
    if (Z_TYPE_P(dst_real_zval) == IS_OBJECT && Z_OBJCE_P(dst_real_zval) == opencv_mat_ce) {
        dst_object = Z_PHP_MAT_OBJ_P(dst_real_zval);
    } else {
        zval_ptr_dtor(dst_real_zval);
        zval instance;
        Mat dst;
        object_init_ex(&instance, opencv_mat_ce);
        ZVAL_COPY_VALUE(dst_real_zval, &instance);
        dst_object = Z_PHP_MAT_OBJ_P(dst_real_zval);
        dst_object->mat = new Mat(dst);
    }
    blur(*src_object->mat, *dst_object->mat, *ksize_object->size, anchor, (int) border_type);
    RETURN_NULL();
}

PHP_FUNCTION (opencv_gaussian_blur) {

    zval *src_zval, *dst_zval, *ksize_zval;
    double sigma_x, sigma_y = 0;
    long border_type = BORDER_DEFAULT;
    opencv_mat_object *dst_object;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "OzOd|dl",
                              &src_zval, opencv_mat_ce,
                              &dst_zval,
                              &ksize_zval, opencv_size_ce,
                              &sigma_x, &sigma_y,
                              &border_type) == FAILURE) {
        RETURN_NULL();
    }

    opencv_mat_object *src_object = Z_PHP_MAT_OBJ_P(src_zval);
    opencv_size_object *ksize_object = Z_PHP_SIZE_OBJ_P(ksize_zval);

    zval *dst_real_zval = Z_REFVAL_P(dst_zval);
    if (Z_TYPE_P(dst_real_zval) == IS_OBJECT && Z_OBJCE_P(dst_real_zval) == opencv_mat_ce) {
        dst_object = Z_PHP_MAT_OBJ_P(dst_real_zval);
    } else {
        zval_ptr_dtor(dst_real_zval);
        zval instance;
        Mat dst;
        object_init_ex(&instance, opencv_mat_ce);
        ZVAL_COPY_VALUE(dst_real_zval, &instance);
        dst_object = Z_PHP_MAT_OBJ_P(dst_real_zval);
        dst_object->mat = new Mat(dst);
    }
    GaussianBlur(*src_object->mat, *dst_object->mat, *ksize_object->size, sigma_x, sigma_y, (int) border_type);
    RETURN_NULL();
}

PHP_FUNCTION (opencv_median_blur) {

    zval *src_zval, *dst_zval;
    long ksize;
    opencv_mat_object *dst_object;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "Ozl",
                              &src_zval, opencv_mat_ce,
                              &dst_zval, &ksize) == FAILURE) {
        RETURN_NULL();
    }

    opencv_mat_object *src_object = Z_PHP_MAT_OBJ_P(src_zval);

    zval *dst_real_zval = Z_REFVAL_P(dst_zval);
    if (Z_TYPE_P(dst_real_zval) == IS_OBJECT && Z_OBJCE_P(dst_real_zval) == opencv_mat_ce) {
        dst_object = Z_PHP_MAT_OBJ_P(dst_real_zval);
    } else {
        zval_ptr_dtor(dst_real_zval);
        zval instance;
        Mat dst;
        object_init_ex(&instance, opencv_mat_ce);
        ZVAL_COPY_VALUE(dst_real_zval, &instance);
        dst_object = Z_PHP_MAT_OBJ_P(dst_real_zval);
        dst_object->mat = new Mat(dst);
    }
    medianBlur(*src_object->mat, *dst_object->mat, (int) ksize);
    RETURN_NULL();
}

PHP_FUNCTION (opencv_bilateral_filter) {

    zval *src_zval, *dst_zval;
    long d, border_type = BORDER_DEFAULT;
    double sigma_color, sigma_space;
    opencv_mat_object *dst_object;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "Ozldd|l",
                              &src_zval, opencv_mat_ce,
                              &dst_zval, &d, &sigma_color,
                              &sigma_space, &border_type) == FAILURE) {
        RETURN_NULL();
    }

    opencv_mat_object *src_object = Z_PHP_MAT_OBJ_P(src_zval);

    zval *dst_real_zval = Z_REFVAL_P(dst_zval);
    if (Z_TYPE_P(dst_real_zval) == IS_OBJECT && Z_OBJCE_P(dst_real_zval) == opencv_mat_ce) {
        dst_object = Z_PHP_MAT_OBJ_P(dst_real_zval);
    } else {
        zval_ptr_dtor(dst_real_zval);
        zval instance;
        Mat dst;
        object_init_ex(&instance, opencv_mat_ce);
        ZVAL_COPY_VALUE(dst_real_zval, &instance);
        dst_object = Z_PHP_MAT_OBJ_P(dst_real_zval);
        dst_object->mat = new Mat(dst);
    }
    bilateralFilter(*src_object->mat, *dst_object->mat, (int) d, sigma_color, sigma_space, (int) border_type);
    RETURN_NULL();
}


PHP_FUNCTION (opencv_dilate) {
    zval *src_zval, *dst_zval, *kernel_zval, *anchor_zval = NULL, *border_value_zval = NULL;
    long iterations = 1, border_type = BORDER_CONSTANT;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "OzO|OllO",
                              &src_zval, opencv_mat_ce,
                              &dst_zval,
                              &kernel_zval, opencv_mat_ce,
                              &anchor_zval, opencv_point_ce,
                              &iterations, &border_type,
                              &border_value_zval, opencv_scalar_ce) == FAILURE) {
        RETURN_NULL();
    }
    opencv_mat_object *src_object, *dst_object, *kernel_object;
    Point anchor = Point(-1, -1);
    Scalar border_value = morphologyDefaultBorderValue();

    src_object = Z_PHP_MAT_OBJ_P(src_zval);
    kernel_object = Z_PHP_MAT_OBJ_P(kernel_zval);
    zval *dst_real_zval = Z_REFVAL_P(dst_zval);

    if (Z_TYPE_P(dst_real_zval) == IS_OBJECT && Z_OBJCE_P(dst_real_zval) == opencv_mat_ce) {
        dst_object = Z_PHP_MAT_OBJ_P(dst_real_zval);
    } else {
        zval_ptr_dtor(dst_real_zval);
        zval instance;
        Mat dst;
        object_init_ex(&instance, opencv_mat_ce);
        ZVAL_COPY_VALUE(dst_real_zval, &instance);
        dst_object = Z_PHP_MAT_OBJ_P(dst_real_zval);
        dst_object->mat = new Mat(dst);
    }

    if (anchor_zval != NULL) {
        opencv_point_object *anchor_object = Z_PHP_POINT_OBJ_P(anchor_zval);
        anchor = *anchor_object->point;
    }

    if (border_value_zval != NULL) {
        opencv_scalar_object *border_value_object = Z_PHP_SCALAR_OBJ_P(border_value_zval);
        border_value = *border_value_object->scalar;
    }

    dilate(*src_object->mat, *dst_object->mat, *kernel_object->mat, anchor, (int) iterations, (int) border_type,
           border_value);
    RETURN_NULL();

}

PHP_FUNCTION (opencv_erode) {

    zval *src_zval, *dst_zval, *kernel_zval, *anchor_zval = NULL, *border_value_zval = NULL;
    long iterations = 1, border_type = BORDER_CONSTANT;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "OzO|OllO",
                              &src_zval, opencv_mat_ce,
                              &dst_zval,
                              &kernel_zval, opencv_mat_ce,
                              &anchor_zval, opencv_point_ce,
                              &iterations, &border_type,
                              &border_value_zval, opencv_scalar_ce) == FAILURE) {
        RETURN_NULL();
    }
    opencv_mat_object *src_object, *dst_object, *kernel_object;
    Point anchor = Point(-1, -1);
    Scalar border_value = morphologyDefaultBorderValue();

    src_object = Z_PHP_MAT_OBJ_P(src_zval);
    kernel_object = Z_PHP_MAT_OBJ_P(kernel_zval);
    zval *dst_real_zval = Z_REFVAL_P(dst_zval);

    if (Z_TYPE_P(dst_real_zval) == IS_OBJECT && Z_OBJCE_P(dst_real_zval) == opencv_mat_ce) {
        dst_object = Z_PHP_MAT_OBJ_P(dst_real_zval);
    } else {
        zval_ptr_dtor(dst_real_zval);
        zval instance;
        Mat dst;
        object_init_ex(&instance, opencv_mat_ce);
        ZVAL_COPY_VALUE(dst_real_zval, &instance);
        dst_object = Z_PHP_MAT_OBJ_P(dst_real_zval);
        dst_object->mat = new Mat(dst);
    }

    if (anchor_zval != NULL) {
        opencv_point_object *anchor_object = Z_PHP_POINT_OBJ_P(anchor_zval);
        anchor = *anchor_object->point;
    }

    if (border_value_zval != NULL) {
        opencv_scalar_object *border_value_object = Z_PHP_SCALAR_OBJ_P(border_value_zval);
        border_value = *border_value_object->scalar;
    }
    erode(*src_object->mat, *dst_object->mat, *kernel_object->mat, anchor, (int) iterations, (int) border_type,
          border_value);
    RETURN_NULL();
}


PHP_FUNCTION (opencv_threshold) {

    zval *src_zval, *dst_zval;
    double thresh, maxval;
    long type;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "Ozddl",
                              &src_zval, opencv_mat_ce,
                              &dst_zval,
                              &thresh, &maxval,
                              &type) == FAILURE) {
        RETURN_NULL();
    }

    opencv_mat_object *src_object, *dst_object;

    src_object = Z_PHP_MAT_OBJ_P(src_zval);
    zval *dst_real_zval = Z_REFVAL_P(dst_zval);
    if (Z_TYPE_P(dst_real_zval) == IS_OBJECT && Z_OBJCE_P(dst_real_zval) == opencv_mat_ce) {
        dst_object = Z_PHP_MAT_OBJ_P(dst_real_zval);
    } else {
        zval_ptr_dtor(dst_real_zval);
        zval instance;
        Mat dst;
        object_init_ex(&instance, opencv_mat_ce);
        ZVAL_COPY_VALUE(dst_real_zval, &instance);
        dst_object = Z_PHP_MAT_OBJ_P(dst_real_zval);
        dst_object->mat = new Mat(dst);
    }
    RETURN_DOUBLE(threshold(*src_object->mat, *dst_object->mat, thresh, maxval, (int) type));
}


PHP_FUNCTION (opencv_adaptive_threshold) {

    zval *src_zval, *dst_zval;
    double maxValue, C;
    long adaptiveMethod, thresholdType, blockSize;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "Ozdllld",
                              &src_zval, opencv_mat_ce,
                              &dst_zval,
                              &maxValue, &adaptiveMethod,
                              &thresholdType, &blockSize, &C) == FAILURE) {
        RETURN_NULL();
    }

    opencv_mat_object *src_object, *dst_object;

    src_object = Z_PHP_MAT_OBJ_P(src_zval);
    zval *dst_real_zval = Z_REFVAL_P(dst_zval);
    if (Z_TYPE_P(dst_real_zval) == IS_OBJECT && Z_OBJCE_P(dst_real_zval) == opencv_mat_ce) {
        dst_object = Z_PHP_MAT_OBJ_P(dst_real_zval);
    } else {
        zval_ptr_dtor(dst_real_zval);
        zval instance;
        Mat dst;
        object_init_ex(&instance, opencv_mat_ce);
        ZVAL_COPY_VALUE(dst_real_zval, &instance);
        dst_object = Z_PHP_MAT_OBJ_P(dst_real_zval);
        dst_object->mat = new Mat(dst);
    }

    adaptiveThreshold(*src_object->mat, *dst_object->mat, maxValue, (int) adaptiveMethod, (int) thresholdType,
                      (int) blockSize, C);
    RETURN_NULL();
}


/**
 * CV\sobel
 * @param execute_data
 * @param return_value
 */
PHP_FUNCTION (opencv_sobel) {

    zval *src_zval, *dst_zval;
    long ddepth, dx, dy;
    long ksize = 3;

    double delta = 0.0, scale = 1.0;
    long border_type = BORDER_DEFAULT;
    opencv_mat_object *dst_object;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "Ozlll|lddl",
                              &src_zval, opencv_mat_ce,
                              &dst_zval,
                              &ddepth,
                              &dx,
                              &dy,
                              &ksize,
                              &scale,
                              &delta,
                              &border_type) == FAILURE) {
        RETURN_NULL();
    }

    opencv_mat_object *src_object = Z_PHP_MAT_OBJ_P(src_zval);

    zval *dst_real_zval = Z_REFVAL_P(dst_zval);
    if (Z_TYPE_P(dst_real_zval) == IS_OBJECT && Z_OBJCE_P(dst_real_zval) == opencv_mat_ce) {
        dst_object = Z_PHP_MAT_OBJ_P(dst_real_zval);
    } else {
        zval_ptr_dtor(dst_real_zval);
        zval instance;
        Mat dst;
        object_init_ex(&instance, opencv_mat_ce);
        ZVAL_COPY_VALUE(dst_real_zval, &instance);
        dst_object = Z_PHP_MAT_OBJ_P(dst_real_zval);
        dst_object->mat = new Mat(dst);
    }
    Sobel(*src_object->mat, *dst_object->mat, (int) ddepth, (int) dx, (int) dy, (int) ksize, scale, delta,
          (int) border_type);
    RETURN_NULL();
}

/**
 * CV\Scharr
 * @param execute_data
 * @param return_value
 */
PHP_FUNCTION (opencv_scharr) {

    zval *src_zval, *dst_zval;
    long ddepth, dx, dy;

    double delta = 0.0, scale = 1.0;
    long border_type = BORDER_DEFAULT;
    opencv_mat_object *dst_object;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "Ozlll|ddl",
                              &src_zval, opencv_mat_ce,
                              &dst_zval,
                              &ddepth,
                              &dx,
                              &dy,
                              &scale,
                              &delta,
                              &border_type) == FAILURE) {
        RETURN_NULL();
    }

    opencv_mat_object *src_object = Z_PHP_MAT_OBJ_P(src_zval);

    zval *dst_real_zval = Z_REFVAL_P(dst_zval);
    if (Z_TYPE_P(dst_real_zval) == IS_OBJECT && Z_OBJCE_P(dst_real_zval) == opencv_mat_ce) {
        dst_object = Z_PHP_MAT_OBJ_P(dst_real_zval);
    } else {
        zval_ptr_dtor(dst_real_zval);
        zval instance;
        Mat dst;
        object_init_ex(&instance, opencv_mat_ce);
        ZVAL_COPY_VALUE(dst_real_zval, &instance);
        dst_object = Z_PHP_MAT_OBJ_P(dst_real_zval);
        dst_object->mat = new Mat(dst);
    }
    Scharr(*src_object->mat, *dst_object->mat, (int) ddepth, (int) dx, (int) dy, scale, delta, (int) border_type);
    RETURN_NULL();
}

/**
 * CV\laplacian
 * @param execute_data
 * @param return_value
 */
PHP_FUNCTION (opencv_laplacian) {

    zval *src_zval, *dst_zval;
    long ddepth;
    long ksize = 3;

    double delta = 0.0, scale = 1.0;
    long border_type = BORDER_DEFAULT;
    opencv_mat_object *dst_object;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "Ozl|lddl",
                              &src_zval, opencv_mat_ce,
                              &dst_zval,
                              &ddepth,
                              &ksize,
                              &scale,
                              &delta,
                              &border_type) == FAILURE) {
        RETURN_NULL();
    }

    opencv_mat_object *src_object = Z_PHP_MAT_OBJ_P(src_zval);

    zval *dst_real_zval = Z_REFVAL_P(dst_zval);
    if (Z_TYPE_P(dst_real_zval) == IS_OBJECT && Z_OBJCE_P(dst_real_zval) == opencv_mat_ce) {
        dst_object = Z_PHP_MAT_OBJ_P(dst_real_zval);
    } else {
        zval_ptr_dtor(dst_real_zval);
        zval instance;
        Mat dst;
        object_init_ex(&instance, opencv_mat_ce);
        ZVAL_COPY_VALUE(dst_real_zval, &instance);
        dst_object = Z_PHP_MAT_OBJ_P(dst_real_zval);
        dst_object->mat = new Mat(dst);
    }
    Laplacian(*src_object->mat, *dst_object->mat, (int) ddepth, (int) ksize, scale, delta, (int) border_type);
    RETURN_NULL();
}

/**
 * CV\filter2D
 * @param execute_data
 * @param return_value
 */
PHP_FUNCTION (opencv_filter2D) {

    zval *src_zval, *dst_zval, *kernel_zval, *anchor_zval = NULL;
    long ddepth;
    Point anchor = Point(-1, -1);
    double delta = 0.0;
    long border_type = BORDER_DEFAULT;
    opencv_mat_object *dst_object;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "OzlO|Odl",
                              &src_zval, opencv_mat_ce,
                              &dst_zval,
                              &ddepth,
                              &kernel_zval, opencv_mat_ce,
                              &anchor_zval, opencv_point_ce,
                              &delta,
                              &border_type) == FAILURE) {
        RETURN_NULL();
    }

    opencv_mat_object *src_object = Z_PHP_MAT_OBJ_P(src_zval);
    opencv_mat_object *kernel_object = Z_PHP_MAT_OBJ_P(kernel_zval);
    if (anchor_zval != NULL) {
        opencv_point_object *anchor_object = Z_PHP_POINT_OBJ_P(anchor_zval);
        anchor = *anchor_object->point;
    }

    zval *dst_real_zval = Z_REFVAL_P(dst_zval);
    if (Z_TYPE_P(dst_real_zval) == IS_OBJECT && Z_OBJCE_P(dst_real_zval) == opencv_mat_ce) {
        dst_object = Z_PHP_MAT_OBJ_P(dst_real_zval);
    } else {
        zval_ptr_dtor(dst_real_zval);
        zval instance;
        Mat dst;
        object_init_ex(&instance, opencv_mat_ce);
        ZVAL_COPY_VALUE(dst_real_zval, &instance);
        dst_object = Z_PHP_MAT_OBJ_P(dst_real_zval);
        dst_object->mat = new Mat(dst);
    }
    filter2D(*src_object->mat, *dst_object->mat, (int) ddepth, *kernel_object->mat, anchor, delta, (int) border_type);
    RETURN_NULL();
}

/**
 * CV\convertScaleAbs
 * @param execute_data
 * @param return_value
 */
PHP_FUNCTION (opencv_convert_scale_abs) {

    zval *src_zval, *dst_zval;
    double alpha = 1.0;
    double beta = 0.0;

    opencv_mat_object *dst_object;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "Oz|dd",
                              &src_zval, opencv_mat_ce,
                              &dst_zval,
                              &alpha,
                              &beta) == FAILURE) {
        RETURN_NULL();
    }

    opencv_mat_object *src_object = Z_PHP_MAT_OBJ_P(src_zval);

    zval *dst_real_zval = Z_REFVAL_P(dst_zval);
    if (Z_TYPE_P(dst_real_zval) == IS_OBJECT && Z_OBJCE_P(dst_real_zval) == opencv_mat_ce) {
        dst_object = Z_PHP_MAT_OBJ_P(dst_real_zval);
    } else {
        zval_ptr_dtor(dst_real_zval);
        zval instance;
        Mat dst;
        object_init_ex(&instance, opencv_mat_ce);
        ZVAL_COPY_VALUE(dst_real_zval, &instance);
        dst_object = Z_PHP_MAT_OBJ_P(dst_real_zval);
        dst_object->mat = new Mat(dst);
    }
    convertScaleAbs(*src_object->mat, *dst_object->mat, alpha, beta);
    RETURN_NULL();
}

/**
 * CV\getStructuringElement
 * @param execute_data
 * @param return_value
 */
PHP_FUNCTION (opencv_get_structuring_element) {
    long shape;
    zval *ksize_zval, *anchor_zval = NULL;
    Point anchor = Point(-1, -1);
    Mat dst;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "lO|O",
                              &shape,
                              &ksize_zval, opencv_size_ce,
                              &anchor_zval, opencv_point_ce) == FAILURE) {
        RETURN_NULL();
    }

    opencv_size_object *ksize_object = Z_PHP_SIZE_OBJ_P(ksize_zval);
    if (anchor_zval != NULL) {
        opencv_point_object *anchor_object = Z_PHP_POINT_OBJ_P(anchor_zval);
        anchor = *anchor_object->point;
    }

    dst = getStructuringElement((int) shape, *ksize_object->size, anchor);

    zval instance;
    object_init_ex(&instance, opencv_mat_ce);
    opencv_mat_object *dst_obj = Z_PHP_MAT_OBJ_P(&instance);

    dst_obj->mat = new Mat(dst);
    opencv_mat_update_property_by_c_mat(&instance, dst_obj->mat);

    RETURN_ZVAL(&instance, 0, 0); //return php Mat object
}


PHP_FUNCTION (opencv_morphology_ex) {

    zval *src_zval, *dst_zval, *kernel_zval, *anchor_zval = NULL, *border_value_zval = NULL;
    long op, iterations = 1, border_type = BORDER_CONSTANT;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "OzlO|OllO",
                              &src_zval, opencv_mat_ce,
                              &dst_zval,
                              &op,
                              &kernel_zval, opencv_mat_ce,
                              &anchor_zval, opencv_point_ce,
                              &iterations, &border_type,
                              &border_value_zval, opencv_scalar_ce) == FAILURE) {
        RETURN_NULL();
    }
    opencv_mat_object *src_object, *dst_object, *kernel_object;
    Point anchor = Point(-1, -1);
    Scalar border_value = morphologyDefaultBorderValue();

    src_object = Z_PHP_MAT_OBJ_P(src_zval);
    kernel_object = Z_PHP_MAT_OBJ_P(kernel_zval);
    zval *dst_real_zval = Z_REFVAL_P(dst_zval);

    if (Z_TYPE_P(dst_real_zval) == IS_OBJECT && Z_OBJCE_P(dst_real_zval) == opencv_mat_ce) {
        dst_object = Z_PHP_MAT_OBJ_P(dst_real_zval);
    } else {
        zval_ptr_dtor(dst_real_zval);
        zval instance;
        Mat dst;
        object_init_ex(&instance, opencv_mat_ce);
        ZVAL_COPY_VALUE(dst_real_zval, &instance);
        dst_object = Z_PHP_MAT_OBJ_P(dst_real_zval);
        dst_object->mat = new Mat(dst);
    }

    if (anchor_zval != NULL) {
        opencv_point_object *anchor_object = Z_PHP_POINT_OBJ_P(anchor_zval);
        anchor = *anchor_object->point;
    }

    if (border_value_zval != NULL) {
        opencv_scalar_object *border_value_object = Z_PHP_SCALAR_OBJ_P(border_value_zval);
        border_value = *border_value_object->scalar;
    }
    morphologyEx(*src_object->mat, *dst_object->mat, int(op), *kernel_object->mat, anchor, (int) iterations,
                 (int) border_type, border_value);
    RETURN_NULL();
}


PHP_FUNCTION (opencv_flood_fill) {
    zval *image_zval, *seed_point_zval, *new_val_zval, *mask_zval = NULL, *rect_zval = NULL, *lo_diff_zval = NULL, *up_diff_zval = NULL;
    long flags = 4;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "OOOO!|O!OOl",
                              &image_zval, opencv_mat_ce,
                              &seed_point_zval, opencv_point_ce,
                              &new_val_zval, opencv_scalar_ce,
                              &mask_zval, opencv_mat_ce,
                              &rect_zval, opencv_rect_ce,
                              &lo_diff_zval, opencv_scalar_ce,
                              &up_diff_zval, opencv_scalar_ce,
                              &flags) == FAILURE) {
        RETURN_NULL();
    }
    opencv_mat_object *image_object;
    opencv_point_object *seed_point_object;
    opencv_scalar_object *new_value_object;

    image_object = Z_PHP_MAT_OBJ_P(image_zval);
    seed_point_object = Z_PHP_POINT_OBJ_P(seed_point_zval);
    new_value_object = Z_PHP_SCALAR_OBJ_P(new_val_zval);

    Rect *rect = 0;
    Scalar lo_diff = Scalar(), up_diff = Scalar();
    opencv_rect_object *rect_object;
    if (rect_zval != NULL) {
        rect_object = Z_PHP_RECT_OBJ_P(rect_zval);
        rect = rect_object->rect;
    }
    if (lo_diff_zval != NULL) {
        opencv_scalar_object *lo_diff_object = Z_PHP_SCALAR_OBJ_P(lo_diff_zval);
        lo_diff = *lo_diff_object->scalar;
    }

    if (up_diff_zval != NULL) {
        opencv_scalar_object *up_diff_object = Z_PHP_SCALAR_OBJ_P(up_diff_zval);
        up_diff = *up_diff_object->scalar;
    }

    int result;
    try {
        if (mask_zval == NULL) {
            result = floodFill(*image_object->mat, *seed_point_object->point, *new_value_object->scalar, rect, lo_diff,
                               up_diff, (int) flags);
        } else {
            opencv_mat_object *mask_object = Z_PHP_MAT_OBJ_P(mask_zval);
            result = floodFill(*image_object->mat, *mask_object->mat, *seed_point_object->point,
                               *new_value_object->scalar, rect, lo_diff, up_diff, (int) flags);
        }

        if (rect_zval != NULL) {
            opencv_rect_update_property_by_c_rect(rect_zval, rect_object->rect);
        }

    } catch (Exception e) {
        opencv_throw_exception(e.what());
        RETURN_NULL();
    }
    RETURN_LONG(result);
}

/**
 * CV\findContoursWithoutHierarchy()
 * @param execute_data
 * @param return_value
 */
PHP_FUNCTION (opencv_find_contours_without_hierarchy) {
    zval *image_zval, *contours_zval, *offset_zval = NULL;
    long mode, method;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "Ozll|z",
                              &image_zval, opencv_mat_ce,
                              &contours_zval,
                              &mode, &method,
                              &offset_zval) == FAILURE) {
        RETURN_NULL();
    }
    opencv_mat_object *image_object = Z_PHP_MAT_OBJ_P(image_zval);
    zval *contours_real_zval = Z_REFVAL_P(contours_zval);
    zval *offset_real_zval;

    Point offset;
    opencv_point_object *offset_object;
    if (offset_zval != NULL) {
        offset_real_zval = Z_REFVAL_P(offset_zval);
        if (Z_TYPE_P(offset_real_zval) == IS_OBJECT && Z_OBJCE_P(offset_real_zval) == opencv_point_ce) {
            // is Point object
            offset_object = Z_PHP_POINT_OBJ_P(offset_real_zval);
        } else {
            // isn't Point object
            zval_ptr_dtor(offset_real_zval);
            zval instance;
            object_init_ex(&instance, opencv_point_ce);
            ZVAL_COPY_VALUE(offset_real_zval, &instance);// Cover dst_real_zval by Point object
            offset_object = Z_PHP_POINT_OBJ_P(offset_real_zval);
        }
    } else {
        offset = Point();
    }

    std::vector<std::vector<cv::Point> > contours;
    findContours(*image_object->mat, contours, (int) mode, (int) method, offset);

    if (offset_zval != NULL) {
        offset_object->point = new Point(offset);
        opencv_point_update_property_by_c_point(offset_real_zval, offset_object->point);
    }
    zval_dtor(
            contours_real_zval);//if contours_real_zval value not eq null ,free contours_real_zval to avoid memory leaks detected
    array_init(contours_real_zval);
    int point_count = 0;
    for (unsigned long i = 0; i < contours.size(); i++) {
        zval OPENCV_CONNECT(zval_arr, i);
        array_init(&OPENCV_CONNECT(zval_arr, i));
        for (unsigned long j = 0; j < contours.at(i).size(); j++) {
            zval OPENCV_CONNECT(zval_point, point_count);
            object_init_ex(&OPENCV_CONNECT(zval_point, point_count), opencv_point_ce);
            Z_PHP_POINT_OBJ_P(&OPENCV_CONNECT(zval_point, point_count))->point = new Point(contours.at(i).at(j));
            opencv_point_update_property_by_c_point(&OPENCV_CONNECT(zval_point, point_count),
                                                    Z_PHP_POINT_OBJ_P(&OPENCV_CONNECT(zval_point, point_count))->point);
            add_next_index_zval(&OPENCV_CONNECT(zval_arr, i), &OPENCV_CONNECT(zval_point, point_count));
            point_count++;
        }
        add_next_index_zval(contours_real_zval, &OPENCV_CONNECT(zval_arr, i));

    }
    RETURN_NULL();
}

/**
 * //todo hierarchy param
 * CV\drawContours()
 * @param execute_data
 * @param return_value
 */
PHP_FUNCTION (opencv_draw_contours) {
    zval *image_zval, *contours_zval, *color_zval, *hierarchy_zval, *offset_zval = NULL;
    long contourIdx, thickness = 1, lineType = LINE_8, maxLevel = INT_MAX;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "OalO|llalz",
                              &image_zval, opencv_mat_ce,
                              &contours_zval,
                              &contourIdx,
                              &color_zval, opencv_scalar_ce,
                              &thickness, &lineType,
                              &hierarchy_zval,
                              &maxLevel, &offset_zval
    ) == FAILURE) {
        RETURN_NULL();
    }
    std::vector<std::vector<cv::Point> > contours;
    std::vector<cv::Point> contour;
    opencv_point_object *point_object;
    opencv_mat_object *image_object = Z_PHP_MAT_OBJ_P(image_zval);
    opencv_scalar_object *color_object = Z_PHP_SCALAR_OBJ_P(color_zval);
    zend_ulong _h;
    zend_ulong _h2;
    zval *array_val_zval;
    zval *array_val_zval2;
    ZEND_HASH_FOREACH_NUM_KEY_VAL(Z_ARRVAL_P(contours_zval), _h, array_val_zval)
            {//get point arrays
                again1:
                if (Z_TYPE_P(array_val_zval) == IS_ARRAY) {
                    contour.clear();
                    ZEND_HASH_FOREACH_NUM_KEY_VAL(Z_ARRVAL_P(array_val_zval), _h2, array_val_zval2)
                            {//get points object
                                again2:
                                if (Z_TYPE_P(array_val_zval2) == IS_OBJECT &&
                                    Z_OBJCE_P(array_val_zval2) == opencv_point_ce) {
                                    point_object = Z_PHP_POINT_OBJ_P(array_val_zval2);
                                    contour.push_back(*point_object->point);
                                } else if (Z_TYPE_P(array_val_zval2) == IS_REFERENCE) {
                                    array_val_zval2 = Z_REFVAL_P(array_val_zval2);
                                    goto again2;
                                } else {
                                    opencv_throw_exception("The 2D array element can only be Point object.");
                                    RETURN_NULL();
                                }
                            }
                    ZEND_HASH_FOREACH_END();
                    contours.push_back(contour);
                } else if (Z_TYPE_P(array_val_zval) == IS_REFERENCE) {
                    array_val_zval = Z_REFVAL_P(array_val_zval);
                    goto again1;
                } else {
                    opencv_throw_exception("The parameter contours can only be a Point object two bit array.");
                    RETURN_NULL();
                }
            }
    ZEND_HASH_FOREACH_END();
    InputArray hierarchy = noArray();
    zval *offset_real_zval;

    Point offset;
    opencv_point_object *offset_object;
    if (offset_zval != NULL) {
        offset_real_zval = Z_REFVAL_P(offset_zval);
        if (Z_TYPE_P(offset_real_zval) == IS_OBJECT && Z_OBJCE_P(offset_real_zval) == opencv_point_ce) {
            // is Point object
            offset_object = Z_PHP_POINT_OBJ_P(offset_real_zval);
        } else {
            // isn't Point object
            zval_ptr_dtor(offset_real_zval);
            zval instance;
            object_init_ex(&instance, opencv_point_ce);
            ZVAL_COPY_VALUE(offset_real_zval, &instance);// Cover dst_real_zval by Point object
            offset_object = Z_PHP_POINT_OBJ_P(offset_real_zval);
        }
    } else {
        offset = Point();
    }
    try {
        drawContours(*image_object->mat, contours, (int) contourIdx, *color_object->scalar,
                     (int) thickness, (int) lineType, hierarchy, (int) maxLevel, offset);
    } catch (Exception e) {
        opencv_throw_exception(e.what());
    }


    if (offset_zval != NULL) {
        offset_object->point = new Point(offset);
        opencv_point_update_property_by_c_point(offset_real_zval, offset_object->point);
    }

    RETURN_NULL();


}

/**
 * todo param can Mat
 * @param execute_data
 * @param return_value
 */
PHP_FUNCTION (opencv_bounding_rect) {
    zval *points_zval;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "a", &points_zval) == FAILURE) {
        RETURN_NULL();
    }
    std::vector<cv::Point> points;
    opencv_point_object *point_object;
    Rect return_rect;
    unsigned long src_count = zend_hash_num_elements(Z_ARRVAL_P(points_zval));
    points.reserve(src_count);//指定长度
    zend_ulong _h;
    zval *array_val_zval;
    ZEND_HASH_FOREACH_NUM_KEY_VAL(Z_ARRVAL_P(points_zval), _h, array_val_zval)
            {//get point arrays
                again1:
                if (Z_TYPE_P(array_val_zval) == IS_OBJECT && Z_OBJCE_P(array_val_zval) == opencv_point_ce) {
                    point_object = Z_PHP_POINT_OBJ_P(array_val_zval);
                    points.push_back(*point_object->point);
                } else if (Z_TYPE_P(array_val_zval) == IS_REFERENCE) {
                    array_val_zval = Z_REFVAL_P(array_val_zval);
                    goto again1;
                } else {
                    opencv_throw_exception("The parameter contours can only be a Point object two bit array.");
                    RETURN_NULL();
                }
            }
    ZEND_HASH_FOREACH_END();
    try {
        return_rect = boundingRect(points);
    } catch (Exception e) {
        opencv_throw_exception(e.what());
    }

    zval instance;
    object_init_ex(&instance, opencv_rect_ce);
    opencv_rect_object *rect_obj = Z_PHP_RECT_OBJ_P(&instance);

    rect_obj->rect = new Rect(return_rect);

    opencv_rect_update_property_by_c_rect(&instance, rect_obj->rect);

    RETURN_ZVAL(&instance, 0, 0); //return php Rect object
}


/**
 * CV\getRotationMatrix2D
 * @param execute_data
 * @param return_value
 */
PHP_FUNCTION (opencv_get_rotation_matrix2D) {
    zval *center_zval;
    double angle, scale;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "Odd", &center_zval, opencv_point_ce, &angle, &scale) == FAILURE) {
        RETURN_NULL();
    }

    opencv_point_object *center_object = Z_PHP_POINT_OBJ_P(center_zval);
    Mat mat = getRotationMatrix2D(Point2f(*center_object->point), angle, scale);

    zval instance;
    object_init_ex(&instance, opencv_mat_ce);
    opencv_mat_object *instance_object = Z_PHP_MAT_OBJ_P(&instance);

    instance_object->mat = new Mat(mat);

    opencv_mat_update_property_by_c_mat(&instance, instance_object->mat);

    RETURN_ZVAL(&instance, 0, 0); //return php Mat object

}


/**
 * CV\warpAffine
 * @param execute_data
 * @param return_value
 */
PHP_FUNCTION (opencv_warp_affine) {
    zval *src_zval, *dst_zval, *M_zval, *dsize_zval, *border_value_zval = NULL;
    long flags = INTER_LINEAR, borderMode = BORDER_CONSTANT;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "OzOO|llO",
                              &src_zval, opencv_mat_ce,
                              &dst_zval,
                              &M_zval, opencv_mat_ce,
                              &dsize_zval, opencv_size_ce,
                              &flags, &borderMode,
                              &border_value_zval, opencv_scalar_ce) == FAILURE) {
        RETURN_NULL();
    }

    Scalar borderValue = Scalar();
    if (border_value_zval != NULL) {
        opencv_scalar_object *border_value_object = Z_PHP_SCALAR_OBJ_P(border_value_zval);
        borderValue = *border_value_object->scalar;
    }
    opencv_mat_object *src_object = Z_PHP_MAT_OBJ_P(src_zval);
    opencv_mat_object *M_object = Z_PHP_MAT_OBJ_P(M_zval);
    opencv_size_object *dsize_object = Z_PHP_SIZE_OBJ_P(dsize_zval);

    opencv_mat_object *dst_object;
    zval *dst_real_zval = Z_REFVAL_P(dst_zval);

    if (Z_TYPE_P(dst_real_zval) == IS_OBJECT && Z_OBJCE_P(dst_real_zval) == opencv_mat_ce) {
        // is Point object
        dst_object = Z_PHP_MAT_OBJ_P(dst_real_zval);
    } else {
        // isn't Mat object
        zval_ptr_dtor(dst_real_zval);
        zval instance;
        object_init_ex(&instance, opencv_mat_ce);
        ZVAL_COPY_VALUE(dst_real_zval, &instance);// Cover dst_real_zval by Mat object
        dst_object = Z_PHP_MAT_OBJ_P(dst_real_zval);
    }
    Mat dst;
    warpAffine(*src_object->mat, dst, *M_object->mat, *dsize_object->size, (int) flags, (int) borderMode, borderValue);
    dst_object->mat = new Mat(dst);
    opencv_mat_update_property_by_c_mat(dst_real_zval, dst_object->mat);

    RETURN_NULL();

}


PHP_FUNCTION (opencv_get_rect_sub_pix) {
    zval *image_zval, *patch_size_zval, *center_zval, *patch_zval;
    long patchType = -1;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "OOOz|l",
                              &image_zval, opencv_mat_ce,
                              &patch_size_zval, opencv_size_ce,
                              &center_zval, opencv_point_ce,
                              &patch_zval,
                              &patchType) == FAILURE) {
        RETURN_NULL();
    }


    opencv_mat_object *image_object = Z_PHP_MAT_OBJ_P(image_zval);
    opencv_size_object *patch_size_object = Z_PHP_SIZE_OBJ_P(patch_size_zval);
    opencv_point_object *center_object = Z_PHP_POINT_OBJ_P(center_zval);

    opencv_mat_object *patch_object;
    zval *patch_real_zval = Z_REFVAL_P(patch_zval);

    if (Z_TYPE_P(patch_real_zval) == IS_OBJECT && Z_OBJCE_P(patch_real_zval) == opencv_mat_ce) {
        // is Point object
        patch_object = Z_PHP_MAT_OBJ_P(patch_real_zval);
    } else {
        // isn't Mat object
        zval_ptr_dtor(patch_real_zval);
        zval instance;
        object_init_ex(&instance, opencv_mat_ce);
        ZVAL_COPY_VALUE(patch_real_zval, &instance);// Cover dst_real_zval by Mat object
        patch_object = Z_PHP_MAT_OBJ_P(patch_real_zval);
    }
    Mat patch;
    getRectSubPix(*image_object->mat, *patch_size_object->size, Point2f(*center_object->point), patch, (int) patchType);
    patch_object->mat = new Mat(patch);
    opencv_mat_update_property_by_c_mat(patch_real_zval, patch_object->mat);

    RETURN_NULL();

}

/**
 * @see cv::getPerspectiveTransform
 * @param execute_data
 * @param return_value
 */
PHP_FUNCTION(opencv_get_perspective_transform){

    zval *src_zval,*dst_zval;
    long solveMethod = DECOMP_LU;

    if (zend_parse_parameters_ex(ZEND_PARSE_PARAMS_THROW, ZEND_NUM_ARGS(), "aa|l",
                                 &src_zval ,
                                 &dst_zval ,
                                 &solveMethod
    ) == FAILURE) {
        RETURN_NULL();
    }

    zend_ulong _h;
    zval *array_val_zval;
    std::vector<cv::Point2f> src_points, dst_points;
    opencv_point_object *point_object;
    //src point数组
    unsigned long src_count = zend_hash_num_elements(Z_ARRVAL_P(src_zval));//获取数组长度
    src_points.reserve(src_count);//指定长度
    ZEND_HASH_FOREACH_NUM_KEY_VAL(Z_ARRVAL_P(src_zval), _h, array_val_zval)
            {//get point arrays
                again1:
                if (Z_TYPE_P(array_val_zval) == IS_OBJECT && Z_OBJCE_P(array_val_zval) == opencv_point_ce) {
                    point_object = Z_PHP_POINT_OBJ_P(array_val_zval);
                    src_points.push_back(*point_object->point);
                } else if (Z_TYPE_P(array_val_zval) == IS_REFERENCE) {
                    array_val_zval = Z_REFVAL_P(array_val_zval);
                    goto again1;
                } else {
                    opencv_throw_exception("The parameter src can only be a Point object two bit array.");
                    RETURN_NULL();
                }
            }
    ZEND_HASH_FOREACH_END();

    //dst point数组
    unsigned long dst_count = zend_hash_num_elements(Z_ARRVAL_P(dst_zval));//获取数组长度
    dst_points.reserve(dst_count);//指定长度
    ZEND_HASH_FOREACH_NUM_KEY_VAL(Z_ARRVAL_P(dst_zval), _h, array_val_zval)
            {//get point arrays
                again2:
                if (Z_TYPE_P(array_val_zval) == IS_OBJECT && Z_OBJCE_P(array_val_zval) == opencv_point_ce) {
                    point_object = Z_PHP_POINT_OBJ_P(array_val_zval);
                    dst_points.push_back(*point_object->point);
                } else if (Z_TYPE_P(array_val_zval) == IS_REFERENCE) {
                    array_val_zval = Z_REFVAL_P(array_val_zval);
                    goto again2;
                } else {
                    opencv_throw_exception("The parameter dst can only be a Point object two bit array.");
                    RETURN_NULL();
                }
            }
    ZEND_HASH_FOREACH_END();

    try {
        Mat mat = getPerspectiveTransform(src_points, dst_points, (int)solveMethod);
        zval instance;
        object_init_ex(&instance, opencv_mat_ce);
        opencv_mat_object *instance_object = Z_PHP_MAT_OBJ_P(&instance);

        instance_object->mat = new Mat(mat);

        opencv_mat_update_property_by_c_mat(&instance, instance_object->mat);

        RETURN_ZVAL(&instance, 0, 0); //return php Mat object
    } catch (Exception e) {
        opencv_throw_exception(e.what());
    }

}


PHP_FUNCTION(opencv_warp_perspective){

    zval *src_zval, *dst_zval, *M_zval, *dsize_zval, *border_value_zval = nullptr;
    long flags = INTER_LINEAR ,borderMode = BORDER_CONSTANT;

    if (zend_parse_parameters_ex(ZEND_PARSE_PARAMS_THROW, ZEND_NUM_ARGS(), "OzOO|llO",
                                 &src_zval ,opencv_mat_ce,
                                 &dst_zval ,
                                 &M_zval ,opencv_mat_ce,
                                 &dsize_zval ,opencv_size_ce,
                                 &flags,
                                 &borderMode,
                                 &border_value_zval, opencv_scalar_ce
    ) == FAILURE) {
        RETURN_NULL();
    }

    Scalar borderValue = Scalar();
    if (border_value_zval != nullptr) {
        opencv_scalar_object *border_value_object = Z_PHP_SCALAR_OBJ_P(border_value_zval);
        borderValue = *border_value_object->scalar;
    }

    opencv_mat_object *src_object = Z_PHP_MAT_OBJ_P(src_zval);
    opencv_mat_object *M_object = Z_PHP_MAT_OBJ_P(M_zval);
    opencv_size_object *dsize_object = Z_PHP_SIZE_OBJ_P(dsize_zval);

    opencv_mat_object *dst_object;
    zval *dst_real_zval = Z_REFVAL_P(dst_zval);

    if (Z_TYPE_P(dst_real_zval) == IS_OBJECT && Z_OBJCE_P(dst_real_zval) == opencv_mat_ce) {
        // is Point object
        dst_object = Z_PHP_MAT_OBJ_P(dst_real_zval);
    } else {
        // isn't Mat object
        zval_ptr_dtor(dst_real_zval);
        zval instance;
        object_init_ex(&instance, opencv_mat_ce);
        ZVAL_COPY_VALUE(dst_real_zval, &instance);// Cover dst_real_zval by Mat object
        dst_object = Z_PHP_MAT_OBJ_P(dst_real_zval);
    }
    try{
        Mat dst;
        warpPerspective(*src_object->mat, dst, *M_object->mat, *dsize_object->size, (int) flags, (int) borderMode, borderValue);
        dst_object->mat = new Mat(dst);
        opencv_mat_update_property_by_c_mat(dst_real_zval, dst_object->mat);

        RETURN_NULL();

    } catch (Exception e) {
        opencv_throw_exception(e.what());
    }


}


/**
 * color conversion code in CV\cvtColor,opencv enum ColorConversionCodes
 * @param module_number
 */
void opencv_color_conversion_code_init(int module_number) {

    //!< add alpha channel to RGB or BGR image, equal to 0
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_BGR2BGRA", COLOR_BGR2BGRA, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_RGB2RGBA", COLOR_RGB2RGBA, CONST_CS | CONST_PERSISTENT);

    //!< remove alpha channel from RGB or BGR image, equal to 1
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_BGRA2BGR", COLOR_BGRA2BGR, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_RGBA2RGB", COLOR_RGBA2RGB, CONST_CS | CONST_PERSISTENT);

    //!< convert between RGB and BGR color spaces (with or without alpha channel) ,equal to 2
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_BGR2RGBA", COLOR_BGR2RGBA, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_RGB2BGRA", COLOR_RGB2BGRA, CONST_CS | CONST_PERSISTENT);

    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_RGBA2BGR", COLOR_RGBA2BGR, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_BGRA2RGB", COLOR_BGRA2RGB, CONST_CS | CONST_PERSISTENT);

    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_BGR2RGB", COLOR_BGR2RGB, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_RGB2BGR", COLOR_RGB2BGR, CONST_CS | CONST_PERSISTENT);

    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_BGRA2RGBA", COLOR_BGRA2RGBA, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_RGBA2BGRA", COLOR_RGBA2BGRA, CONST_CS | CONST_PERSISTENT);

    //!< convert between RGB/BGR and grayscale, @ref color_convert_rgb_gray "color conversions",equal to 6
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_BGR2GRAY", COLOR_BGR2GRAY, CONST_CS | CONST_PERSISTENT);

    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_RGB2GRAY", COLOR_RGB2GRAY, CONST_CS | CONST_PERSISTENT);

    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_GRAY2BGR", COLOR_GRAY2BGR, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_GRAY2RGB", COLOR_GRAY2RGB, CONST_CS | CONST_PERSISTENT);

    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_GRAY2BGRA", COLOR_GRAY2BGRA, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_GRAY2RGBA", COLOR_GRAY2RGBA, CONST_CS | CONST_PERSISTENT);

    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_BGRA2GRAY", COLOR_BGRA2GRAY, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_RGBA2GRAY", COLOR_RGBA2GRAY, CONST_CS | CONST_PERSISTENT);

    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_BGR2BGR565", COLOR_BGR2BGR565, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_RGB2BGR565", COLOR_RGB2BGR565, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_BGR5652BGR", COLOR_BGR5652BGR, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_BGR5652RGB", COLOR_BGR5652RGB, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_BGRA2BGR565", COLOR_BGRA2BGR565, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_BGR5652BGRA", COLOR_BGR5652BGRA, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_BGR5652RGBA", COLOR_BGR5652RGBA, CONST_CS | CONST_PERSISTENT);

    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_GRAY2BGR565", COLOR_GRAY2BGR565, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_BGR5652GRAY", COLOR_BGR5652GRAY, CONST_CS | CONST_PERSISTENT);

    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_BGR2BGR555", COLOR_BGR2BGR555, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_RGB2BGR555", COLOR_RGB2BGR555, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_BGR5552BGR", COLOR_BGR5552BGR, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_BGR5552RGB", COLOR_BGR5552RGB, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_BGRA2BGR555", COLOR_BGRA2BGR555, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_RGBA2BGR555", COLOR_RGBA2BGR555, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_BGR5552BGRA", COLOR_BGR5552BGRA, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_BGR5552RGBA", COLOR_BGR5552RGBA, CONST_CS | CONST_PERSISTENT);

    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_GRAY2BGR555", COLOR_GRAY2BGR555, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_BGR5552GRAY", COLOR_BGR5552GRAY, CONST_CS | CONST_PERSISTENT);

    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_BGR2XYZ", COLOR_BGR2XYZ, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_RGB2XYZ", COLOR_RGB2XYZ, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_XYZ2BGR", COLOR_XYZ2BGR, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_XYZ2RGB", COLOR_XYZ2RGB, CONST_CS | CONST_PERSISTENT);

    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_BGR2YCrCb", COLOR_BGR2YCrCb, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_RGB2YCrCb", COLOR_RGB2YCrCb, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YCrCb2BGR", COLOR_YCrCb2BGR, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YCrCb2RGB", COLOR_YCrCb2RGB, CONST_CS | CONST_PERSISTENT);

    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_BGR2HSV", COLOR_BGR2HSV, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_RGB2HSV", COLOR_RGB2HSV, CONST_CS | CONST_PERSISTENT);

    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_BGR2Lab", COLOR_BGR2Lab, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_RGB2Lab", COLOR_RGB2Lab, CONST_CS | CONST_PERSISTENT);

    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_BGR2Luv", COLOR_BGR2Luv, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_RGB2Luv", COLOR_RGB2Luv, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_BGR2HLS", COLOR_BGR2HLS, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_RGB2HLS", COLOR_RGB2HLS, CONST_CS | CONST_PERSISTENT);

    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_HSV2BGR", COLOR_HSV2BGR, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_HSV2RGB", COLOR_HSV2RGB, CONST_CS | CONST_PERSISTENT);

    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_Lab2BGR", COLOR_Lab2BGR, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_Lab2RGB", COLOR_Lab2RGB, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_Luv2BGR", COLOR_Luv2BGR, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_Luv2RGB", COLOR_Luv2RGB, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_HLS2BGR", COLOR_HLS2BGR, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_HLS2RGB", COLOR_HLS2RGB, CONST_CS | CONST_PERSISTENT);

    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_BGR2HSV_FULL", COLOR_BGR2HSV_FULL, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_RGB2HSV_FULL", COLOR_RGB2HSV_FULL, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_BGR2HLS_FULL", COLOR_BGR2HLS_FULL, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_RGB2HLS_FULL", COLOR_RGB2HLS_FULL, CONST_CS | CONST_PERSISTENT);

    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_HSV2BGR_FULL", COLOR_HSV2BGR_FULL, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_HSV2RGB_FULL", COLOR_HSV2RGB_FULL, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_HLS2BGR_FULL", COLOR_HLS2BGR_FULL, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_HLS2RGB_FULL", COLOR_HLS2RGB_FULL, CONST_CS | CONST_PERSISTENT);

    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_LBGR2Lab", COLOR_LBGR2Lab, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_LRGB2Lab", COLOR_LRGB2Lab, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_LBGR2Luv", COLOR_LBGR2Luv, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_LRGB2Luv", COLOR_LRGB2Luv, CONST_CS | CONST_PERSISTENT);

    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_Lab2LBGR", COLOR_Lab2LBGR, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_Lab2LRGB", COLOR_Lab2LRGB, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_Luv2LBGR", COLOR_Luv2LBGR, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_Luv2LRGB", COLOR_Luv2LRGB, CONST_CS | CONST_PERSISTENT);

    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_BGR2YUV", COLOR_BGR2YUV, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_RGB2YUV", COLOR_RGB2YUV, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV2BGR", COLOR_YUV2BGR, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV2RGB", COLOR_YUV2RGB, CONST_CS | CONST_PERSISTENT);

    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV2RGB_NV12", COLOR_YUV2RGB_NV12, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV2BGR_NV12", COLOR_YUV2BGR_NV12, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV2RGB_NV21", COLOR_YUV2RGB_NV21, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV2BGR_NV21", COLOR_YUV2BGR_NV21, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV420sp2RGB", COLOR_YUV420sp2RGB, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV420sp2BGR", COLOR_YUV420sp2BGR, CONST_CS | CONST_PERSISTENT);

    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV2RGBA_NV12", COLOR_YUV2RGBA_NV12, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV2BGRA_NV12", COLOR_YUV2BGRA_NV12, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV2RGBA_NV21", COLOR_YUV2RGBA_NV21, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV2BGRA_NV21", COLOR_YUV2BGRA_NV21, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV420sp2RGBA", COLOR_YUV420sp2RGBA, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV420sp2BGRA", COLOR_YUV420sp2BGRA, CONST_CS | CONST_PERSISTENT);

    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV2RGB_YV12", COLOR_YUV2RGB_YV12, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV2BGR_YV12", COLOR_YUV2BGR_YV12, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV2RGB_IYUV", COLOR_YUV2RGB_IYUV, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV2BGR_IYUV", COLOR_YUV2BGR_IYUV, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV2RGB_I420", COLOR_YUV2RGB_I420, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV2BGR_I420", COLOR_YUV2BGR_I420, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV420p2RGB", COLOR_YUV420p2RGB, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV420p2BGR", COLOR_YUV420p2BGR, CONST_CS | CONST_PERSISTENT);

    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV2RGBA_YV12", COLOR_YUV2RGBA_YV12, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV2BGRA_YV12", COLOR_YUV2BGRA_YV12, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV2RGBA_IYUV", COLOR_YUV2RGBA_IYUV, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV2BGRA_IYUV", COLOR_YUV2BGRA_IYUV, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV2RGBA_I420", COLOR_YUV2RGBA_I420, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV2BGRA_I420", COLOR_YUV2BGRA_I420, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV420p2RGBA", COLOR_YUV420p2RGBA, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV420p2BGRA", COLOR_YUV420p2BGRA, CONST_CS | CONST_PERSISTENT);

    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV2GRAY_420", COLOR_YUV2GRAY_420, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV2GRAY_NV21", COLOR_YUV2GRAY_NV21, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV2GRAY_NV12", COLOR_YUV2GRAY_NV12, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV2GRAY_YV12", COLOR_YUV2GRAY_YV12, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV2GRAY_IYUV", COLOR_YUV2GRAY_IYUV, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV2GRAY_I420", COLOR_YUV2GRAY_I420, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV420sp2GRAY", COLOR_YUV420sp2GRAY, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV420p2GRAY", COLOR_YUV420p2GRAY, CONST_CS | CONST_PERSISTENT);

    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV2RGB_UYVY", COLOR_YUV2RGB_UYVY, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV2BGR_UYVY", COLOR_YUV2BGR_UYVY, CONST_CS | CONST_PERSISTENT);

    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV2RGB_Y422", COLOR_YUV2RGB_Y422, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV2BGR_Y422", COLOR_YUV2BGR_Y422, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV2RGB_UYNV", COLOR_YUV2RGB_UYNV, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV2BGR_UYNV", COLOR_YUV2BGR_UYNV, CONST_CS | CONST_PERSISTENT);

    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV2RGBA_UYVY", COLOR_YUV2RGBA_UYVY, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV2BGRA_UYVY", COLOR_YUV2BGRA_UYVY, CONST_CS | CONST_PERSISTENT);

    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV2RGBA_Y422", COLOR_YUV2RGBA_Y422, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV2BGRA_Y422", COLOR_YUV2BGRA_Y422, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV2RGBA_UYNV", COLOR_YUV2RGBA_UYNV, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV2BGRA_UYNV", COLOR_YUV2BGRA_UYNV, CONST_CS | CONST_PERSISTENT);

    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV2RGB_YUY2", COLOR_YUV2RGB_YUY2, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV2BGR_YUY2", COLOR_YUV2BGR_YUY2, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV2RGB_YVYU", COLOR_YUV2RGB_YVYU, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV2BGR_YVYU", COLOR_YUV2BGR_YVYU, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV2RGB_YUYV", COLOR_YUV2RGB_YUYV, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV2BGR_YUYV", COLOR_YUV2BGR_YUYV, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV2RGB_YUNV", COLOR_YUV2RGB_YUNV, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV2BGR_YUNV", COLOR_YUV2BGR_YUNV, CONST_CS | CONST_PERSISTENT);

    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV2RGBA_YUY2", COLOR_YUV2RGBA_YUY2, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV2BGRA_YUY2", COLOR_YUV2BGRA_YUY2, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV2RGBA_YVYU", COLOR_YUV2RGBA_YVYU, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV2BGRA_YVYU", COLOR_YUV2BGRA_YVYU, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV2RGBA_YUYV", COLOR_YUV2RGBA_YUYV, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV2BGRA_YUYV", COLOR_YUV2BGRA_YUYV, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV2RGBA_YUNV", COLOR_YUV2RGBA_YUNV, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV2BGRA_YUNV", COLOR_YUV2BGRA_YUNV, CONST_CS | CONST_PERSISTENT);

    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV2GRAY_UYVY", COLOR_YUV2GRAY_UYVY, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV2GRAY_YUY2", COLOR_YUV2GRAY_YUY2, CONST_CS | CONST_PERSISTENT);

    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV2GRAY_Y422", COLOR_YUV2GRAY_Y422, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV2GRAY_UYNV", COLOR_YUV2GRAY_UYNV, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV2GRAY_YVYU", COLOR_YUV2GRAY_YVYU, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV2GRAY_YUYV", COLOR_YUV2GRAY_YUYV, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_YUV2GRAY_YUNV", COLOR_YUV2GRAY_YUNV, CONST_CS | CONST_PERSISTENT);

    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_RGBA2mRGBA", COLOR_RGBA2mRGBA, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_mRGBA2RGBA", COLOR_mRGBA2RGBA, CONST_CS | CONST_PERSISTENT);

    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_RGB2YUV_I420", COLOR_RGB2YUV_I420, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_BGR2YUV_I420", COLOR_BGR2YUV_I420, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_RGB2YUV_IYUV", COLOR_RGB2YUV_IYUV, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_BGR2YUV_IYUV", COLOR_BGR2YUV_IYUV, CONST_CS | CONST_PERSISTENT);

    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_RGBA2YUV_I420", COLOR_RGBA2YUV_I420, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_BGRA2YUV_I420", COLOR_BGRA2YUV_I420, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_RGBA2YUV_IYUV", COLOR_RGBA2YUV_IYUV, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_BGRA2YUV_IYUV", COLOR_BGRA2YUV_IYUV, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_RGB2YUV_YV12", COLOR_RGB2YUV_YV12, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_BGR2YUV_YV12", COLOR_BGR2YUV_YV12, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_RGBA2YUV_YV12", COLOR_RGBA2YUV_YV12, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_BGRA2YUV_YV12", COLOR_BGRA2YUV_YV12, CONST_CS | CONST_PERSISTENT);

    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_BayerBG2BGR", COLOR_BayerBG2BGR, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_BayerGB2BGR", COLOR_BayerGB2BGR, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_BayerRG2BGR", COLOR_BayerRG2BGR, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_BayerGR2BGR", COLOR_BayerGR2BGR, CONST_CS | CONST_PERSISTENT);

    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_BayerBG2RGB", COLOR_BayerBG2RGB, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_BayerGB2RGB", COLOR_BayerGB2RGB, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_BayerRG2RGB", COLOR_BayerRG2RGB, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_BayerGR2RGB", COLOR_BayerGR2RGB, CONST_CS | CONST_PERSISTENT);

    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_BayerBG2GRAY", COLOR_BayerBG2GRAY, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_BayerGB2GRAY", COLOR_BayerGB2GRAY, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_BayerRG2GRAY", COLOR_BayerRG2GRAY, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_BayerGR2GRAY", COLOR_BayerGR2GRAY, CONST_CS | CONST_PERSISTENT);

    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_BayerBG2BGR_VNG", COLOR_BayerBG2BGR_VNG, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_BayerGB2BGR_VNG", COLOR_BayerGB2BGR_VNG, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_BayerRG2BGR_VNG", COLOR_BayerRG2BGR_VNG, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_BayerGR2BGR_VNG", COLOR_BayerGR2BGR_VNG, CONST_CS | CONST_PERSISTENT);

    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_BayerBG2RGB_VNG", COLOR_BayerBG2RGB_VNG, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_BayerGB2RGB_VNG", COLOR_BayerGB2RGB_VNG, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_BayerRG2RGB_VNG", COLOR_BayerRG2RGB_VNG, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_BayerGR2RGB_VNG", COLOR_BayerGR2RGB_VNG, CONST_CS | CONST_PERSISTENT);

    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_BayerBG2BGR_EA", COLOR_BayerBG2BGR_EA, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_BayerGB2BGR_EA", COLOR_BayerGB2BGR_EA, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_BayerRG2BGR_EA", COLOR_BayerRG2BGR_EA, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_BayerGR2BGR_EA", COLOR_BayerGR2BGR_EA, CONST_CS | CONST_PERSISTENT);

    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_BayerBG2RGB_EA", COLOR_BayerBG2RGB_EA, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_BayerGB2RGB_EA", COLOR_BayerGB2RGB_EA, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_BayerRG2RGB_EA", COLOR_BayerRG2RGB_EA, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_BayerGR2RGB_EA", COLOR_BayerGR2RGB_EA, CONST_CS | CONST_PERSISTENT);

    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "COLOR_COLORCVT_MAX", COLOR_COLORCVT_MAX, CONST_CS | CONST_PERSISTENT);
}

void opencv_line_type_init(int module_number) {
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "FILLED", FILLED, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "LINE_4", LINE_4, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "LINE_8", LINE_8, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "LINE_AA", LINE_AA, CONST_CS | CONST_PERSISTENT);
}

void opencv_morph_shapes_init(int module_number) {
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "MORPH_RECT", MORPH_RECT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "MORPH_CROSS", MORPH_CROSS, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "MORPH_ELLIPSE", MORPH_ELLIPSE, CONST_CS | CONST_PERSISTENT);
}

void opencv_morph_types_init(int module_number) {
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "MORPH_ERODE", MORPH_ERODE, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "MORPH_DILATE", MORPH_DILATE, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "MORPH_OPEN", MORPH_OPEN, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "MORPH_CLOSE", MORPH_CLOSE, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "MORPH_GRADIENT", MORPH_GRADIENT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "MORPH_TOPHAT", MORPH_TOPHAT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "MORPH_BLACKHAT", MORPH_BLACKHAT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "MORPH_HITMISS", MORPH_HITMISS, CONST_CS | CONST_PERSISTENT);
}

//! floodfill algorithm flags
void opencv_flood_fill_flags_init(int module_number) {
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "FLOODFILL_FIXED_RANGE", FLOODFILL_FIXED_RANGE, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "FLOODFILL_MASK_ONLY", FLOODFILL_MASK_ONLY, CONST_CS | CONST_PERSISTENT);
}

//! type of the threshold operation
//! ![threshold types](pics/threshold.png)
void opencv_threshold_types_init(int module_number) {
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "THRESH_BINARY", THRESH_BINARY, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "THRESH_BINARY_INV", THRESH_BINARY_INV, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "THRESH_TRUNC", THRESH_TRUNC, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "THRESH_TOZERO", THRESH_TOZERO, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "THRESH_TOZERO_INV", THRESH_TOZERO_INV, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "THRESH_MASK", THRESH_MASK, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "THRESH_OTSU", THRESH_OTSU, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "THRESH_TRIANGLE", THRESH_TRIANGLE, CONST_CS | CONST_PERSISTENT);
}

//AdaptiveThresholdTypes
void opencv_adaptive_threshold_types_init(int module_number) {
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "ADAPTIVE_THRESH_MEAN_C", ADAPTIVE_THRESH_MEAN_C, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "ADAPTIVE_THRESH_GAUSSIAN_C", ADAPTIVE_THRESH_GAUSSIAN_C,
                              CONST_CS | CONST_PERSISTENT);
}

void opencv_retrieval_modes_init(int module_number) {
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "RETR_EXTERNAL", RETR_EXTERNAL, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "RETR_LIST", RETR_LIST, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "RETR_CCOMP", RETR_CCOMP, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "RETR_TREE", RETR_TREE, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "RETR_FLOODFILL", RETR_FLOODFILL, CONST_CS | CONST_PERSISTENT);
}

void opencv_contour_approximation_modes_init(int module_number) {
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "CHAIN_APPROX_NONE", CHAIN_APPROX_NONE, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "CHAIN_APPROX_SIMPLE", CHAIN_APPROX_SIMPLE, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "CHAIN_APPROX_TC89_L1", CHAIN_APPROX_TC89_L1, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "CHAIN_APPROX_TC89_KCOS", CHAIN_APPROX_TC89_KCOS, CONST_CS | CONST_PERSISTENT);
}
