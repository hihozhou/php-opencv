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
#include "opencv_facerec.h"

#ifdef HAVE_OPENCV_FACE

#include "../opencv_face.h"
#include "../core/opencv_mat.h"
#include "../../../opencv_exception.h"
#include <opencv2/core.hpp>
#include <opencv2/face.hpp>
using namespace cv::face;

#define Z_PHP_LBPH_FACE_RECOGNIZER_OBJ_P(zv)  get_lbph_face_recognizer_obj(Z_OBJ_P(zv))

typedef struct _opencv_lbph_face_recognizer_object{
    zend_object std;
    Ptr<LBPHFaceRecognizer> faceRecognizer;
}opencv_lbph_face_recognizer_object;


/**
 * @param obj
 * @return
 */
static inline opencv_lbph_face_recognizer_object* get_lbph_face_recognizer_obj(zend_object *obj) {
    return (opencv_lbph_face_recognizer_object*)((char*)(obj) - XtOffsetOf(opencv_lbph_face_recognizer_object, std));
}

zend_object_handlers opencv_lbph_face_recognizer_object_handlers;

zend_class_entry *opencv_lbph_face_recognizer_ce;

zend_class_entry *opencv_base_face_recognizer_ce;

PHP_METHOD(opencv_lbph_face_recognizer, create)
{
    zval instance;
    object_init_ex(&instance, opencv_lbph_face_recognizer_ce);
    opencv_lbph_face_recognizer_object *obj = Z_PHP_LBPH_FACE_RECOGNIZER_OBJ_P(&instance);
    obj->faceRecognizer = LBPHFaceRecognizer::create();
    RETURN_ZVAL(&instance,0,0);
}

PHP_METHOD(opencv_lbph_face_recognizer, train)
{
    zval *src_zval, *labels_zval;
    zend_ulong _h;
    zval *array_val_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "aa", &src_zval, &labels_zval) == FAILURE) {
        RETURN_NULL();
    }
    std::vector<Mat> src;
    std::vector<int> labels;
    //check
    opencv_lbph_face_recognizer_object *obj = Z_PHP_LBPH_FACE_RECOGNIZER_OBJ_P(getThis());
    unsigned long src_count = zend_hash_num_elements(Z_ARRVAL_P(src_zval));
    src.reserve(src_count);//指定长度
    opencv_mat_object *mat_obj;

    ZEND_HASH_FOREACH_NUM_KEY_VAL(Z_ARRVAL_P(src_zval),_h,array_val_zval){
                //check array_val_zval is Mat object
                again1:
                if(Z_TYPE_P(array_val_zval) == IS_OBJECT && Z_OBJCE_P(array_val_zval)==opencv_mat_ce){
                    mat_obj = Z_PHP_MAT_OBJ_P(array_val_zval);
                    src.push_back(*mat_obj->mat);
                }else if(Z_TYPE_P(array_val_zval) == IS_REFERENCE){
                    array_val_zval = Z_REFVAL_P(array_val_zval);
                    goto again1;
                } else {
                    opencv_throw_exception("array value just Mat object.");
                    RETURN_NULL();
                }
            }ZEND_HASH_FOREACH_END();
    ZEND_HASH_FOREACH_NUM_KEY_VAL(Z_ARRVAL_P(labels_zval),_h,array_val_zval){
                again2:
                if(Z_TYPE_P(array_val_zval) == IS_LONG){
                    labels.push_back((int)zval_get_long(array_val_zval));
                }else if(Z_TYPE_P(array_val_zval) == IS_REFERENCE){
                    array_val_zval = Z_REFVAL_P(array_val_zval);
                    goto again2;
                } else {
                    opencv_throw_exception("array value just number.");
                    RETURN_NULL();
                }
            }ZEND_HASH_FOREACH_END();
    obj->faceRecognizer->train(src,labels);
    RETURN_NULL();

}

PHP_METHOD(opencv_lbph_face_recognizer, predict)
{
    zval *src_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "o", &src_zval, opencv_mat_ce) == FAILURE) {
        RETURN_NULL();
    }
    opencv_lbph_face_recognizer_object *obj = Z_PHP_LBPH_FACE_RECOGNIZER_OBJ_P(getThis());
    opencv_mat_object *src_object = Z_PHP_MAT_OBJ_P(src_zval);
    int predict_label = obj->faceRecognizer->predict(*src_object->mat);
    RETURN_LONG(predict_label);
}

PHP_METHOD(opencv_lbph_face_recognizer, predictConfidence)
{
    zval *src_zval;
    int label = 0;
    double confidence = 0;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "o", &src_zval, opencv_mat_ce) == FAILURE) {
        RETURN_NULL();
    }
    opencv_lbph_face_recognizer_object *obj = Z_PHP_LBPH_FACE_RECOGNIZER_OBJ_P(getThis());
    opencv_mat_object *src_object = Z_PHP_MAT_OBJ_P(src_zval);
    obj->faceRecognizer->predict(*src_object->mat, label, confidence);
    RETURN_DOUBLE(confidence);
}

PHP_METHOD(opencv_lbph_face_recognizer, read)
{
    char *filename;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &filename) == FAILURE) {
        RETURN_NULL();
    }

    opencv_lbph_face_recognizer_object *obj = Z_PHP_LBPH_FACE_RECOGNIZER_OBJ_P(getThis());
    obj->faceRecognizer->read(filename);
    RETURN_NULL();
}

