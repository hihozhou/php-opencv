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
#include "opencv_mat.h"
#include "opencv_type.h"
#include "../../../opencv_exception.h"

zend_object_handlers opencv_mat_object_handlers;

zend_class_entry *opencv_mat_ce;

/**
 * @param type
 * @return
 */
zend_object* opencv_mat_create_handler(zend_class_entry *type)
{
    int size = sizeof(opencv_mat_object)+zend_object_properties_size(type);
    opencv_mat_object *obj = (opencv_mat_object *)ecalloc(1,size);
    memset(obj, 0, size);
    zend_object_std_init(&obj->std, type);
    object_properties_init(&obj->std, type);
    obj->std.ce = type;
    obj->std.handlers = &opencv_mat_object_handlers;
    return &obj->std;
}


void opencv_mat_free_obj(zend_object *object)
{
    opencv_mat_object *obj;
    obj = get_mat_obj(object);
    delete obj->mat;
    zend_object_std_dtor(object);
}

void opencv_mat_update_property_by_c_mat(zval *z,Mat *mat){
    zend_update_property_long(opencv_mat_ce, z, "rows", sizeof("rows")-1, mat->rows);
    zend_update_property_long(opencv_mat_ce, z, "cols", sizeof("cols")-1, mat->cols);
    zend_update_property_long(opencv_mat_ce, z, "dims", sizeof("dims")-1, mat->dims);
    zend_update_property_long(opencv_mat_ce, z, "type", sizeof("type")-1, mat->type());
    //zend_update_property_long(opencv_mat_ce, z, "depth", sizeof("depth")-1, mat->depth());

    if (mat->dims > 2) {
        zval shape_zval;
        array_init(&shape_zval);
        for(int i = 0; i < mat->dims; i++)
        {
            add_next_index_long(&shape_zval, mat->size.p[i]);
        }
        zend_update_property(opencv_mat_ce, z, "shape", sizeof("shape")-1, &shape_zval);
    }
}

