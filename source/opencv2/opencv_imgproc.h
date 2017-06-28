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

#endif //OPENCV_OPENCV_IMGPROC_H
