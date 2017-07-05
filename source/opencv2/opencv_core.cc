

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
    opencv_mat_object *dst_object;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "OdOddz|l",
                              &src1_zval, opencv_mat_ce, &alpha,
                              &src2_zval, opencv_mat_ce, &beta,
                              &gamma,
                              &dst_zval,
                              &dtype) == FAILURE) {
        RETURN_NULL();
    }

    zval *dst_real_zval = Z_REFVAL_P(dst_zval);
    opencv_mat_object *src1_obj = Z_PHP_MAT_OBJ_P(src1_zval);
    opencv_mat_object *src2_obj = Z_PHP_MAT_OBJ_P(src2_zval);


    if(Z_TYPE_P(dst_real_zval) == IS_OBJECT && Z_OBJCE_P(dst_real_zval)==opencv_mat_ce){
        // is Mat object
        dst_object = Z_PHP_MAT_OBJ_P(dst_real_zval);
    } else{
        // isn't Mat object
        zval instance;
        Mat dst;
        object_init_ex(&instance,opencv_mat_ce);
        ZVAL_COPY_VALUE(dst_real_zval, &instance);// Cover dst_real_zval by Mat object
        dst_object = Z_PHP_MAT_OBJ_P(dst_real_zval);
        dst_object->mat = new Mat(dst);
    }

    try{
        addWeighted(*src1_obj->mat, alpha, *src2_obj->mat, beta, gamma, *dst_object->mat, dtype);
    }catch (Exception e){
        opencv_throw_exception(e.what());
    }
    opencv_mat_update_property_by_c_mat(dst_real_zval, dst_object->mat);

    RETURN_NULL();
}

#define OPENCV_CONNECT(text1,text2) text1##text2

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


    for(unsigned long i=0; i < channels.size(); i++){
        zval OPENCV_CONNECT(zval,i);
        Mat OPENCV_CONNECT(mat,i);
        opencv_mat_object *OPENCV_CONNECT(mat_object,i);
        object_init_ex(&OPENCV_CONNECT(zval,i),opencv_mat_ce);
        OPENCV_CONNECT(mat_object,i) = Z_PHP_MAT_OBJ_P(&OPENCV_CONNECT(zval,i));
        OPENCV_CONNECT(mat,i) = channels.at(i);
        OPENCV_CONNECT(mat_object,i)->mat = new Mat(OPENCV_CONNECT(mat,i));
        opencv_mat_update_property_by_c_mat(&OPENCV_CONNECT(zval,i),OPENCV_CONNECT(mat_object,i)->mat);
        add_next_index_zval(&return_val,&OPENCV_CONNECT(zval,i));
    }

    RETURN_ZVAL(&return_val,0,0);
}