void opencv_mat_at(Mat *mat, int *idx, long channel, zval *value_zval, long *return_long_val, double *return_double_val) {
    uchar *return_uchar_val;
    schar *return_schar_val;
    ushort *return_ushort_val;
    short *return_short_val;
    int *return_int_val;
    float *return_float_val;

    switch(mat->type()) {
        //CV_8U
        case CV_8UC1: return_uchar_val = &mat->at<uchar>(idx); break;
        case CV_8UC2: return_uchar_val = &mat->at<Vec2b>(idx)[channel]; break;
        case CV_8UC3: return_uchar_val = &mat->at<Vec3b>(idx)[channel]; break;
        case CV_8UC4: return_uchar_val = &mat->at<Vec4b>(idx)[channel]; break;

        //CV_8S
        case CV_8SC1: return_schar_val = &mat->at<schar>(idx); break;
        case CV_8SC2: return_schar_val = &mat->at<Vec<schar, 2>>(idx)[channel]; break;
        case CV_8SC3: return_schar_val = &mat->at<Vec<schar, 3>>(idx)[channel]; break;
        case CV_8SC4: return_schar_val = &mat->at<Vec<schar, 4>>(idx)[channel]; break;

        //CV_16U
        case CV_16UC1: return_ushort_val = &mat->at<ushort>(idx); break;
        case CV_16UC2: return_ushort_val = &mat->at<Vec2w>(idx)[channel]; break;
        case CV_16UC3: return_ushort_val = &mat->at<Vec3w>(idx)[channel]; break;
        case CV_16UC4: return_ushort_val = &mat->at<Vec4w>(idx)[channel]; break;

        //CV_16S
        case CV_16SC1: return_short_val = &mat->at<short>(idx); break;
        case CV_16SC2: return_short_val = &mat->at<Vec2s>(idx)[channel]; break;
        case CV_16SC3: return_short_val = &mat->at<Vec3s>(idx)[channel]; break;
        case CV_16SC4: return_short_val = &mat->at<Vec4s>(idx)[channel]; break;

        //CV_32S
        case CV_32SC1: return_int_val = &mat->at<int>(idx); break;
        case CV_32SC2: return_int_val = &mat->at<Vec2i>(idx)[channel]; break;
        case CV_32SC3: return_int_val = &mat->at<Vec3i>(idx)[channel]; break;
        case CV_32SC4: return_int_val = &mat->at<Vec4i>(idx)[channel]; break;

        //CV_32F
        case CV_32FC1: return_float_val = &mat->at<float>(idx); break;
        case CV_32FC2: return_float_val = &mat->at<Vec2f>(idx)[channel]; break;
        case CV_32FC3: return_float_val = &mat->at<Vec3f>(idx)[channel]; break;
        case CV_32FC4: return_float_val = &mat->at<Vec4f>(idx)[channel]; break;

        //CV_64F
        case CV_64FC1: return_double_val = &mat->at<double>(idx); break;
        case CV_64FC2: return_double_val = &mat->at<Vec2d>(idx)[channel]; break;
        case CV_64FC3: return_double_val = &mat->at<Vec3d>(idx)[channel]; break;
        case CV_64FC4: return_double_val = &mat->at<Vec4d>(idx)[channel]; break;

        default: opencv_throw_exception("Wrong Mat type"); break;
    }

    //get px value
    switch(mat->depth()){
        case CV_8U: *return_long_val = *return_uchar_val; break;
        case CV_8S: *return_long_val = *return_schar_val; break;
        case CV_16U: *return_long_val = *return_ushort_val; break;
        case CV_16S: *return_long_val = *return_short_val; break;
        case CV_32S: *return_long_val = *return_int_val; break;
        case CV_32F: *return_double_val = *return_float_val; break;
        case CV_64F: break;

        default: opencv_throw_exception("Wrong Mat type"); break;
    }

    //set px value
    if (value_zval != NULL) {
        switch(mat->depth()){
            case CV_32F:
            case CV_64F: convert_to_double(value_zval); break;
            default: convert_to_long(value_zval); break;
        }

        zend_long value = Z_LVAL_P(value_zval);
        switch(mat->depth()){
            case CV_8U: *return_uchar_val = saturate_cast<uchar>(Z_LVAL_P(value_zval)); break;
            case CV_8S: *return_schar_val = saturate_cast<schar>(Z_LVAL_P(value_zval)); break;
            case CV_16U: *return_ushort_val = saturate_cast<ushort>(Z_LVAL_P(value_zval)); break;
            case CV_16S: *return_short_val = saturate_cast<short>(Z_LVAL_P(value_zval)); break;
            case CV_32S: *return_int_val = saturate_cast<int>(Z_LVAL_P(value_zval)); break;
            case CV_32F: *return_float_val = saturate_cast<float>(Z_DVAL_P(value_zval)); break;
            case CV_64F: *return_double_val = saturate_cast<double>(Z_DVAL_P(value_zval)); break;

            default: opencv_throw_exception("Wrong Mat type"); break;
        }
    }
}

/**
 * Mat __construct
 * @param execute_data
 * @param return_value
 */
PHP_METHOD(opencv_mat, __construct)
{
    long rows, cols, type;
    zval *scalar_zval = NULL;
    Scalar scalar;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "lll|O", &rows, &cols, &type, &scalar_zval,opencv_scalar_ce) == FAILURE) {
        RETURN_NULL();
    }

    opencv_mat_object *obj = Z_PHP_MAT_OBJ_P(getThis());
    if(scalar_zval != NULL){
        opencv_scalar_object *scalar_object = Z_PHP_SCALAR_OBJ_P(scalar_zval);
        scalar = *(scalar_object->scalar);
    }else{
        scalar=Scalar(0);
    }
    Mat M((int)rows, (int)cols, (int)type);
//    obj->mat = new Mat(M);
    obj->mat = new Mat((int)rows, (int)cols, (int)type, scalar);
    //obj->mat = new Mat((int)rows, (int)cols, (int)type); //TODO Why Mat array not correct
    opencv_mat_update_property_by_c_mat(getThis(), obj->mat);
}

/**
 * print Mat data
 * @param execute_data
 * @param return_value
 */
PHP_METHOD(opencv_mat, print)
{
    long type = Formatter::FMT_DEFAULT;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "|l", &type) == FAILURE) {
        RETURN_NULL();
    }
    opencv_mat_object *obj = Z_PHP_MAT_OBJ_P(getThis());
    std::cout << format(*(obj->mat),int(type)) << std::endl;
    RETURN_NULL();
}


