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
#include "opencv_core.h"
#include "core/opencv_mat.h"
#include "../../opencv_exception.h"
#include "core/opencv_type.h"


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

/**
 * @see NormTypes
 * @param module_number
 */
void opencv_norm_types_const_init(int module_number){

    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "NORM_INF", NORM_INF, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "NORM_L1", NORM_L1, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "NORM_L2", NORM_L2, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "NORM_L2SQR", NORM_L2SQR, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "NORM_HAMMING", NORM_HAMMING, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "NORM_HAMMING2", NORM_HAMMING2, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "NORM_TYPE_MASK", NORM_TYPE_MASK, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "NORM_RELATIVE", NORM_RELATIVE, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "NORM_MINMAX", NORM_MINMAX, CONST_CS | CONST_PERSISTENT);
}

//todo
//void opencv_hershey_fonts_const_init(int module_number){

    //cv::HersheyFonts
//    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "FONT_HERSHEY_SIMPLEX", FONT_HERSHEY_SIMPLEX, CONST_CS | CONST_PERSISTENT);
//    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "FONT_HERSHEY_PLAIN", FONT_HERSHEY_PLAIN, CONST_CS | CONST_PERSISTENT);
//    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "FONT_HERSHEY_DUPLEX", FONT_HERSHEY_DUPLEX, CONST_CS | CONST_PERSISTENT);
//    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "FONT_HERSHEY_COMPLEX", FONT_HERSHEY_COMPLEX, CONST_CS | CONST_PERSISTENT);
//    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "FONT_HERSHEY_TRIPLEX", FONT_HERSHEY_TRIPLEX, CONST_CS | CONST_PERSISTENT);
//    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "FONT_HERSHEY_COMPLEX_SMALL", FONT_HERSHEY_COMPLEX_SMALL, CONST_CS | CONST_PERSISTENT);
//    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "FONT_HERSHEY_SCRIPT_SIMPLEX", FONT_HERSHEY_SCRIPT_SIMPLEX, CONST_CS | CONST_PERSISTENT);
//    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "FONT_HERSHEY_SCRIPT_COMPLEX", FONT_HERSHEY_SCRIPT_COMPLEX, CONST_CS | CONST_PERSISTENT);
//    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "FONT_ITALIC", FONT_ITALIC, CONST_CS | CONST_PERSISTENT);
//}


void opencv_core_init(int module_number)
{
    opencv_formatter_init();
    opencv_formatter_const_init(module_number);
    opencv_norm_types_const_init(module_number);
//    opencv_hershey_fonts_const_init(module_number);
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
        zval_ptr_dtor(dst_real_zval);
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


/**
 * 矩阵数据按通道切割，CV\split(Mat $mat)，返回一个存在切割后矩阵的数组
 * CV\split
 * @param execute_data
 * @param return_value
 */
PHP_FUNCTION(opencv_split){
    double alpha, beta, gamma;
    long dtype = -1;
    zval *src_zval;

    //传入一个Mat对象
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "O", &src_zval, opencv_mat_ce) == FAILURE) {
        RETURN_NULL();
    }
    opencv_mat_object *src_obj = Z_PHP_MAT_OBJ_P(src_zval);
    std::vector<Mat> channels;
    split(*src_obj->mat,channels);//使用split方法讲mat切割放在vector中
    zval return_val,blue_zval,green_zval,red_zval;
    Mat blue,green,red;
    array_init(&return_val);


    //遍历切割后得到的vector
    for(unsigned long i=0; i < channels.size(); i++){
        //创建对象
        zval OPENCV_CONNECT(zval,i);
        Mat OPENCV_CONNECT(mat,i);
        opencv_mat_object *OPENCV_CONNECT(mat_object,i);
        object_init_ex(&OPENCV_CONNECT(zval,i),opencv_mat_ce);
        OPENCV_CONNECT(mat_object,i) = Z_PHP_MAT_OBJ_P(&OPENCV_CONNECT(zval,i));
        OPENCV_CONNECT(mat,i) = channels.at(i);
        OPENCV_CONNECT(mat_object,i)->mat = new Mat(OPENCV_CONNECT(mat,i));
        opencv_mat_update_property_by_c_mat(&OPENCV_CONNECT(zval,i),OPENCV_CONNECT(mat_object,i)->mat);
        add_next_index_zval(&return_val,&OPENCV_CONNECT(zval,i));//存放在返回的数组中
    }

    RETURN_ZVAL(&return_val,0,0);
}


