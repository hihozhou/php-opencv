

#include "../../php_opencv.h"
#include "opencv_core.h"
#include "core/opencv_mat.h"
#include "../../opencv_exception.h"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

zend_class_entry *opencv_formatter_ce;

const zend_function_entry opencv_formatter_methods[] = {
        PHP_FE_END
};

void opencv_formatter_init(){
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce, OPENCV_NS, "Formatter", opencv_formatter_methods);
    opencv_formatter_ce = zend_register_internal_class(&ce);
}

void opencv_formatter_const_init(int module_number){
    zend_declare_class_constant_long(opencv_formatter_ce,"FMT_DEFAULT",sizeof("FMT_DEFAULT")-1,Formatter::FMT_DEFAULT);
    zend_declare_class_constant_long(opencv_formatter_ce,"FMT_MATLAB",sizeof("FMT_MATLAB")-1,Formatter::FMT_MATLAB);
    zend_declare_class_constant_long(opencv_formatter_ce,"FMT_CSV",sizeof("FMT_CSV")-1,Formatter::FMT_CSV);
    zend_declare_class_constant_long(opencv_formatter_ce,"FMT_PYTHON",sizeof("FMT_PYTHON")-1,Formatter::FMT_PYTHON);
    zend_declare_class_constant_long(opencv_formatter_ce,"FMT_NUMPY",sizeof("FMT_NUMPY")-1,Formatter::FMT_NUMPY);
    zend_declare_class_constant_long(opencv_formatter_ce,"FMT_C",sizeof("FMT_C")-1,Formatter::FMT_C);
}


void opencv_core_init(int module_number)
{
    opencv_formatter_init();
    opencv_formatter_const_init(module_number);
}

/**
 * CV\addWeighted
 * @param execute_data
 * @param return_value
 */
PHP_FUNCTION(opencv_add_weighted){
    double alpha, beta, gamma;
    long dtype = -1;
    zval *src1_zval, *src2_zval, *dst_zval = NULL;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "OdOdd|Ol",
                              &src1_zval, opencv_mat_ce, &alpha,
                              &src2_zval, opencv_mat_ce, &beta,
                              &gamma,
                              &dst_zval, opencv_mat_ce,
                              &dtype) == FAILURE) {
        RETURN_NULL();
    }
    opencv_mat_object *src1_obj = Z_PHP_MAT_OBJ_P(src1_zval);
    opencv_mat_object *src2_obj = Z_PHP_MAT_OBJ_P(src2_zval);

    if(dst_zval != NULL){
        opencv_mat_object *dst_obj = Z_PHP_MAT_OBJ_P(dst_zval);
        try{
            addWeighted(*src1_obj->mat, alpha, *src2_obj->mat, beta, gamma, *dst_obj->mat, dtype);
        }catch (Exception e){
            opencv_throw_exception(e.what());//throw exception
        }

        opencv_mat_update_property_by_c_mat(dst_zval, dst_obj->mat);

        RETURN_NULL();
    }else{
        zval instance;
        Mat dst;
        try{
            addWeighted(*src1_obj->mat, alpha, *src2_obj->mat, beta, gamma, dst, dtype);
        }catch (Exception e){
            opencv_throw_exception(e.what());//throw exception
        }

        object_init_ex(&instance,opencv_mat_ce);
        opencv_mat_object *new_obj = Z_PHP_MAT_OBJ_P(&instance);
        new_obj->mat = new Mat(dst);

        opencv_mat_update_property_by_c_mat(&instance, new_obj->mat);
        RETURN_ZVAL(&instance,0,0);
    }
}

/**
 * CV\split
 * @param execute_data
 * @param return_value
 */
PHP_FUNCTION(opencv_split){
    double alpha, beta, gamma;
    long dtype = -1;
    zval *src_zval;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "O", &src_zval, opencv_mat_ce) == FAILURE) {
        RETURN_NULL();
    }
    opencv_mat_object *src_obj = Z_PHP_MAT_OBJ_P(src_zval);
    std::vector<Mat> channels;
    split(*src_obj->mat,channels);
    zval return_val,blue_zval,green_zval,red_zval;
    Mat blue,green,red;
    array_init(&return_val);

    object_init_ex(&blue_zval,opencv_mat_ce);
    opencv_mat_object *blue_mat_object = Z_PHP_MAT_OBJ_P(&blue_zval);
    blue = channels.at(0);
    blue_mat_object->mat = new Mat(blue);
    opencv_mat_update_property_by_c_mat(&blue_zval,blue_mat_object->mat);

    object_init_ex(&green_zval,opencv_mat_ce);
    opencv_mat_object *green_mat_object = Z_PHP_MAT_OBJ_P(&green_zval);
    green = channels.at(1);
    green_mat_object->mat = new Mat(green);
    opencv_mat_update_property_by_c_mat(&green_zval,green_mat_object->mat);

    object_init_ex(&red_zval,opencv_mat_ce);
    opencv_mat_object *red_mat_object = Z_PHP_MAT_OBJ_P(&red_zval);
    red = channels.at(2);
    red_mat_object->mat = new Mat(red);
    opencv_mat_update_property_by_c_mat(&red_zval,red_mat_object->mat);

    add_next_index_zval(&return_val,&blue_zval);
    add_next_index_zval(&return_val,&green_zval);
    add_next_index_zval(&return_val,&red_zval);

    RETURN_ZVAL(&return_val,0,0);
}