PHP_METHOD(opencv_mat, type)
{
    opencv_mat_object *obj = Z_PHP_MAT_OBJ_P(getThis());
    RETURN_LONG(obj->mat->type());
}

PHP_METHOD(opencv_mat, depth)
{
    opencv_mat_object *obj = Z_PHP_MAT_OBJ_P(getThis());
    RETURN_LONG(obj->mat->depth());
}

PHP_METHOD(opencv_mat, channels)
{
    opencv_mat_object *obj = Z_PHP_MAT_OBJ_P(getThis());
    RETURN_LONG(obj->mat->channels());
}

PHP_METHOD(opencv_mat, total)
{
    opencv_mat_object *obj = Z_PHP_MAT_OBJ_P(getThis());
    RETURN_LONG(obj->mat->total());
}

PHP_METHOD(opencv_mat, empty)
{
    opencv_mat_object *obj = Z_PHP_MAT_OBJ_P(getThis());
    RETURN_LONG(obj->mat->empty());
}

PHP_METHOD(opencv_mat, ones)
{
    long rows, cols, flags;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "lll", &rows, &cols, &flags) == FAILURE) {
        RETURN_NULL();
    }
    zval instance;
    object_init_ex(&instance, opencv_mat_ce);
    opencv_mat_object *obj = Z_PHP_MAT_OBJ_P(&instance);

    Mat im = Mat::ones((int)rows, (int)cols, (int)flags);

    obj->mat=new Mat(im);
    //update php Mat object property
    opencv_mat_update_property_by_c_mat(&instance, obj->mat);

    RETURN_ZVAL(&instance,0,0); //return php Mat object
}

PHP_METHOD(opencv_mat, zeros)
{
    long rows, cols, flags;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "lll", &rows, &cols, &flags) == FAILURE) {
        RETURN_NULL();
    }
    zval instance;
    object_init_ex(&instance, opencv_mat_ce);
    opencv_mat_object *obj = Z_PHP_MAT_OBJ_P(&instance);

    Mat im = Mat::zeros((int)rows, (int)cols, (int)flags);

    obj->mat=new Mat(im);
    //update php Mat object property
    opencv_mat_update_property_by_c_mat(&instance, obj->mat);

    RETURN_ZVAL(&instance,0,0); //return php Mat object
}

PHP_METHOD(opencv_mat, zeros_by_size)
{
    zval *size_zval;
    long flags;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "Ol", &size_zval, opencv_size_ce, &flags) == FAILURE) {
        RETURN_NULL();
    }

    opencv_size_object *size_object = Z_PHP_SIZE_OBJ_P(size_zval);
    zval instance;
    object_init_ex(&instance, opencv_mat_ce);
    opencv_mat_object *obj = Z_PHP_MAT_OBJ_P(&instance);

    Mat im = Mat::zeros(*size_object->size, (int)flags);

    obj->mat=new Mat(im);
    opencv_mat_update_property_by_c_mat(&instance, obj->mat);

    RETURN_ZVAL(&instance,0,0);
}


/**
 * Mat->clone()
 * @param execute_data
 * @param return_value
 */
PHP_METHOD(opencv_mat, clone)
{
    zval instance;
    object_init_ex(&instance, opencv_mat_ce);
    opencv_mat_object *new_obj = Z_PHP_MAT_OBJ_P(&instance);
    opencv_mat_object *old_obj = Z_PHP_MAT_OBJ_P(getThis());
    Mat new_mat = old_obj->mat->clone();

    new_obj->mat = new Mat(new_mat);
    //update php Mat object property
    opencv_mat_update_property_by_c_mat(&instance, new_obj->mat);

    RETURN_ZVAL(&instance,0,0); //return php Mat object
}

/**
 * Mat->isContinuous
 * @param execute_data
 * @param return_value
 */
PHP_METHOD(opencv_mat, is_continuous)
{
    opencv_mat_object *obj = Z_PHP_MAT_OBJ_P(getThis());
    bool isContinuous = obj->mat->isContinuous();
    RETURN_BOOL(isContinuous);
}

/**
 * Mat->isSubmatrix
 * @param execute_data
 * @param return_value
 */