/**
 * CV\merge
 * @param execute_data
 * @param return_value
 */
PHP_FUNCTION(opencv_merge){
    zval *channels_zval, *array_val_zval, *dst_zval;
    zend_ulong _h;
    opencv_mat_object *dst_object;


    if (zend_parse_parameters(ZEND_NUM_ARGS(), "az", &channels_zval, &dst_zval) == FAILURE) {
        RETURN_NULL();
    }

    unsigned long channel_count = zend_hash_num_elements(Z_ARRVAL_P(channels_zval));
    std::vector<Mat> channels;
    if(channel_count == 0){
        opencv_throw_exception("array lenght must be >=1");
        RETURN_NULL();
    }

    channels.reserve(channel_count);
    opencv_mat_object *mat_obj;

    ZEND_HASH_FOREACH_NUM_KEY_VAL(Z_ARRVAL_P(channels_zval),_h,array_val_zval){
                //check array_val_zval is Mat object
                again:
                if(Z_TYPE_P(array_val_zval) == IS_OBJECT && Z_OBJCE_P(array_val_zval)==opencv_mat_ce){
                    mat_obj = Z_PHP_MAT_OBJ_P(array_val_zval);
                    channels.push_back(*mat_obj->mat);
                }else if(Z_TYPE_P(array_val_zval) == IS_REFERENCE){
                    array_val_zval = Z_REFVAL_P(array_val_zval);
                    goto again;
                } else {
                    opencv_throw_exception("array value just Mat object.");
                    RETURN_NULL();
                }
    }ZEND_HASH_FOREACH_END();

    zval *dst_real_zval = Z_REFVAL_P(dst_zval);
    if(Z_TYPE_P(dst_real_zval) == IS_OBJECT && Z_OBJCE_P(dst_real_zval)==opencv_mat_ce){
        // is Mat object
        dst_object = Z_PHP_MAT_OBJ_P(dst_real_zval);
    } else{
        // isn't Mat object
        zval_ptr_dtor(dst_real_zval);
        zval instance;
        Mat dst;
        object_init_ex(&instance,opencv_mat_ce);
        ZVAL_COPY_VALUE(dst_real_zval, &instance);// Cover dst_real_zval by Mat object
        dst_object = Z_PHP_MAT_OBJ_P(dst_real_zval);
        dst_object->mat = new Mat(dst);
    }

    try{
        merge(channels, *dst_object->mat);
    }catch (Exception e){
        opencv_throw_exception(e.what());
    }
    opencv_mat_update_property_by_c_mat(dst_real_zval, dst_object->mat);
    RETURN_NULL();

}

/**
 * CV\getOptimalDFTSize
 * @param execute_data
 * @param return_value
 */
PHP_FUNCTION(opencv_get_optimal_dft_size){
    long vecsize;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "l", &vecsize) == FAILURE) {
        RETURN_NULL();
    }
    RETURN_LONG(getOptimalDFTSize((int)vecsize));
}

/**
 * copyMakeBorder
 * @param execute_data
 * @param return_value
 */
