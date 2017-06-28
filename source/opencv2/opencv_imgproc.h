//
// Created by hiho on 17-6-25.
//

#ifndef OPENCV_OPENCV_IMGPROC_H
#define OPENCV_OPENCV_IMGPROC_H

void opencv_imgproc_init(int module_number);
void opencv_color_conversion_code_init(int module_number);
void opencv_line_type_init(int module_number);
PHP_FUNCTION(opencv_cv_t_color);
PHP_FUNCTION(opencv_ellipse);
PHP_FUNCTION(opencv_circle);
PHP_FUNCTION(opencv_fill_poly);//TODO fillPoly
PHP_FUNCTION(opencv_line);
PHP_FUNCTION(opencv_rectangle);
PHP_FUNCTION(opencv_rectangle_by_point);
PHP_FUNCTION(opencv_rectangle_by_rect);

#endif //OPENCV_OPENCV_IMGPROC_H