PHP_METHOD(opencv_mat, is_submatrix)
{
    opencv_mat_object *obj = Z_PHP_MAT_OBJ_P(getThis());
    bool isSubmatrix = obj->mat->isSubmatrix();
    RETURN_BOOL(isSubmatrix);
}

/**
 * Mat->row(y)
 * @param execute_data
 * @param return_value
 */
PHP_METHOD(opencv_mat, row)
{
    long y;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "l", &y) == FAILURE) {
        RETURN_NULL();
    }
    zval instance;
    object_init_ex(&instance, opencv_mat_ce);
    opencv_mat_object *new_obj = Z_PHP_MAT_OBJ_P(&instance);

    opencv_mat_object *obj = Z_PHP_MAT_OBJ_P(getThis());
    Mat im = obj->mat->row(y);
    new_obj->mat=new Mat(im);
    opencv_mat_update_property_by_c_mat(&instance, new_obj->mat);

    RETURN_ZVAL(&instance,0,0); //return php Mat object
}

/**
 * Mat->col(x)
 * @param execute_data
 * @param return_value
 */
PHP_METHOD(opencv_mat, col)
{
    long x;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "l", &x) == FAILURE) {
        RETURN_NULL();
    }
    zval instance;
    object_init_ex(&instance, opencv_mat_ce);
    opencv_mat_object *new_obj = Z_PHP_MAT_OBJ_P(&instance);

    opencv_mat_object *obj = Z_PHP_MAT_OBJ_P(getThis());
    Mat im = obj->mat->col(x);
    new_obj->mat=new Mat(im);

    opencv_mat_update_property_by_c_mat(&instance, new_obj->mat);

    RETURN_ZVAL(&instance,0,0); //return php Mat object
}

/**
 * Mat->getImageROI(x)
 * @param execute_data
 * @param return_value
 */
PHP_METHOD(opencv_mat, get_image_roi)
{
    zval *rect_zval;
    zval instance;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "O", &rect_zval,opencv_rect_ce) == FAILURE) {
        RETURN_NULL();
    }
    opencv_rect_object *rect_object = Z_PHP_RECT_OBJ_P(rect_zval);

    object_init_ex(&instance, opencv_mat_ce);
    opencv_mat_object *new_obj = Z_PHP_MAT_OBJ_P(&instance);

    opencv_mat_object *obj = Z_PHP_MAT_OBJ_P(getThis());
    try {
        Mat roi = (*obj->mat)(*rect_object->rect);
        new_obj->mat = new Mat(roi);
    }catch (Exception exception){
        const char* err_msg = exception.what();
        opencv_throw_exception(err_msg);//throw exception
        RETURN_NULL();
    }

    opencv_mat_update_property_by_c_mat(&instance, new_obj->mat);

    RETURN_ZVAL(&instance,0,0); //return php Mat object
}

ZEND_BEGIN_ARG_INFO_EX(opencv_mat_copy_to_arginfo, 0, 0, 2)
                ZEND_ARG_INFO(1, m)
                ZEND_ARG_INFO(0, mask)
ZEND_END_ARG_INFO()

/**
 * Mat->copyTo(Mat $mat,Mat $mask=NULL)
 * @param execute_data
 * @param return_value
 */
PHP_METHOD(opencv_mat, copy_to)
{
    zval *m_zval, *mask_zval = NULL;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "z|O", &m_zval, opencv_mat_ce, &mask_zval, opencv_mat_ce) == FAILURE) {
        RETURN_NULL();
    }

    zval *m_real_zval = Z_REFVAL_P(m_zval);
    opencv_mat_object *m_object;
    if(Z_TYPE_P(m_real_zval) == IS_OBJECT && Z_OBJCE_P(m_real_zval)==opencv_mat_ce){
        m_object = Z_PHP_MAT_OBJ_P(m_real_zval);
    } else if(Z_TYPE_P(m_real_zval) == IS_NULL){
        zval_ptr_dtor(m_real_zval);
        zval instance;
        Mat dst;
        object_init_ex(&instance,opencv_mat_ce);
        ZVAL_COPY_VALUE(m_real_zval, &instance);
        m_object = Z_PHP_MAT_OBJ_P(m_real_zval);
        m_object->mat = new Mat(dst);
    }else{
        opencv_throw_exception("copy expect param is Mat object or null.");
        RETURN_NULL();
    }
    opencv_mat_object *this_object = Z_PHP_MAT_OBJ_P(getThis());
    try {
        if(mask_zval != NULL){
            opencv_mat_object *mask_object = Z_PHP_MAT_OBJ_P(mask_zval);
            this_object->mat->copyTo(*m_object->mat, *mask_object->mat);
        }else{
            this_object->mat->copyTo(*m_object->mat);
        }
        opencv_mat_update_property_by_c_mat(m_real_zval, m_object->mat);
    }catch (Exception exception){
        const char* err_msg = exception.what();
        opencv_throw_exception(err_msg);//throw exception
    }


    RETURN_NULL();

}

