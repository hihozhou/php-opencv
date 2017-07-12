#include "../../../php_opencv.h"
#include "opencv_persistence.h"
#include "opencv_mat.h"
#include "../../../opencv_exception.h"

zend_class_entry *opencv_file_storage_ce;

zend_object_handlers opencv_file_storage_object_handlers;

zend_object* opencv_file_storage_create_handler(zend_class_entry *type){
    size_t size = sizeof(opencv_file_storage_object);
    opencv_file_storage_object *obj = (opencv_file_storage_object *)ecalloc(1,size);
    memset(obj, 0, sizeof(opencv_file_storage_object));
    zend_object_std_init(&obj->std, type);
    object_properties_init(&obj->std, type);
    obj->std.ce = type;
    obj->std.handlers = &opencv_file_storage_object_handlers;
    return &obj->std;
}

/**
 * //todo encoding param
 * CV\FileStorage __construct
 * @param execute_data
 * @param return_value
 */
PHP_METHOD(opencv_file_storage, __construct){
    char *source;
    long source_len = 0, flags;
    FileStorage *fs;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "|sl", &source, &source_len, &flags) == FAILURE) {
        RETURN_NULL();
    }
    if(source_len == 0){
        fs = new FileStorage();
    }else{
        fs = new FileStorage(source, (int)flags);
    }
    opencv_file_storage_object *obj = Z_PHP_FILE_STORAGE_OBJ_P(getThis());
    obj->fileStorage = fs;
}

/**
 * //todo encoding param
 * CV\FileStorage open
 * @param execute_data
 * @param return_value
 */
PHP_METHOD(opencv_file_storage, open){
    char *source;
    long source_len = 0, flags;
    FileStorage *fs;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "sl", &source, &source_len, &flags) == FAILURE) {
        RETURN_NULL();
    }
    opencv_file_storage_object *obj = Z_PHP_FILE_STORAGE_OBJ_P(getThis());
    obj->fileStorage->open(source, (int)flags);
    RETURN_NULL();
}

PHP_METHOD(opencv_file_storage, write){
    char *name;
    long name_len = 0;
    char *error_message;
    zval *val_zval;
    FileStorage fs;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "sz", &name, &name_len, &val_zval) == FAILURE) {
        RETURN_NULL();
    }
    //todo check name len
    opencv_file_storage_object *obj = Z_PHP_FILE_STORAGE_OBJ_P(getThis());
    fs = *(obj->fileStorage);
    again:
    switch (Z_TYPE_P(val_zval)) {
        case IS_FALSE:
            try{
                fs<< name << false;
            }catch (Exception e){
                opencv_throw_exception(e.what());
            }
        case IS_TRUE:
            try{
                fs<< name << true;
            }catch (Exception e){
                opencv_throw_exception(e.what());
            }
            break;
        case IS_LONG:
            try{
                int long_val = (int)zval_get_long(val_zval);
                fs<< name << long_val;
            }catch (Exception e){
                opencv_throw_exception(e.what());
            }
            break;
        case IS_DOUBLE:
            try{
                double double_val = (double)zval_get_double(val_zval);
                fs<< name << double_val;
            }catch (Exception e){
                opencv_throw_exception(e.what());
            }
            break;
        case IS_STRING:
            //todo check name len and value len
            try{
                String string_val=(String)ZSTR_VAL(zval_get_string(val_zval));
                fs<< name << string_val;
            }catch (Exception e){
                opencv_throw_exception(e.what());
            }
//            if (Z_STRLEN_P(op) > 1 || (Z_STRLEN_P(op) && Z_STRVAL_P(op)[0] != '0')) {
//                result = 1;
//            }
            break;
        case IS_ARRAY:
            //非空数组为true
//            if (zend_hash_num_elements(Z_ARRVAL_P(op))) {
//                result = 1;
//            }
            break;
        case IS_OBJECT:
            //only Mat
            if(Z_OBJCE_P(val_zval) == opencv_mat_ce){
                opencv_mat_object *mat_object = Z_PHP_MAT_OBJ_P(val_zval);
                fs<< name << *(mat_object->mat);
            }else{
                error_message = (char*)malloc(strlen("Can't write file object only Mat.")+ 1);
                strcpy(error_message,"Can't write file object only Mat.");
                opencv_throw_exception(error_message);
                free(error_message);
            }

//            result = zend_object_is_true(op);
            break;
        case IS_RESOURCE:
            error_message = (char*)malloc(strlen("Can't write file on resource.")+ 1);
            strcpy(error_message,"Can't write file on resource.");
            opencv_throw_exception(error_message);
            free(error_message);
        case IS_REFERENCE:
            val_zval = Z_REFVAL_P(val_zval);
            goto again;
            break;
        default:
            break;
    }
    RETURN_NULL();

}

PHP_METHOD(opencv_file_storage, read){

}

PHP_METHOD(opencv_file_storage, release){
    opencv_file_storage_object *obj = Z_PHP_FILE_STORAGE_OBJ_P(getThis());
    obj->fileStorage->release();
    RETURN_NULL();
}

/**
 * opencv_file_storage_methods[]
 */
const zend_function_entry opencv_file_storage_methods[] = {
        PHP_ME(opencv_file_storage, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
        PHP_ME(opencv_file_storage, open, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(opencv_file_storage, write, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(opencv_file_storage, read, NULL, ZEND_ACC_PUBLIC)
        PHP_ME(opencv_file_storage, release, NULL, ZEND_ACC_PUBLIC)
        PHP_FE_END
};
/* }}} */

zval *opencv_file_storage_read_property(zval *object, zval *member, int type, void **cache_slot, zval *rv){
//    std::cout<<"opencv_file_storage_read_property"<<std::endl;
    return std_object_handlers.read_property(object, member, type, cache_slot, rv);

}

/**
 * FileStorage class Init
 */
void opencv_file_storage_init(int module_number){
    zend_class_entry ce;
    INIT_NS_CLASS_ENTRY(ce,OPENCV_NS, "FileStorage", opencv_file_storage_methods);
    opencv_file_storage_ce = zend_register_internal_class(&ce);

//    zend_class_implements(&opencv_file_storage_ce,1,zend_ce_arrayaccess);

    opencv_file_storage_ce->create_object = opencv_file_storage_create_handler;
    memcpy(&opencv_file_storage_object_handlers,
           zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    opencv_file_storage_object_handlers.clone_obj = NULL;
//    opencv_file_storage_object_handlers.write_property = opencv_mat_write_property;
    opencv_file_storage_object_handlers.read_property = opencv_file_storage_read_property;

//    zend_declare_property_null(opencv_mat_ce,"type",sizeof("type") - 1,ZEND_ACC_PRIVATE);//private Mat->type
//    opencv_mat_object_handlers.free_obj = opencv_mat_free_obj;
}