PHP_FUNCTION(opencv_copy_make_border){
    zval *src_zval, *dst_zval, *value_zval = NULL;
    long top, bottom, left, right, border_type;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "Ozlllll|O",
                              &src_zval, opencv_mat_ce,
                              &dst_zval,
                              &top, &bottom, &left, &right, &border_type,
                              &value_zval, opencv_scalar_ce) == FAILURE) {
        RETURN_NULL();
    }

    opencv_mat_object *src_object = Z_PHP_MAT_OBJ_P(src_zval);
    Scalar value;
    if(value_zval == NULL){
        value = Scalar();
    }else{
        opencv_scalar_object *value_object = Z_PHP_SCALAR_OBJ_P(value_zval);
        value = *value_object->scalar;
    }
    opencv_mat_object *dst_object;
    zval *dst_real_zval = Z_REFVAL_P(dst_zval);
    if(Z_TYPE_P(dst_real_zval) == IS_OBJECT && Z_OBJCE_P(dst_real_zval) == opencv_mat_ce){
        // is Mat object
        dst_object = Z_PHP_MAT_OBJ_P(dst_real_zval);
    } else{
        // isn't Mat object
        zval_ptr_dtor(dst_real_zval);
        zval instance;
        Mat dst;
        object_init_ex(&instance,opencv_mat_ce);
        ZVAL_COPY_VALUE(dst_real_zval, &instance);// Cover dst_real_zval by Mat object
        dst_object = Z_PHP_MAT_OBJ_P(dst_real_zval);
        dst_object->mat = new Mat(dst);
    }
    try {
        copyMakeBorder(*src_object->mat, *dst_object->mat, (int)top, (int)bottom, (int)left, (int)right, (int)border_type, value);
    }catch (Exception e){
        opencv_throw_exception(e.what());
    }
    opencv_mat_update_property_by_c_mat(dst_real_zval, dst_object->mat);
    RETURN_NULL();

}

/**
 * CV\dft
 * @param execute_data
 * @param return_value
 */
PHP_FUNCTION(opencv_dft){
    zval *src_zval, *array_val_zval, *dst_zval;
    long flags = 0, nonzero_rows = 0;
    opencv_mat_object *dst_object;


    if (zend_parse_parameters(ZEND_NUM_ARGS(), "Oz|ll", &src_zval, opencv_mat_ce, &dst_zval, &flags, &nonzero_rows) == FAILURE) {
        RETURN_NULL();
    }

    opencv_mat_object *src_object = Z_PHP_MAT_OBJ_P(src_zval);

    zval *dst_real_zval = Z_REFVAL_P(dst_zval);
    if(Z_TYPE_P(dst_real_zval) == IS_OBJECT && Z_OBJCE_P(dst_real_zval)==opencv_mat_ce){
        // is Mat object
        dst_object = Z_PHP_MAT_OBJ_P(dst_real_zval);
    } else{
        // isn't Mat object
        zval_ptr_dtor(dst_real_zval);
        zval instance;
        Mat dst;
        object_init_ex(&instance,opencv_mat_ce);
        ZVAL_COPY_VALUE(dst_real_zval, &instance);// Cover dst_real_zval by Mat object
        dst_object = Z_PHP_MAT_OBJ_P(dst_real_zval);
        dst_object->mat = new Mat(dst);
    }

    try{
        dft(*src_object->mat, *dst_object->mat, (int)flags, (int)nonzero_rows);
    }catch (Exception e){
        opencv_throw_exception(e.what());
    }
    opencv_mat_update_property_by_c_mat(dst_real_zval, dst_object->mat);
    RETURN_NULL();

}

/**
 * CV\magnitude
 * @param execute_data
 * @param return_value
 */
