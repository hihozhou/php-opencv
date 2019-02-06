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

/* $Id$ */

#pragma once

#ifndef PHP_OPENCV_H
#define PHP_OPENCV_H

extern "C" {
    #include "php.h"

}

#ifdef ZTS
#include "TSRM.h"
#endif

extern zend_module_entry opencv_module_entry;
#define phpext_opencv_ptr &opencv_module_entry

#define PHP_OPENCV_VERSION "0.1.0" /* Replace with version number for your extension */

#ifdef PHP_WIN32
#	define PHP_OPENCV_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_OPENCV_API __attribute__ ((visibility("default")))
#else
#	define PHP_OPENCV_API
#endif



#define OPENCV_NS "CV"
#define OPENCV_FACE_NS ZEND_NS_NAME(OPENCV_NS,"Face")
#define OPENCV_ML_NS ZEND_NS_NAME(OPENCV_NS,"ML")

#define OPENCV_CONNECT(text1,text2) text1##text2


//#define OPENCV_BEGIN_ARG_INFO		ZEND_BEGIN_ARG_INFO
//#define OPENCV_BEGIN_ARG_INFO_EX	ZEND_BEGIN_ARG_INFO_EX

/*
  	Declare any global variables you may need between the BEGIN
	and END macros here:

ZEND_BEGIN_MODULE_GLOBALS(opencv)
	zend_long  global_value;
	char *global_string;
ZEND_END_MODULE_GLOBALS(opencv)
*/

/* Always refer to the globals in your function as OPENCV_G(variable).
   You are encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/
#define OPENCV_G(v) ZEND_MODULE_GLOBALS_ACCESSOR(opencv, v)

#if defined(ZTS) && defined(COMPILE_DL_OPENCV)
ZEND_TSRMLS_CACHE_EXTERN()
#endif

#endif    /* PHP_OPENCV_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
