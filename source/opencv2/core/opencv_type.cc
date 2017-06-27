#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "../../../php_opencv.h"
#include "opencv_type.h"

zend_class_entry *opencv_point_ce;
zend_class_entry *opencv_scalar_ce;
zend_class_entry *opencv_size_ce;
zend_class_entry *opencv_rect_ce;

/**
 * -----------------------------------【CV\Point】--------------------------------------
 *
 * -------------------------------------------------------------------------------------
 */

zend_object_handlers opencv_point_object_handlers;

/**
 * Point __construct
 * @param execute_data
 * @param return_value
 */
PHP_METHOD(opencv_point, __construct)
{
    long x=0, y=0;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "|ll", &x, &y) == FAILURE) {
        RETURN_NULL();
    }
    opencv_point_object *obj = Z_PHP_POINT_OBJ_P(getThis());
    Point point = Point((int)x, (int)y);
    obj->point = new Point(point);

    zend_update_property_long(opencv_point_ce, getThis(), "x", sizeof("x")-1, x);
    zend_update_property_long(opencv_point_ce, getThis(), "y", sizeof("y")-1, y);
}

/**
 * print Point data
 * @param execute_data
 * @param return_value
 */
PHP_METHOD(opencv_point, print)
{
    opencv_point_object *obj = Z_PHP_POINT_OBJ_P(getThis());
    std::cout <<*(obj->point)<< std::endl;
    RETURN_NULL();
}



/**
 * opencv_point_methods[]
 */
const zend_function_entry opencv_point_methods[] = {
        PHP_ME(opencv_point, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
        PHP_ME(opencv_point, print, NULL, ZEND_ACC_PUBLIC) //todo why Point print method can effect Mat print method
        PHP_FE_END
};
/* }}} */

zend_object* opencv_point_create_handler(zend_class_entry *type)
{
    int size = sizeof(opencv_point_object);
    opencv_point_object *obj = (opencv_point_object *)ecalloc(1,size);
    memset(obj, 0, sizeof(opencv_point_object));
    zend_object_std_init(&obj->std, type);
    object_properties_init(&obj->std, type);
    obj->std.ce = type;
    obj->std.handlers = &opencv_point_object_handlers;
    return &obj->std;
}

/**
 * Point Class write_property
 * @param object
 * @param member
 * @param value
 * @param cache_slot
 */
void opencv_point_write_property(zval *object, zval *member, zval *value, void **cache_slot){

    zend_string *str = zval_get_string(member);
    char *memberName=ZSTR_VAL(str);
    opencv_point_object *obj = Z_PHP_POINT_OBJ_P(object);

    if(strcmp(memberName, "x") == 0 && obj->point->x!=(int)zval_get_long(value)){
        obj->point->x=(int)zval_get_long(value);
    }else if(strcmp(memberName, "y") == 0 && obj->point->y!=(int)zval_get_long(value)){
        obj->point->y=(int)zval_get_long(value);
    }
    zend_string_release(str);//free zend_string not memberName(zend_string->val)
    std_object_handlers.write_property(object,member,value,cache_slot);

}

/**
 * Point Init
 */
void opencv_point_init(int module_number){
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce,OPENCV_NS, "Point", opencv_point_methods);
    opencv_point_ce = zend_register_internal_class(&ce);

    opencv_point_ce->create_object = opencv_point_create_handler;
    memcpy(&opencv_point_object_handlers,
           zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    opencv_point_object_handlers.clone_obj = NULL;
    opencv_point_object_handlers.write_property = opencv_point_write_property;
}





/**
 * -----------------------------------【CV\Scalar】--------------------------------------
 *
 * -------------------------------------------------------------------------------------
 */

zend_object_handlers opencv_scalar_object_handlers;

zend_object* opencv_scalar_create_handler(zend_class_entry *type)
{
    int size = sizeof(opencv_scalar_object);
    opencv_scalar_object *obj = (opencv_scalar_object *)ecalloc(1,size);
    memset(obj, 0, sizeof(opencv_scalar_object));
    zend_object_std_init(&obj->std, type);
    object_properties_init(&obj->std, type);
    obj->std.ce = type;
    obj->std.handlers = &opencv_scalar_object_handlers;
    return &obj->std;
}


/**
 * Scalar __construct
 * @param execute_data
 * @param return_value
 */
PHP_METHOD(opencv_scalar, __construct)
{
    long blue=0, green = 0, red = 0;//value:0~255
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "|lll", &blue, &green ,&red) == FAILURE) {
        RETURN_NULL();
    }
    opencv_scalar_object *obj = Z_PHP_SCALAR_OBJ_P(getThis());
    Scalar scalar = Scalar((int)blue, (int)green, (int)red);
    obj->scalar = new Scalar(scalar);

    zend_update_property_long(opencv_scalar_ce, getThis(), "blue", sizeof("blue")-1, obj->scalar->val[0]);
    zend_update_property_long(opencv_scalar_ce, getThis(), "green", sizeof("green")-1, obj->scalar->val[1]);
    zend_update_property_long(opencv_scalar_ce, getThis(), "red", sizeof("red")-1, obj->scalar->val[2]);
}