/**
 * CV\Mat->at
 * @param execute_data
 * @param return_value
 */
PHP_METHOD(opencv_mat, at)
{
    long row, col, channel;
    zval *value_zval = NULL;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "lll|z", &row, &col, &channel, &value_zval) == FAILURE) {
        RETURN_NULL();
    }

    opencv_mat_object *this_object = Z_PHP_MAT_OBJ_P(getThis());
    zval *idx_zval;
    int *idx;
    long return_long_val;
    double return_double_val;

    idx = new int(2);
    idx[0] = row;
    idx[1] = col;

    opencv_mat_at(this_object->mat, idx, channel, value_zval, &return_long_val, &return_double_val);

    switch (this_object->mat->depth()){
        case CV_32F:
        case CV_64F:
            RETURN_DOUBLE(return_double_val);
        default:
            RETURN_LONG(return_long_val);
    }
}

/**
 * CV\Mat->atIdx
 * @param execute_data
 * @param return_value
 */
PHP_METHOD(opencv_mat, atIdx) // multi dimensions support
{
    long channel = 1;
    zval *value_zval = NULL;
    zval *idx_zval;
    int *idx = nullptr;

    if (zend_parse_parameters_ex(ZEND_PARSE_PARAMS_QUIET, ZEND_NUM_ARGS(), "a|lz", &idx_zval, &channel, &value_zval) == FAILURE) {
        RETURN_NULL();
    }

    opencv_mat_object *this_object = Z_PHP_MAT_OBJ_P(getThis());

    unsigned long idx_count = zend_hash_num_elements(Z_ARRVAL_P(idx_zval));

    if (idx_count == 0) {
        opencv_throw_exception("array lenght must be >=1");
        RETURN_NULL();
    } else if (idx_count != this_object->mat->dims) {
        opencv_throw_exception("array lenght must be = dims");
        RETURN_NULL();
    }

    idx = new int(idx_count);
    zval *array_val_zval;
    zend_ulong _h;

    ZEND_HASH_FOREACH_NUM_KEY_VAL(Z_ARRVAL_P(idx_zval),_h,array_val_zval){
                again:
                if(Z_TYPE_P(array_val_zval) == IS_LONG){
                    //idx.push_back((int)zval_get_long(array_val_zval));
                    idx[_h] = (int)zval_get_long(array_val_zval);
                }else if(Z_TYPE_P(array_val_zval) == IS_REFERENCE){
                    array_val_zval = Z_REFVAL_P(array_val_zval);
                    goto again;
                } else {
                    opencv_throw_exception("array value just number.");
                    RETURN_NULL();
                }
    }ZEND_HASH_FOREACH_END();

    long return_long_val;
    double return_double_val;

    opencv_mat_at(this_object->mat, idx, channel, value_zval, &return_long_val, &return_double_val);


    switch (this_object->mat->depth()){
        case CV_32F:
        case CV_64F:
            RETURN_DOUBLE(return_double_val);
        default:
            RETURN_LONG(return_long_val);
    }
}

ZEND_BEGIN_ARG_INFO_EX(opencv_mat_convert_to_arginfo, 0, 0, 4)
                ZEND_ARG_INFO(1, dst)
                ZEND_ARG_INFO(0, rtype)
                ZEND_ARG_INFO(0, alpha)
                ZEND_ARG_INFO(0, beta)
ZEND_END_ARG_INFO()

/**
 * CV\Mat->convertTo
 * @param execute_data
 * @param return_value
 */