PHP_FUNCTION(opencv_magnitude){
    zval *x_zval, *y_zval, *dst_zval;
    opencv_mat_object *dst_object;


    if (zend_parse_parameters(ZEND_NUM_ARGS(), "OOz",
                              &x_zval, opencv_mat_ce,
                              &y_zval, opencv_mat_ce,
                              &dst_zval) == FAILURE) {
        RETURN_NULL();
    }

    opencv_mat_object *x_object = Z_PHP_MAT_OBJ_P(x_zval);
    opencv_mat_object *y_object = Z_PHP_MAT_OBJ_P(y_zval);

    zval *dst_real_zval = Z_REFVAL_P(dst_zval);
    if(Z_TYPE_P(dst_real_zval) == IS_OBJECT && Z_OBJCE_P(dst_real_zval)==opencv_mat_ce){
        dst_object = Z_PHP_MAT_OBJ_P(dst_real_zval);
    } else{
        zval_ptr_dtor(dst_real_zval);
        zval instance;
        Mat dst;
        object_init_ex(&instance,opencv_mat_ce);
        ZVAL_COPY_VALUE(dst_real_zval, &instance);
        dst_object = Z_PHP_MAT_OBJ_P(dst_real_zval);
        dst_object->mat = new Mat(dst);
    }

    try{
        magnitude(*x_object->mat, *y_object->mat, *dst_object->mat);
    }catch (Exception e){
        opencv_throw_exception(e.what());
    }
    opencv_mat_update_property_by_c_mat(dst_real_zval, dst_object->mat);
    RETURN_NULL();

}

/**
 * Copyright (c) MaleicAcid
 * CV\absdiff
 * @param execute_data
 * @param return_value
 */
PHP_FUNCTION(opencv_absdiff){
    zval *src1_zval, *src2_zval, *dst_zval;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "zzz",
                              &src1_zval,
                              &src2_zval,
                              &dst_zval) == FAILURE) {
        RETURN_NULL();
    }
    opencv_mat_object *src1_mat_object = NULL, *src2_mat_object = NULL, *dst_mat_object = NULL;
    opencv_scalar_object *src1_scalar_object = NULL, *src2_scalar_object = NULL, *dst_scalar_object = NULL;

    int flag = 0;//dst 1 mat,0 scalar

    if(Z_TYPE_P(src1_zval) != IS_OBJECT || Z_TYPE_P(src2_zval) != IS_OBJECT){
        opencv_throw_exception("src1 and src2 parameter must be Mat or Scalar object.");
        RETURN_NULL();
    }

    if(Z_OBJCE_P(src1_zval) == opencv_mat_ce){
        src1_mat_object = Z_PHP_MAT_OBJ_P(src1_zval);
    }else if(Z_OBJCE_P(src1_zval) == opencv_scalar_ce){
        src1_scalar_object = Z_PHP_SCALAR_OBJ_P(src1_zval);
    }else{
        opencv_throw_exception("src1 parameter must be Mat or Scalar object.");
        RETURN_NULL();
    }

    if(Z_OBJCE_P(src2_zval) == opencv_mat_ce){
        src2_mat_object = Z_PHP_MAT_OBJ_P(src2_zval);
        if(Z_OBJCE_P(src1_zval) == opencv_mat_ce){
            flag = 3;
        }else{
            flag = 1;
        }
    }else if(Z_OBJCE_P(src2_zval) == opencv_scalar_ce){
        src2_scalar_object = Z_PHP_SCALAR_OBJ_P(src2_zval);
        if(Z_OBJCE_P(src1_zval) == opencv_mat_ce){
            flag = 2;
        }
    }else{
        opencv_throw_exception("src2 parameter must be Mat or Scalar object.");
        RETURN_NULL();
    }

    zval *dst_real_zval = Z_REFVAL_P(dst_zval);

    if(flag == 0){ //both scalar
        if(Z_TYPE_P(dst_real_zval) == IS_OBJECT && Z_OBJCE_P(dst_real_zval)==opencv_scalar_ce){
            dst_scalar_object = Z_PHP_SCALAR_OBJ_P(dst_real_zval);
        } else{
            zval_ptr_dtor(dst_real_zval);
            zval instance;
            Scalar dst;
            object_init_ex(&instance,opencv_scalar_ce);
            ZVAL_COPY_VALUE(dst_real_zval, &instance);
            dst_scalar_object = Z_PHP_SCALAR_OBJ_P(dst_real_zval);
            dst_scalar_object->scalar = new Scalar(dst);
        }

        absdiff(*src1_scalar_object->scalar,*src2_scalar_object->scalar, *dst_scalar_object->scalar);
        opencv_scalar_update_property_by_c_scalar(dst_real_zval, dst_scalar_object->scalar);
    }else{
        if(Z_TYPE_P(dst_real_zval) == IS_OBJECT && Z_OBJCE_P(dst_real_zval)==opencv_mat_ce){
            dst_mat_object = Z_PHP_MAT_OBJ_P(dst_real_zval);
        } else{
            zval_ptr_dtor(dst_real_zval);
            zval instance;
            Mat dst;
            object_init_ex(&instance,opencv_mat_ce);
            ZVAL_COPY_VALUE(dst_real_zval, &instance);

            dst_mat_object = Z_PHP_MAT_OBJ_P(dst_real_zval);
            dst_mat_object->mat = new Mat(dst);
        }
        switch (flag){
            case 1:
                absdiff(*src1_scalar_object->scalar,*src2_mat_object->mat, *dst_mat_object->mat);
                opencv_mat_update_property_by_c_mat(dst_real_zval, dst_mat_object->mat);
                break;
            case 2:
                absdiff(*src1_mat_object->mat,*src2_scalar_object->scalar, *dst_mat_object->mat);
                opencv_mat_update_property_by_c_mat(dst_real_zval, dst_mat_object->mat);
                break;
            case 3:
                absdiff(*src1_mat_object->mat,*src2_mat_object->mat, *dst_mat_object->mat);
                opencv_mat_update_property_by_c_mat(dst_real_zval, dst_mat_object->mat);
                break;
            default:
                opencv_throw_exception("absdiff function error.");
                RETURN_NULL();
                break;
        }
    }
    RETURN_NULL();
}