/**
 * print Scalar data
 * @param execute_data
 * @param return_value
 */
PHP_METHOD(opencv_scalar, print)
{
    opencv_scalar_object *obj = Z_PHP_SCALAR_OBJ_P(getThis());
    std::cout <<*(obj->scalar)<< std::endl;
    RETURN_NULL();
}


/**
 * opencv_point_methods[]
 */
const zend_function_entry opencv_scalar_methods[] = {
        PHP_ME(opencv_scalar, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
        PHP_ME(opencv_scalar, print, NULL, ZEND_ACC_PUBLIC)
        PHP_FE_END
};
/* }}} */


/**
 * Point Class write_property
 * @param object
 * @param member
 * @param value
 * @param cache_slot
 */
void opencv_scalar_write_property(zval *object, zval *member, zval *value, void **cache_slot){

    zend_string *str = zval_get_string(member);
    char *memberName=ZSTR_VAL(str);
    opencv_scalar_object *obj = Z_PHP_SCALAR_OBJ_P(object);

    if(strcmp(memberName, "blue") == 0 && obj->scalar->val[0]!=(int)zval_get_long(value)){
        obj->scalar->val[0]=(int)zval_get_long(value);
    }else if(strcmp(memberName, "green") == 0 && obj->scalar->val[1]!=(int)zval_get_long(value)){
        obj->scalar->val[1]=(int)zval_get_long(value);
    }else if(strcmp(memberName, "red") == 0 && obj->scalar->val[2]!=(int)zval_get_long(value)){
        obj->scalar->val[2]=(int)zval_get_long(value);
    }
    zend_string_release(str);//free zend_string not memberName(zend_string->val)
    std_object_handlers.write_property(object,member,value,cache_slot);

}


/**
 * Scalar Init
 */
void opencv_scalar_init(int module_number){
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce,OPENCV_NS, "Scalar", opencv_scalar_methods);
    opencv_scalar_ce = zend_register_internal_class(&ce);

    opencv_scalar_ce->create_object = opencv_scalar_create_handler;
    memcpy(&opencv_scalar_object_handlers,
           zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    opencv_scalar_object_handlers.clone_obj = NULL;
    opencv_scalar_object_handlers.write_property = opencv_scalar_write_property;
}



//-----------------------------------【CV\Size】---------------------------------------
//
//-------------------------------------------------------------------------------------


zend_object_handlers opencv_size_object_handlers;

zend_object* opencv_size_create_handler(zend_class_entry *type)
{
    int size = sizeof(opencv_size_object);
    opencv_size_object *obj = (opencv_size_object *)ecalloc(1,size);
    memset(obj, 0, sizeof(opencv_size_object));
    zend_object_std_init(&obj->std, type);
    object_properties_init(&obj->std, type);
    obj->std.ce = type;
    obj->std.handlers = &opencv_size_object_handlers;
    return &obj->std;
}


/**
 * Size __construct
 * @param execute_data
 * @param return_value
 */
PHP_METHOD(opencv_size, __construct)
{
    long width=0, height = 0;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "|ll", &width, &height) == FAILURE) {
        RETURN_NULL();
    }
    opencv_size_object *obj = Z_PHP_SIZE_OBJ_P(getThis());
    Size size = Size((int)width, (int)height);
    obj->size = new Size(size);

    zend_update_property_long(opencv_scalar_ce, getThis(), "width", sizeof("width")-1, obj->size->width);
    zend_update_property_long(opencv_scalar_ce, getThis(), "height", sizeof("height")-1, obj->size->height);
}


/**
 * print Scalar data
 * @param execute_data
 * @param return_value
 */
