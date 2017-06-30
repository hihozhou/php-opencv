#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

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
zend_object* mat_create_handler(zend_class_entry *type)
{
    int size = sizeof(opencv_mat_object);
    opencv_mat_object *obj = (opencv_mat_object *)ecalloc(1,size);
    memset(obj, 0, sizeof(opencv_mat_object));
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
    zend_update_property_long(opencv_mat_ce, z, "type", sizeof("type")-1, mat->type());
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


PHP_METHOD(opencv_mat, zeros)
{
    long rows, cols, flags = IMREAD_COLOR;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "ll|l", &rows, &cols, &flags) == FAILURE) {
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
        new_obj->mat=new Mat(roi);
    }catch (Exception exception){
        const char* err_msg = exception.what();
        opencv_throw_exception(err_msg);//throw exception
        RETURN_NULL();
    }

    opencv_mat_update_property_by_c_mat(&instance, new_obj->mat);

    RETURN_ZVAL(&instance,0,0); //return php Mat object
}


/**
 * Mat->copyTo(Mat $mat,Mat $mask=NULL)
 * @param execute_data
 * @param return_value
 */
PHP_METHOD(opencv_mat, copy_to)
{
    zval *mat_zval, *mask_zval = NULL;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "O|O", &mat_zval, opencv_mat_ce, &mask_zval, opencv_mat_ce) == FAILURE) {
        RETURN_NULL();
    }
    opencv_mat_object *mat_object = Z_PHP_MAT_OBJ_P(mat_zval);
    opencv_mat_object *this_object = Z_PHP_MAT_OBJ_P(getThis());

    if(mask_zval != NULL){
        opencv_mat_object *mask_object = Z_PHP_MAT_OBJ_P(mask_zval);
        try {
            this_object->mat->copyTo(*mat_object->mat, *mask_object->mat);
        }catch (Exception exception){
            const char* err_msg = exception.what();
            opencv_throw_exception(err_msg);//throw exception
        }
    }else{
        try {
            this_object->mat->copyTo(*mat_object->mat);
        }catch (Exception exception){
            const char* err_msg = exception.what();
            opencv_throw_exception(err_msg);//throw exception
        }
    }
    RETURN_NULL();

}


/**
 * mat_methods[]
 */
const zend_function_entry mat_methods[] = {
        PHP_ME(opencv_mat, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
        PHP_ME(opencv_mat, type, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(opencv_mat, depth, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(opencv_mat, channels, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(opencv_mat, print, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(opencv_mat, zeros, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_MALIAS(opencv_mat, isContinuous ,is_continuous, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(opencv_mat, row, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(opencv_mat, col, NULL, ZEND_ACC_PUBLIC)
        PHP_MALIAS(opencv_mat, getImageROI ,get_image_roi, NULL, ZEND_ACC_PUBLIC)
        PHP_MALIAS(opencv_mat, copyTo ,copy_to, NULL, ZEND_ACC_PUBLIC)
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
    INIT_NS_CLASS_ENTRY(ce,OPENCV_NS, "Mat", mat_methods);
    opencv_mat_ce = zend_register_internal_class(&ce);

    opencv_mat_ce->create_object = mat_create_handler;
    memcpy(&opencv_mat_object_handlers,
           zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    opencv_mat_object_handlers.clone_obj = NULL;
    opencv_mat_object_handlers.write_property = opencv_mat_write_property;

    zend_declare_property_null(opencv_mat_ce,"type",sizeof("type") - 1,ZEND_ACC_PRIVATE);//private Mat->type
    opencv_mat_object_handlers.free_obj = opencv_mat_free_obj;
}






