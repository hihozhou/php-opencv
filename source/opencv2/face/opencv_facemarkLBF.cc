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
#include "opencv_facemarkLBF.h"

#ifdef HAVE_OPENCV_FACE

#include "../opencv_face.h"
#include "../core/opencv_type.h"
#include "../core/opencv_mat.h"
#include "../../../opencv_exception.h"
#include <opencv2/face.hpp>
using namespace cv::face;

#define Z_PHP_FACEMARK_LBF_OBJ_P(zv)  get_facemark_lbf_obj(Z_OBJ_P(zv))

typedef struct _opencv_facemark_lbf_object{
    Ptr<FacemarkLBF> Facemark;
    zend_object std;
}opencv_facemark_lbf_object;


/**
 * @param obj
 * @return
 */
static inline opencv_facemark_lbf_object* get_facemark_lbf_obj(zend_object *obj) {
    return (opencv_facemark_lbf_object*)((char*)(obj) - XtOffsetOf(opencv_facemark_lbf_object, std));
}

zend_object_handlers opencv_facemark_lbf_object_handlers;

zend_class_entry *opencv_facemark_lbf_ce;

zend_class_entry *opencv_base_facemark_ce;

PHP_METHOD(opencv_facemark_lbf, create)
{
    zval instance;
    object_init_ex(&instance, opencv_facemark_lbf_ce);
    opencv_facemark_lbf_object *obj = Z_PHP_FACEMARK_LBF_OBJ_P(&instance);
    obj->Facemark = FacemarkLBF::create();
    RETURN_ZVAL(&instance,0,0);
}

PHP_METHOD(opencv_facemark_lbf, loadModel)
{
    char *filename;
    size_t filename_len;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &filename, &filename_len) == FAILURE) {
        RETURN_NULL();
    }

    opencv_facemark_lbf_object *obj = Z_PHP_FACEMARK_LBF_OBJ_P(getThis());
    obj->Facemark->loadModel(filename);
    RETURN_NULL();
}

PHP_METHOD(opencv_facemark_lbf, getFaces)
{
    zval *image_zval, *objects_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "Oz", &image_zval, opencv_mat_ce, &objects_zval) == FAILURE) {
        RETURN_NULL();
    }

    std::vector<Rect> objects;
    opencv_mat_object *image_object = Z_PHP_MAT_OBJ_P(image_zval);
    opencv_facemark_lbf_object *obj = Z_PHP_FACEMARK_LBF_OBJ_P(getThis());
    obj->Facemark->getFaces(*(image_object->mat), objects);

    zval *objects_real_zval = Z_REFVAL_P(objects_zval);

    zval_dtor(objects_real_zval);//if real_zval value not eq null ,free real_zval to avoid memory leaks detected

    array_init(objects_real_zval);
    for(unsigned long i=0; i < objects.size(); i++){
        zval OPENCV_CONNECT(zval,i);
        Rect OPENCV_CONNECT(rect,i);
        opencv_rect_object *OPENCV_CONNECT(rect_object,i);
        object_init_ex(&OPENCV_CONNECT(zval,i), opencv_rect_ce);
        OPENCV_CONNECT(rect_object,i) = Z_PHP_RECT_OBJ_P(&OPENCV_CONNECT(zval,i));
        OPENCV_CONNECT(rect,i) = objects.at(i);
        OPENCV_CONNECT(rect_object,i)->rect = new Rect(OPENCV_CONNECT(rect,i));
        opencv_rect_update_property_by_c_rect(&OPENCV_CONNECT(zval,i), OPENCV_CONNECT(rect_object,i)->rect);

        add_next_index_zval(objects_real_zval,&OPENCV_CONNECT(zval,i));
    }

    RETURN_NULL();
}

ZEND_BEGIN_ARG_INFO_EX(opencv_facemark_lbf_fit_arginfo, 0, 0, 3)
                ZEND_ARG_INFO(0, image)
                ZEND_ARG_INFO(0, faces)
                ZEND_ARG_INFO(1, landmarks)
ZEND_END_ARG_INFO()