PHP_METHOD(opencv_size, print)
{
    opencv_size_object *obj = Z_PHP_SIZE_OBJ_P(getThis());
    std::cout <<*(obj->size)<< std::endl;
    RETURN_NULL();
}


/**
 * opencv_point_methods[]
 */
const zend_function_entry opencv_size_methods[] = {
        PHP_ME(opencv_size, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
        PHP_ME(opencv_size, print, NULL, ZEND_ACC_PUBLIC)
        PHP_FE_END
};
/* }}} */


/**
 * Point Class write_property
 * @param object
 * @param member
 * @param value
 * @param cache_slot
 */
void opencv_size_write_property(zval *object, zval *member, zval *value, void **cache_slot){

    zend_string *str = zval_get_string(member);
    char *memberName=ZSTR_VAL(str);
    opencv_size_object *obj = Z_PHP_SIZE_OBJ_P(object);

    if(strcmp(memberName, "width") == 0 && obj->size->width!=(int)zval_get_long(value)){
        obj->size->width=(int)zval_get_long(value);
    }else if(strcmp(memberName, "height") == 0 && obj->size->height!=(int)zval_get_long(value)){
        obj->size->height=(int)zval_get_long(value);
    }
    zend_string_release(str);//free zend_string not memberName(zend_string->val)
    std_object_handlers.write_property(object,member,value,cache_slot);

}


/**
 * Scalar Init
 */
void opencv_size_init(int module_number){
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce,OPENCV_NS, "Size", opencv_size_methods);
    opencv_size_ce = zend_register_internal_class(&ce);

    opencv_size_ce->create_object = opencv_size_create_handler;
    memcpy(&opencv_size_object_handlers,
           zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    opencv_size_object_handlers.clone_obj = NULL;
    opencv_size_object_handlers.write_property = opencv_size_write_property;
}



//-----------------------------------【CV\Rect】---------------------------------------
//
//-------------------------------------------------------------------------------------


zend_object_handlers opencv_rect_object_handlers;

zend_object* opencv_rect_create_handler(zend_class_entry *type)
{
    int size = sizeof(opencv_rect_object);
    opencv_rect_object *obj = (opencv_rect_object *)ecalloc(1,size);
    memset(obj, 0, sizeof(opencv_rect_object));
    zend_object_std_init(&obj->std, type);
    object_properties_init(&obj->std, type);
    obj->std.ce = type;
    obj->std.handlers = &opencv_rect_object_handlers;
    return &obj->std;
}


/**
 * Rect __construct
 * @param execute_data
 * @param return_value
 */
PHP_METHOD(opencv_rect, __construct)
{
    long x = 0, y = 0, width = 0, height = 0;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "|llll", &x, &y, &width, &height) == FAILURE) {
        RETURN_NULL();
    }
    opencv_rect_object *obj = Z_PHP_RECT_OBJ_P(getThis());
    Rect rect = Rect((int)x, (int)y, (int)width, (int)height);
    obj->rect = new Rect(rect);

    zend_update_property_long(opencv_rect_ce, getThis(), "x", sizeof("x")-1, obj->rect->x);
    zend_update_property_long(opencv_rect_ce, getThis(), "y", sizeof("y")-1, obj->rect->y);
    zend_update_property_long(opencv_rect_ce, getThis(), "width", sizeof("width")-1, obj->rect->width);
    zend_update_property_long(opencv_rect_ce, getThis(), "height", sizeof("height")-1, obj->rect->height);
}


/**
 * print Rect data
 * @param execute_data
 * @param return_value
 */
PHP_METHOD(opencv_rect, print)
{
    opencv_rect_object *obj = Z_PHP_RECT_OBJ_P(getThis());
    std::cout <<*(obj->rect)<< std::endl;
    RETURN_NULL();
}

/**
 * ! the top-left corner
 * @param execute_data
 * @param return_value
 */
PHP_METHOD(opencv_rect, tl)
{
    opencv_rect_object *rect_obj = Z_PHP_RECT_OBJ_P(getThis());
    zval point_zval;

    object_init_ex(&point_zval,opencv_point_ce);
    opencv_point_object *point_obj = Z_PHP_POINT_OBJ_P(&point_zval);
    point_obj->point = new Point(rect_obj->rect->tl());

    zend_update_property_long(opencv_point_ce, &point_zval, "x", sizeof("x")-1, point_obj->point->x);
    zend_update_property_long(opencv_point_ce, &point_zval, "y", sizeof("y")-1, point_obj->point->y);

    RETURN_ZVAL(&point_zval,0,0); //return php Point object
}