/**
 * //todo mask and dtype params
 * CV\add
 * @param execute_data
 * @param return_value
 */
PHP_FUNCTION(opencv_add){
    zval *src1_zval, *src2_zval, *dst_zval;
//    zval *mask_zval;
//    long dtype = -1;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "zzz",
                              &src1_zval,
                              &src2_zval,
                              &dst_zval) == FAILURE) {
        RETURN_NULL();
    }
    opencv_mat_object *src1_mat_object = NULL, *src2_mat_object = NULL, *dst_mat_object = NULL;
    opencv_scalar_object *src1_scalar_object = NULL, *src2_scalar_object = NULL, *dst_scalar_object = NULL;

    if(Z_TYPE_P(src1_zval) == IS_OBJECT && (Z_OBJCE_P(src1_zval) == opencv_mat_ce || Z_OBJCE_P(src1_zval) == opencv_scalar_ce)){
        if(Z_OBJCE_P(src1_zval) == opencv_mat_ce){
            src1_mat_object = Z_PHP_MAT_OBJ_P(src1_zval);
        }else{
            src1_scalar_object = Z_PHP_SCALAR_OBJ_P(src1_zval);
        }
    } else{
        opencv_throw_exception("src1 parameter must be Mat or Scalar object.");
    }

    if(Z_TYPE_P(src2_zval) == IS_OBJECT && (Z_OBJCE_P(src2_zval) == opencv_mat_ce || Z_OBJCE_P(src2_zval) == opencv_scalar_ce)){
        if(Z_OBJCE_P(src2_zval) == opencv_mat_ce){
            src2_mat_object = Z_PHP_MAT_OBJ_P(src2_zval);
        }else{
            src2_scalar_object = Z_PHP_SCALAR_OBJ_P(src2_zval);
        }
    } else{
        opencv_throw_exception("src2 parameter must be Mat or Scalar object.");//throw exception
    }

    zval *dst_real_zval = Z_REFVAL_P(dst_zval);

    //dst is Mat object
    if(src1_mat_object != NULL && src2_mat_object != NULL){
        if(Z_TYPE_P(dst_real_zval) == IS_OBJECT && Z_OBJCE_P(dst_real_zval)==opencv_mat_ce){
            dst_mat_object = Z_PHP_MAT_OBJ_P(dst_real_zval);
        } else{
            zval_ptr_dtor(dst_real_zval);
            zval instance;
            Mat dst;
            object_init_ex(&instance,opencv_mat_ce);
            ZVAL_COPY_VALUE(dst_real_zval, &instance);
            dst_mat_object = Z_PHP_MAT_OBJ_P(dst_real_zval);
            dst_mat_object->mat = new Mat(dst);
        }
        add(*src1_mat_object->mat,*src2_mat_object->mat, *dst_mat_object->mat);
        opencv_mat_update_property_by_c_mat(dst_real_zval, dst_mat_object->mat);

    }else if(src1_mat_object != NULL && src2_mat_object == NULL){
        if(Z_TYPE_P(dst_real_zval) == IS_OBJECT && Z_OBJCE_P(dst_real_zval)==opencv_mat_ce){
            dst_mat_object = Z_PHP_MAT_OBJ_P(dst_real_zval);
        } else{
            zval_ptr_dtor(dst_real_zval);
            zval instance;
            Mat dst;
            object_init_ex(&instance,opencv_mat_ce);
            ZVAL_COPY_VALUE(dst_real_zval, &instance);
            dst_mat_object = Z_PHP_MAT_OBJ_P(dst_real_zval);
            dst_mat_object->mat = new Mat(dst);
        }
        add(*src1_mat_object->mat,*src2_scalar_object->scalar,*dst_mat_object->mat);
        opencv_mat_update_property_by_c_mat(dst_real_zval, dst_mat_object->mat);
    }else if(src1_mat_object==NULL && src2_mat_object != NULL){
        if(Z_TYPE_P(dst_real_zval) == IS_OBJECT && Z_OBJCE_P(dst_real_zval)==opencv_mat_ce){
            dst_mat_object = Z_PHP_MAT_OBJ_P(dst_real_zval);
        } else{
            zval_ptr_dtor(dst_real_zval);
            zval instance;
            Mat dst;
            object_init_ex(&instance,opencv_mat_ce);
            ZVAL_COPY_VALUE(dst_real_zval, &instance);
            dst_mat_object = Z_PHP_MAT_OBJ_P(dst_real_zval);
            dst_mat_object->mat = new Mat(dst);
        }
        add(*src1_scalar_object->scalar,*src2_mat_object->mat,*dst_mat_object->mat);
        opencv_mat_update_property_by_c_mat(dst_real_zval, dst_mat_object->mat);
    }else{
        if(Z_TYPE_P(dst_real_zval) == IS_OBJECT && Z_OBJCE_P(dst_real_zval)==opencv_scalar_ce){
            dst_scalar_object = Z_PHP_SCALAR_OBJ_P(dst_real_zval);
        } else{
            zval instance;
            Scalar dst;
            object_init_ex(&instance,opencv_scalar_ce);
            ZVAL_COPY_VALUE(dst_real_zval, &instance);
            dst_scalar_object = Z_PHP_SCALAR_OBJ_P(dst_real_zval);
            dst_scalar_object->scalar = new Scalar(dst);
        }
        add(*src1_scalar_object->scalar,*src2_scalar_object->scalar,*dst_scalar_object->scalar);
        opencv_scalar_update_property_by_c_scalar(dst_real_zval, dst_scalar_object->scalar);
    }

    RETURN_NULL();

}