PHP_METHOD(opencv_facemark_lbf, fit)
{
    zval *image_zval, *faces_array, *landmarks_zval, *array_val_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "Oaz", &image_zval, opencv_mat_ce, &faces_array, &landmarks_zval) == FAILURE) {
        RETURN_NULL();
    }

    std::vector<Rect> faces;

    zend_ulong _h;
    ZEND_HASH_FOREACH_NUM_KEY_VAL(Z_ARRVAL_P(faces_array),_h,array_val_zval){
        //check array_val_zval is Mat object
        if(Z_TYPE_P(array_val_zval) == IS_OBJECT && Z_OBJCE_P(array_val_zval)==opencv_rect_ce){
            opencv_rect_object *rect_object = Z_PHP_RECT_OBJ_P(array_val_zval);
            faces.push_back(*rect_object->rect);
        }else {
            opencv_throw_exception("array value just Rect object.");
            RETURN_NULL();
        }
    }ZEND_HASH_FOREACH_END();

    std::vector<std::vector<Point2f> > landmarks;

    opencv_mat_object *image_object = Z_PHP_MAT_OBJ_P(image_zval);
    opencv_facemark_lbf_object *obj = Z_PHP_FACEMARK_LBF_OBJ_P(getThis());
    obj->Facemark->fit(*(image_object->mat), faces, landmarks);

    zval *landmarks_real_zval = Z_REFVAL_P(landmarks_zval);

    zval_dtor(landmarks_real_zval);//if real_zval value not eq null ,free real_zval to avoid memory leaks detected

    array_init(landmarks_real_zval);

    int point_count = 0;
    for(unsigned long i=0; i < landmarks.size(); i++){
        zval OPENCV_CONNECT(zval_arr,i);
        array_init(&OPENCV_CONNECT(zval_arr,i));
        for(unsigned long j=0; j < landmarks.at(i).size(); j++){
            zval OPENCV_CONNECT(zval_point,point_count);
            object_init_ex(&OPENCV_CONNECT(zval_point,point_count), opencv_point_ce);
            //printf("* Debug %i %i\n", i, j, landmarks.at(i).at(j));
            Z_PHP_POINT_OBJ_P(&OPENCV_CONNECT(zval_point,point_count))->point=new Point(landmarks.at(i).at(j));
            opencv_point_update_property_by_c_point(&OPENCV_CONNECT(zval_point,point_count), Z_PHP_POINT_OBJ_P(&OPENCV_CONNECT(zval_point,point_count))->point);
            add_next_index_zval(&OPENCV_CONNECT(zval_arr,i),&OPENCV_CONNECT(zval_point,point_count));
            point_count++;
        }
        add_next_index_zval(landmarks_real_zval,&OPENCV_CONNECT(zval_arr,i));
    }

    RETURN_NULL();//RETURN_ZVAL(landmarks_real_zval,0,0);
}

/**
 * opencv_facemark_lbf_methods[]
 */
const zend_function_entry opencv_facemark_lbf_methods[] = {
        PHP_ME(opencv_facemark_lbf, create, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
        PHP_ME(opencv_facemark_lbf, loadModel, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(opencv_facemark_lbf, getFaces, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(opencv_facemark_lbf, fit, opencv_facemark_lbf_fit_arginfo, ZEND_ACC_PUBLIC)
        PHP_FE_END
};
/* }}} */

/**
 * @param type
 * @return
 */
zend_object* opencv_facemark_lbf_handler(zend_class_entry *type)
{
    size_t size = sizeof(opencv_facemark_lbf_object)+zend_object_properties_size(type);
    opencv_facemark_lbf_object *obj = (opencv_facemark_lbf_object *)ecalloc(1,size);
    memset(obj, 0, size);
    zend_object_std_init(&obj->std, type);
    object_properties_init(&obj->std, type);
    obj->std.ce = type;
    obj->std.handlers = &opencv_facemark_lbf_object_handlers;
    return &obj->std;
}


void opencv_facemark_lbf_free_obj(zend_object *object)
{
    opencv_facemark_lbf_object *obj;
    obj = get_facemark_lbf_obj(object);
    delete obj->Facemark;
    zend_object_std_dtor(object);
}

void opencv_facemark_lbf_init(int module_number){
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce,OPENCV_FACE_NS, "FacemarkLBF", opencv_facemark_lbf_methods);
    opencv_facemark_lbf_ce = zend_register_internal_class_ex(&ce, opencv_facemark_lbf_ce);

    opencv_facemark_lbf_ce->create_object = opencv_facemark_lbf_handler;
    memcpy(&opencv_facemark_lbf_object_handlers,
           zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    opencv_facemark_lbf_object_handlers.clone_obj = NULL;
    opencv_facemark_lbf_object_handlers.free_obj = opencv_facemark_lbf_free_obj;
    opencv_facemark_lbf_object_handlers.offset = XtOffsetOf(opencv_facemark_lbf_object, std);
}





/**
 * -----------------------------------【CV\BaseFaceRecognizer】--------------------------------------
 *
 * -------------------------------------------------------------------------------------
 */

/**
 * opencv_facemark_lbf_methods[]
 */
const zend_function_entry opencv_base_facemark_methods[] = {
        PHP_FE_END
};
/* }}} */

void opencv_base_facemark_init(int module_number){
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce,OPENCV_FACE_NS, "BaseFacemarkLBF", opencv_base_facemark_methods);
    opencv_base_facemark_ce = zend_register_internal_class_ex(&ce, opencv_facemark_lbf_ce);
}


#else

void opencv_facemark_lbf_init(int module_number){

}

void opencv_base_facemark_init(int module_number){

}

#endif