/**
 * ! the bottom-right corner
 * @param execute_data
 * @param return_value
 */
PHP_METHOD(opencv_rect, br)
{
    opencv_rect_object *rect_obj = Z_PHP_RECT_OBJ_P(getThis());
    zval point_zval;

    object_init_ex(&point_zval,opencv_point_ce);
    opencv_point_object *point_obj = Z_PHP_POINT_OBJ_P(&point_zval);
    point_obj->point = new Point(rect_obj->rect->br());

    zend_update_property_long(opencv_point_ce, &point_zval, "x", sizeof("x")-1, point_obj->point->x);
    zend_update_property_long(opencv_point_ce, &point_zval, "y", sizeof("y")-1, point_obj->point->y);

    RETURN_ZVAL(&point_zval,0,0); //return php Point object
}

/**
 * size (width, height) of the rectangle
 * @param execute_data
 * @param return_value
 */
PHP_METHOD(opencv_rect, size)
{
    opencv_rect_object *rect_obj = Z_PHP_RECT_OBJ_P(getThis());
    zval size_zval;

    object_init_ex(&size_zval,opencv_size_ce);
    opencv_size_object *size_obj = Z_PHP_SIZE_OBJ_P(&size_zval);
    size_obj->size = new Size(rect_obj->rect->size());

    zend_update_property_long(opencv_size_ce, &size_zval, "width", sizeof("width")-1, size_obj->size->width);
    zend_update_property_long(opencv_size_ce, &size_zval, "height", sizeof("height")-1, size_obj->size->height);

    RETURN_ZVAL(&size_zval,0,0); //return php Point object
}

/**
 * ! area (width*height) of the rectangle
 * @param execute_data
 * @param return_value
 */
PHP_METHOD(opencv_rect, area)
{
    opencv_rect_object *rect_obj = Z_PHP_RECT_OBJ_P(getThis());
    long area = rect_obj->rect->area();
    RETURN_LONG(area);
}


/**
 * opencv_rect_methods[]
 */
const zend_function_entry opencv_rect_methods[] = {
        PHP_ME(opencv_rect, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
        PHP_ME(opencv_rect, print, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(opencv_rect, tl, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(opencv_rect, br, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(opencv_rect, size, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(opencv_rect, area, NULL, ZEND_ACC_PUBLIC)
        PHP_FE_END
};
/* }}} */


/**
 * Rect Class write_property
 * @param object
 * @param member
 * @param value
 * @param cache_slot
 */
void opencv_rect_write_property(zval *object, zval *member, zval *value, void **cache_slot){

    zend_string *str = zval_get_string(member);
    char *memberName=ZSTR_VAL(str);
    opencv_rect_object *obj = Z_PHP_RECT_OBJ_P(object);

    if(strcmp(memberName, "x") == 0 && obj->rect->x!=(int)zval_get_long(value)){
        obj->rect->x=(int)zval_get_long(value);
    }else if(strcmp(memberName, "y") == 0 && obj->rect->y!=(int)zval_get_long(value)){
        obj->rect->y=(int)zval_get_long(value);
    }else if(strcmp(memberName, "width") == 0 && obj->rect->width!=(int)zval_get_long(value)){
        obj->rect->width=(int)zval_get_long(value);
    }else if(strcmp(memberName, "height") == 0 && obj->rect->height!=(int)zval_get_long(value)){
        obj->rect->height=(int)zval_get_long(value);
    }
    zend_string_release(str);//free zend_string not memberName(zend_string->val)
    std_object_handlers.write_property(object,member,value,cache_slot);

}


/**
 * Scalar Init
 */
void opencv_rect_init(int module_number){
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce,OPENCV_NS, "Rect", opencv_rect_methods);
    opencv_rect_ce = zend_register_internal_class(&ce);

    opencv_rect_ce->create_object = opencv_rect_create_handler;
    memcpy(&opencv_rect_object_handlers,
           zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    opencv_rect_object_handlers.clone_obj = NULL;
    opencv_rect_object_handlers.write_property = opencv_rect_write_property;
}


/**
 * Type Init
 */
void opencv_type_init(int module_number){
    opencv_point_init(module_number);
    opencv_scalar_init(module_number);
    opencv_size_init(module_number);
    opencv_rect_init(module_number);
}