/**
 * CV\log
 * @param execute_data
 * @param return_value
 */
PHP_FUNCTION(opencv_log){
    zval *src_zval, *dst_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "Oz",
                              &src_zval, opencv_mat_ce,
                              &dst_zval) == FAILURE) {
        RETURN_NULL();
    }

    opencv_mat_object *src_object = Z_PHP_MAT_OBJ_P(src_zval);
    zval *dst_real_zval = Z_REFVAL_P(dst_zval);
    opencv_mat_object *dst_object;
    if(Z_TYPE_P(dst_real_zval) == IS_OBJECT && Z_OBJCE_P(dst_real_zval)==opencv_mat_ce){
        dst_object = Z_PHP_MAT_OBJ_P(dst_real_zval);
    } else{
        zval_ptr_dtor(dst_real_zval);
        zval instance;
        Mat dst;
        object_init_ex(&instance,opencv_mat_ce);
        ZVAL_COPY_VALUE(dst_real_zval, &instance);
        dst_object = Z_PHP_MAT_OBJ_P(dst_real_zval);
        dst_object->mat = new Mat(dst);
    }

    log(*src_object->mat, *dst_object->mat);
    opencv_mat_update_property_by_c_mat(dst_real_zval, dst_object->mat);
    RETURN_NULL();

}

