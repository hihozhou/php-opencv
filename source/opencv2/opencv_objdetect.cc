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
#include "core/opencv_type.h"
#include "core/opencv_mat.h"
#include "opencv_objdetect.h"

using namespace cv;

zend_class_entry *opencv_cascade_classifier_ce;

zend_object_handlers opencv_cascade_classifier_object_handlers;

/**
 * @param type
 * @return
 */
zend_object* opencv_cascade_classifier_create_handler(zend_class_entry *type)
{
    int size = sizeof(opencv_cascade_classifier_object);
    opencv_cascade_classifier_object *obj = (opencv_cascade_classifier_object *)ecalloc(1,size);
    memset(obj, 0, sizeof(opencv_cascade_classifier_object));
    zend_object_std_init(&obj->std, type);
    object_properties_init(&obj->std, type);
    obj->std.ce = type;
    obj->std.handlers = &opencv_cascade_classifier_object_handlers;
    return &obj->std;
}

/**
 * CascadeClassifier __construct
 * @param execute_data
 * @param return_value
 */
PHP_METHOD(opencv_cascade_classifier, __construct)
{
    opencv_cascade_classifier_object *obj = Z_PHP_CASCADE_CLASSIFIER_OBJ_P(getThis());
    obj->cascadeClassifier = new CascadeClassifier();
}

PHP_METHOD(opencv_cascade_classifier, load)
{
    char *filename;
    long filename_len;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &filename, &filename_len) == FAILURE) {
        RETURN_NULL();
    }
    opencv_cascade_classifier_object *this_obj = Z_PHP_CASCADE_CLASSIFIER_OBJ_P(getThis());
    bool result = this_obj->cascadeClassifier->load(filename);
    RETURN_BOOL(result);
}

ZEND_BEGIN_ARG_INFO_EX(opencv_cascade_classifier_detect_multi_scale_arginfo, 0, 0, 7)
                ZEND_ARG_INFO(0, image)
                ZEND_ARG_INFO(1, objects)
                ZEND_ARG_INFO(0, scaleFactor)
                ZEND_ARG_INFO(0, minNeighbors)
                ZEND_ARG_INFO(0, flags)
                ZEND_ARG_INFO(0, minSize)
                ZEND_ARG_INFO(0, maxSize)
ZEND_END_ARG_INFO()

/**
 * CascadeClassifier->detectMultiScale function
 * @param execute_data
 * @param return_value
 */
PHP_METHOD(opencv_cascade_classifier, detect_multi_scale)
{
    zval *image_zval, *objects_zval, *min_size_zval = NULL, *max_size_zval = NULL;
    double scale_factor = 1.1;
    long min_neighbors = 3, flags = 0;
    Size min_size = Size(), max_size = Size();
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "Oz|dllOO",
                              &image_zval, opencv_mat_ce,
                              &objects_zval, &scale_factor, &min_neighbors, &flags,
                              &min_size_zval, opencv_size_ce,
                              &max_size_zval, opencv_size_ce

    ) == FAILURE) {
        RETURN_NULL();
    }
    std::vector<Rect> objects;
    opencv_mat_object *image_object = Z_PHP_MAT_OBJ_P(image_zval);
    opencv_cascade_classifier_object *this_obj = Z_PHP_CASCADE_CLASSIFIER_OBJ_P(getThis());
    if(min_size_zval != NULL){
        opencv_size_object *min_size_object = Z_PHP_SIZE_OBJ_P(min_size_zval);
        min_size = *min_size_object->size;
    }

    if(max_size_zval != NULL){
        opencv_size_object *max_size_object = Z_PHP_SIZE_OBJ_P(max_size_zval);
        max_size = *max_size_object->size;
    }

    this_obj->cascadeClassifier->detectMultiScale(
            *(image_object->mat), objects, scale_factor,
            (int)min_neighbors, (int)flags,
            min_size, max_size);

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

/**
 * opencv_cascade_classifier_methods[]
 */
const zend_function_entry opencv_cascade_classifier_methods[] = {
        PHP_ME(opencv_cascade_classifier, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
        PHP_ME(opencv_cascade_classifier, load, NULL, ZEND_ACC_PUBLIC)
        PHP_MALIAS(opencv_cascade_classifier, detectMultiScale ,detect_multi_scale, opencv_cascade_classifier_detect_multi_scale_arginfo, ZEND_ACC_PUBLIC)
        PHP_FE_END
};
/* }}} */

void opencv_cascade_classifier_free_obj(zend_object *object)
{
    opencv_cascade_classifier_object *obj;
    obj = get_cascade_classifier_obj(object);
    delete obj->cascadeClassifier;
    zend_object_std_dtor(object);
}


/**
 * opencv_cascade_classifier_init
 * @param module_number
 */
void opencv_cascade_classifier_init(int module_number){
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce,OPENCV_NS, "CascadeClassifier", opencv_cascade_classifier_methods);
    opencv_cascade_classifier_ce = zend_register_internal_class(&ce);

    opencv_cascade_classifier_ce->create_object = opencv_cascade_classifier_create_handler;
    memcpy(&opencv_cascade_classifier_object_handlers,
           zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    opencv_cascade_classifier_object_handlers.clone_obj = NULL;
//    opencv_cascade_classifier_object_handlers.write_property = opencv_mat_write_property;
    opencv_cascade_classifier_object_handlers.free_obj = opencv_cascade_classifier_free_obj;
}



void opencv_objdetect_constants_init(int module_number)
{

//    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "CV_HAAR_DO_CANNY_PRUNING", CV_HAAR_DO_CANNY_PRUNING, CONST_CS | CONST_PERSISTENT);
//    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "CV_HAAR_SCALE_IMAGE", CV_HAAR_SCALE_IMAGE, CONST_CS | CONST_PERSISTENT);
//    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "CV_HAAR_FIND_BIGGEST_OBJECT", CV_HAAR_FIND_BIGGEST_OBJECT, CONST_CS | CONST_PERSISTENT);
//    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "CV_HAAR_DO_ROUGH_SEARCH", CV_HAAR_DO_ROUGH_SEARCH, CONST_CS | CONST_PERSISTENT);

    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "CASCADE_DO_CANNY_PRUNING", CASCADE_DO_CANNY_PRUNING, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "CASCADE_SCALE_IMAGE", CASCADE_SCALE_IMAGE, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "CASCADE_FIND_BIGGEST_OBJECT", CASCADE_FIND_BIGGEST_OBJECT, CONST_CS | CONST_PERSISTENT);
    REGISTER_NS_LONG_CONSTANT(OPENCV_NS, "CASCADE_DO_ROUGH_SEARCH", CASCADE_DO_ROUGH_SEARCH, CONST_CS | CONST_PERSISTENT);
}

void opencv_objdetect_init(int module_number){
    opencv_cascade_classifier_init(module_number);
    opencv_objdetect_constants_init(module_number);
}