PHP_METHOD(opencv_lbph_face_recognizer, write)
{
    char *filename;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &filename) == FAILURE) {
        RETURN_NULL();
    }

    opencv_lbph_face_recognizer_object *obj = Z_PHP_LBPH_FACE_RECOGNIZER_OBJ_P(getThis());
    obj->faceRecognizer->write(filename);
    RETURN_NULL();
}

PHP_METHOD(opencv_lbph_face_recognizer, update)
{
    zval *src_zval, *labels_zval;
    zend_ulong _h;
    zval *array_val_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "aa", &src_zval, &labels_zval) == FAILURE) {
        RETURN_NULL();
    }
    std::vector<Mat> src;
    std::vector<int> labels;
    //check
    opencv_lbph_face_recognizer_object *obj = Z_PHP_LBPH_FACE_RECOGNIZER_OBJ_P(getThis());
    unsigned long src_count = zend_hash_num_elements(Z_ARRVAL_P(src_zval));
    src.reserve(src_count);//指定长度
    opencv_mat_object *mat_obj;

    ZEND_HASH_FOREACH_NUM_KEY_VAL(Z_ARRVAL_P(src_zval),_h,array_val_zval){
                //check array_val_zval is Mat object
                again1:
                if(Z_TYPE_P(array_val_zval) == IS_OBJECT && Z_OBJCE_P(array_val_zval)==opencv_mat_ce){
                    mat_obj = Z_PHP_MAT_OBJ_P(array_val_zval);
                    src.push_back(*mat_obj->mat);
                }else if(Z_TYPE_P(array_val_zval) == IS_REFERENCE){
                    array_val_zval = Z_REFVAL_P(array_val_zval);
                    goto again1;
                } else {
                    opencv_throw_exception("array value just Mat object.");
                    RETURN_NULL();
                }
            }ZEND_HASH_FOREACH_END();
    ZEND_HASH_FOREACH_NUM_KEY_VAL(Z_ARRVAL_P(labels_zval),_h,array_val_zval){
                again2:
                if(Z_TYPE_P(array_val_zval) == IS_LONG){
                    labels.push_back((int)zval_get_long(array_val_zval));
                }else if(Z_TYPE_P(array_val_zval) == IS_REFERENCE){
                    array_val_zval = Z_REFVAL_P(array_val_zval);
                    goto again2;
                } else {
                    opencv_throw_exception("array value just number.");
                    RETURN_NULL();
                }
            }ZEND_HASH_FOREACH_END();
    obj->faceRecognizer->update(src,labels);
    RETURN_NULL();
}

/**
 * opencv_lbph_face_recognizer_methods[]
 */
const zend_function_entry opencv_lbph_face_recognizer_methods[] = {
        PHP_ME(opencv_lbph_face_recognizer, create, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(opencv_lbph_face_recognizer, train, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(opencv_lbph_face_recognizer, predict, NULL, ZEND_ACC_PUBLIC)
        // todo
        PHP_ME(opencv_lbph_face_recognizer, predictConfidence, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(opencv_lbph_face_recognizer, read, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(opencv_lbph_face_recognizer, write, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(opencv_lbph_face_recognizer, update, NULL, ZEND_ACC_PUBLIC)
        PHP_FE_END
};
/* }}} */

/**
 * @param type
 * @return
 */
zend_object* opencv_lbph_face_recognizer_handler(zend_class_entry *type)
{
    size_t size = sizeof(opencv_lbph_face_recognizer_object);
    opencv_lbph_face_recognizer_object *obj = (opencv_lbph_face_recognizer_object *)ecalloc(1,size);
    memset(obj, 0, sizeof(opencv_lbph_face_recognizer_object));
    zend_object_std_init(&obj->std, type);
    object_properties_init(&obj->std, type);
    obj->std.ce = type;
    obj->std.handlers = &opencv_lbph_face_recognizer_object_handlers;
    return &obj->std;
}


void opencv_lbph_face_recognizer_free_obj(zend_object *object)
{
    opencv_lbph_face_recognizer_object *obj;
    obj = get_lbph_face_recognizer_obj(object);
    delete obj->faceRecognizer;
    zend_object_std_dtor(object);
}

void opencv_lbph_face_recognizer_init(int module_number){
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce,OPENCV_FACE_NS, "LBPHFaceRecognizer", opencv_lbph_face_recognizer_methods);
    opencv_lbph_face_recognizer_ce = zend_register_internal_class_ex(&ce, opencv_face_recognizer_ce);

    opencv_lbph_face_recognizer_ce->create_object = opencv_lbph_face_recognizer_handler;
    memcpy(&opencv_lbph_face_recognizer_object_handlers,
           zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    opencv_lbph_face_recognizer_object_handlers.clone_obj = NULL;
    opencv_lbph_face_recognizer_object_handlers.free_obj = opencv_lbph_face_recognizer_free_obj;
}





/**
 * -----------------------------------【CV\BaseFaceRecognizer】--------------------------------------
 *
 * -------------------------------------------------------------------------------------
 */

/**
 * opencv_lbph_face_recognizer_methods[]
 */
const zend_function_entry opencv_base_face_recognizer_methods[] = {
        PHP_FE_END
};
/* }}} */

void opencv_base_face_recognizer_init(int module_number){
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce,OPENCV_FACE_NS, "BaseFaceRecognizer", opencv_base_face_recognizer_methods);
    opencv_base_face_recognizer_ce = zend_register_internal_class_ex(&ce, opencv_face_recognizer_ce);
}


#else

void opencv_lbph_face_recognizer_init(int module_number){

}

void opencv_base_face_recognizer_init(int module_number){

}

#endif