/**
 * //todo mask parameter
 * CV\nromalize
 * @param execute_data
 * @param return_value
 */
PHP_FUNCTION(opencv_normalize){
    zval *src_zval, *dst_zval;
    double alpha = 1, beta = 0;
    long norm_type = NORM_L2, dtype = -1;
    zval *mask_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "Oz|ddll",
                              &src_zval, opencv_mat_ce, &dst_zval,
                              &alpha, &beta, &norm_type, &dtype) == FAILURE) {
        RETURN_NULL();
    }
    opencv_mat_object *src_object = Z_PHP_MAT_OBJ_P(src_zval);
    zval *dst_real_zval = Z_REFVAL_P(dst_zval);
    opencv_mat_object *dst_object;
    if(Z_TYPE_P(dst_real_zval) == IS_OBJECT && Z_OBJCE_P(dst_real_zval)==opencv_mat_ce){
        dst_object = Z_PHP_MAT_OBJ_P(dst_real_zval);
    } else{
        zval_ptr_dtor(dst_real_zval);
        zval instance;
        Mat dst;
        object_init_ex(&instance,opencv_mat_ce);
        ZVAL_COPY_VALUE(dst_real_zval, &instance);
        dst_object = Z_PHP_MAT_OBJ_P(dst_real_zval);
        dst_object->mat = new Mat(dst);
    }
    normalize(*src_object->mat, *dst_object->mat, alpha, beta, (int)norm_type, (int)dtype);
    opencv_mat_update_property_by_c_mat(dst_real_zval, dst_object->mat);
    RETURN_NULL();

}


/**
 *
 * CV\LUT
 * @param execute_data
 * @param return_value
 */
PHP_FUNCTION(opencv_lut){
    zval *src_zval, *lut_zval, *dst_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "OOz",
                              &src_zval, opencv_mat_ce,
                              &lut_zval, opencv_mat_ce,
                              &dst_zval) == FAILURE) {
        RETURN_NULL();
    }
    opencv_mat_object *src_object = Z_PHP_MAT_OBJ_P(src_zval);
    opencv_mat_object *lut_object = Z_PHP_MAT_OBJ_P(lut_zval);
    zval *dst_real_zval = Z_REFVAL_P(dst_zval);
    opencv_mat_object *dst_object;
    if(Z_TYPE_P(dst_real_zval) == IS_OBJECT && Z_OBJCE_P(dst_real_zval)==opencv_mat_ce){
        dst_object = Z_PHP_MAT_OBJ_P(dst_real_zval);
    } else{
        zval_ptr_dtor(dst_real_zval);
        zval instance;
        Mat dst;
        object_init_ex(&instance,opencv_mat_ce);
        ZVAL_COPY_VALUE(dst_real_zval, &instance);
        dst_object = Z_PHP_MAT_OBJ_P(dst_real_zval);
        dst_object->mat = new Mat(dst);
    }
    LUT(*src_object->mat, *lut_object->mat, *dst_object->mat);
    opencv_mat_update_property_by_c_mat(dst_real_zval, dst_object->mat);
    RETURN_NULL();

}