PHP_METHOD(opencv_mat, convert_to){
    zval *dst_zval;
    long rtype;
    double alpha = 1, beta = 0;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "zl|dd", &dst_zval, &rtype, &alpha, &beta) == FAILURE) {
        RETURN_NULL();
    }
    zval *dst_real_zval = Z_REFVAL_P(dst_zval);
    opencv_mat_object *dst_object, *this_object;
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
    this_object = Z_PHP_MAT_OBJ_P(getThis());
    this_object->mat->convertTo(*dst_object->mat, (int)rtype, alpha, beta);
    opencv_mat_update_property_by_c_mat(dst_real_zval,dst_object->mat);
    RETURN_NULL();
}

PHP_METHOD(opencv_mat, size)
{
    zval instance;
    object_init_ex(&instance, opencv_size_ce);
    opencv_size_object *size_object = Z_PHP_SIZE_OBJ_P(&instance);

    opencv_mat_object *obj = Z_PHP_MAT_OBJ_P(getThis());
    try {
        Size size = obj->mat->size();
        size_object->size = new Size(size);
    }catch (Exception e){
        opencv_throw_exception(e.what());
        RETURN_NULL();
    }
    opencv_size_update_property_by_c_size(&instance, size_object->size);
    RETURN_ZVAL(&instance,0,0);
}

/**
 * Mat->plus()
 * @param execute_data
 * @param return_value
 */
PHP_METHOD(opencv_mat, plus)
{
    zval instance;
    double number=1;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "d", &number) == FAILURE) {
        RETURN_NULL();
    }

    object_init_ex(&instance, opencv_mat_ce);

    opencv_mat_object *new_obj = Z_PHP_MAT_OBJ_P(&instance);
    opencv_mat_object *obj = Z_PHP_MAT_OBJ_P(getThis());
    new_obj->mat=new Mat(*(obj->mat)*number);

    opencv_mat_update_property_by_c_mat(&instance, new_obj->mat);

    RETURN_ZVAL(&instance,0,0); //return php Mat object
}

/**
 * Mat->divide()
 * @param execute_data
 * @param return_value
 */
PHP_METHOD(opencv_mat, divide)
{
    zval instance;
    double number=1;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "d", &number) == FAILURE) {
        RETURN_NULL();
    }

    object_init_ex(&instance, opencv_mat_ce);

    opencv_mat_object *new_obj = Z_PHP_MAT_OBJ_P(&instance);
    opencv_mat_object *obj = Z_PHP_MAT_OBJ_P(getThis());
    new_obj->mat=new Mat(*(obj->mat)/number);

    opencv_mat_update_property_by_c_mat(&instance, new_obj->mat);

    RETURN_ZVAL(&instance,0,0); //return php Mat object
}



/**
 * //todo mask
 * Mat->setTo(Scalar $value)
 * @param execute_data
 * @param return_value
 */
PHP_METHOD(opencv_mat, set_to)
{
    zval *value_zval;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "O", &value_zval, opencv_scalar_ce) == FAILURE) {
        RETURN_NULL();
    }

    opencv_mat_object *this_obj = Z_PHP_MAT_OBJ_P(getThis());
    opencv_scalar_object *value_obj = Z_PHP_SCALAR_OBJ_P(value_zval);
    this_obj->mat->setTo(*value_obj->scalar);

    RETURN_NULL();

}

/**
 * CV\Mat::add()
 * @param execute_data
 * @param return_value
 */
PHP_METHOD(opencv_mat, add)
{
    zval *value1_zval, *value2_zval;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "OO",
                              &value1_zval, opencv_mat_ce,
                              &value2_zval, opencv_mat_ce
    ) == FAILURE) {
        RETURN_NULL();
    }

    opencv_mat_object *value1_obj = Z_PHP_MAT_OBJ_P(value1_zval);
    opencv_mat_object *value2_obj = Z_PHP_MAT_OBJ_P(value2_zval);
    zval instance;
    object_init_ex(&instance, opencv_mat_ce);
    opencv_mat_object *obj = Z_PHP_MAT_OBJ_P(&instance);

    Mat im = *value1_obj->mat + *value2_obj->mat;

    obj->mat=new Mat(im);
    //update php Mat object property
    opencv_mat_update_property_by_c_mat(&instance, obj->mat);

    RETURN_ZVAL(&instance,0,0); //return php Mat object
}

