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
    long source_len = 0, flags = FileStorage::READ;
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
            }catch (Exception e){
                opencv_throw_exception(e.what());
            }
//            if (Z_STRLEN_P(op) > 1 || (Z_STRLEN_P(op) && Z_STRVAL_P(op)[0] != '0')) {
//                result = 1;
//            }
            break;
        case IS_ARRAY:
            //todo only one type array
            opencv_throw_exception("Can't write file on array.");
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
                opencv_throw_exception("Can't write file object only Mat.");
            }
            break;
        case IS_RESOURCE:
            opencv_throw_exception("Can't write file on resource.");
        case IS_REFERENCE:
            val_zval = Z_REFVAL_P(val_zval);
            goto again;
            break;
        default:
            opencv_throw_exception("Can't write file on unknow type.");
            break;
    }
    RETURN_NULL();

}

PHP_METHOD(opencv_file_storage, read){
    char *name;
    long name_len = 0, value_type;
    char *error_message;
    FileStorage fs;
    Mat mat_val;
    opencv_mat_object *mat_object;
    char* char_val;
    String string_val;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "sl", &name, &name_len, &value_type) == FAILURE) {
        RETURN_NULL();
    }
    opencv_file_storage_object *obj = Z_PHP_FILE_STORAGE_OBJ_P(getThis());
    fs = *(obj->fileStorage);
    switch (value_type) {
        case 1://int
            int int_val;
            fs[name]>>int_val;
            RETURN_LONG((long)int_val);
            break;
        case 2://double
            double double_val;
            fs[name]>>double_val;
            RETURN_DOUBLE(double_val);
            break;
        case 3://string
            fs[name] >> string_val;
            char_val = const_cast<char*>(string_val.c_str());
            RETURN_STRING(char_val);
            break;
        case 4://bool
            bool bool_val;
            fs[name] >> bool_val;
            RETURN_BOOL(bool_val);
            break;
        case 5://Mat
            fs[name] >> mat_val;
            zval mat_instance;
            object_init_ex(&mat_instance,opencv_mat_ce);
            mat_object = Z_PHP_MAT_OBJ_P(&mat_instance);
            mat_object->mat = new Mat(mat_val);
            opencv_mat_update_property_by_c_mat(&mat_instance, mat_object->mat);
            RETURN_ZVAL(&mat_instance,0,0);
            break;
        default:
            RETURN_NULL();
            break;
    }
}

PHP_METHOD(opencv_file_storage, release){
    opencv_file_storage_object *obj = Z_PHP_FILE_STORAGE_OBJ_P(getThis());
    obj->fileStorage->release();
    RETURN_NULL();
}

/**
 * CV\FileStorage->isOpened()
 * @param execute_data
 * @param return_value
 */
PHP_METHOD(opencv_file_storage, is_opened){
    opencv_file_storage_object *obj = Z_PHP_FILE_STORAGE_OBJ_P(getThis());
    RETURN_BOOL(obj->fileStorage->isOpened());
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
        PHP_MALIAS(opencv_file_storage, isOpened ,is_opened, NULL, ZEND_ACC_PUBLIC)
        PHP_FE_END
};
/* }}} */

zval *opencv_file_storage_read_property(zval *object, zval *member, int type, void **cache_slot, zval *rv){
//    std::cout<<"opencv_file_storage_read_property"<<std::endl;
    return std_object_handlers.read_property(object, member, type, cache_slot, rv);

}

void opencv_file_storage_consts_init(int module_number){
    //! file storage mode
    //@see cv::FileStorage::Mode
    zend_declare_class_constant_long(opencv_file_storage_ce,"READ",sizeof("READ")-1,FileStorage::READ);
    zend_declare_class_constant_long(opencv_file_storage_ce,"WRITE",sizeof("WRITE")-1,FileStorage::WRITE);
    zend_declare_class_constant_long(opencv_file_storage_ce,"APPEND",sizeof("APPEND")-1,FileStorage::APPEND);
    zend_declare_class_constant_long(opencv_file_storage_ce,"MEMORY",sizeof("MEMORY")-1,FileStorage::MEMORY);

    zend_declare_class_constant_long(opencv_file_storage_ce,"FORMAT_MASK",sizeof("FORMAT_MASK")-1,FileStorage::FORMAT_MASK);
    zend_declare_class_constant_long(opencv_file_storage_ce,"FORMAT_AUTO",sizeof("FORMAT_AUTO")-1,FileStorage::FORMAT_AUTO);
    zend_declare_class_constant_long(opencv_file_storage_ce,"FORMAT_XML",sizeof("FORMAT_XML")-1,FileStorage::FORMAT_XML);
    zend_declare_class_constant_long(opencv_file_storage_ce,"FORMAT_YAML",sizeof("FORMAT_YAML")-1,FileStorage::FORMAT_YAML);
    zend_declare_class_constant_long(opencv_file_storage_ce,"FORMAT_JSON",sizeof("FORMAT_JSON")-1,FileStorage::FORMAT_JSON);
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
    opencv_file_storage_consts_init(module_number);
}