PHP_METHOD(opencv_mat, subtract)
{
    zval *value1_zval, *value2_zval;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "OO",
                              &value1_zval, opencv_mat_ce,
                              &value2_zval, opencv_mat_ce
    ) == FAILURE) {
        RETURN_NULL();
    }

    opencv_mat_object *value1_obj = Z_PHP_MAT_OBJ_P(value1_zval);
    opencv_mat_object *value2_obj = Z_PHP_MAT_OBJ_P(value2_zval);
    zval instance;
    object_init_ex(&instance, opencv_mat_ce);
    opencv_mat_object *obj = Z_PHP_MAT_OBJ_P(&instance);

    Mat im = *value1_obj->mat - *value2_obj->mat;

    obj->mat=new Mat(im);
    //update php Mat object property
    opencv_mat_update_property_by_c_mat(&instance, obj->mat);

    RETURN_ZVAL(&instance,0,0); //return php Mat object
}


/**
 * opencv_mat_methods[]
 */
const zend_function_entry opencv_mat_methods[] = {
        PHP_ME(opencv_mat, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
        PHP_ME(opencv_mat, type, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(opencv_mat, depth, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(opencv_mat, channels, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(opencv_mat, empty, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(opencv_mat, print, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(opencv_mat, size, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(opencv_mat, clone, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(opencv_mat, ones, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(opencv_mat, zeros, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_MALIAS(opencv_mat, zerosBySize ,zeros_by_size, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_MALIAS(opencv_mat, isContinuous ,is_continuous, NULL, ZEND_ACC_PUBLIC)
        PHP_MALIAS(opencv_mat, isSubmatrix ,is_submatrix, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(opencv_mat, row, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(opencv_mat, col, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(opencv_mat, at, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(opencv_mat, atIdx, NULL, ZEND_ACC_PUBLIC)
        PHP_MALIAS(opencv_mat, getImageROI ,get_image_roi, NULL, ZEND_ACC_PUBLIC)
        PHP_MALIAS(opencv_mat, copyTo ,copy_to, opencv_mat_copy_to_arginfo, ZEND_ACC_PUBLIC)
        PHP_MALIAS(opencv_mat, convertTo ,convert_to, opencv_mat_convert_to_arginfo, ZEND_ACC_PUBLIC)
        PHP_ME(opencv_mat, plus, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(opencv_mat, divide, NULL, ZEND_ACC_PUBLIC)
        PHP_MALIAS(opencv_mat, setTo ,set_to, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(opencv_mat, add , NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(opencv_mat, subtract , NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_FE_END
};
/* }}} */



/**
 * Mat Class write_property
 * @param object
 * @param member
 * @param value
 * @param cache_slot
 */
void opencv_mat_write_property(zval *object, zval *member, zval *value, void **cache_slot){

    zend_string *str = zval_get_string(member);
    char *memberName=ZSTR_VAL(str);
    opencv_mat_object *obj = Z_PHP_MAT_OBJ_P(object);

    if(strcmp(memberName, "cols") == 0 && obj->mat->cols!=(int)zval_get_long(value)){
        obj->mat->cols=(int)zval_get_long(value);
    }else if(strcmp(memberName, "rows") == 0 && obj->mat->rows!=(int)zval_get_long(value)){
        obj->mat->rows=(int)zval_get_long(value);
    }
    zend_string_release(str);//free zend_string not memberName(zend_string->val)
    std_object_handlers.write_property(object,member,value,cache_slot);

}

/**
 * Mat Init
 */
void opencv_mat_init(void){
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce,OPENCV_NS, "Mat", opencv_mat_methods);
    opencv_mat_ce = zend_register_internal_class(&ce);

    opencv_mat_ce->create_object = opencv_mat_create_handler;
    memcpy(&opencv_mat_object_handlers,
           zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    opencv_mat_object_handlers.clone_obj = NULL;
    opencv_mat_object_handlers.write_property = opencv_mat_write_property;

    zend_declare_property_null(opencv_mat_ce,"type",sizeof("type") - 1,ZEND_ACC_PRIVATE);//private Mat->type
    opencv_mat_object_handlers.free_obj = opencv_mat_free_obj;
    opencv_mat_object_handlers.offset = XtOffsetOf(opencv_mat_object, std);
}






