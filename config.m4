dnl $Id$
dnl config.m4 for extension opencv

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

PHP_ARG_WITH(opencv, for opencv support,
dnl Make sure that the comment is aligned:
[  --with-opencv             Include opencv support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(opencv, whether to enable opencv support,
dnl Make sure that the comment is aligned:
dnl [  --enable-opencv           Enable opencv support])

if test "$PHP_OPENCV" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-opencv -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/opencv.h"  # you most likely want to change this
  dnl if test -r $PHP_OPENCV/$SEARCH_FOR; then # path given as parameter
  dnl   OPENCV_DIR=$PHP_OPENCV
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for opencv files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       OPENCV_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$OPENCV_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the opencv distribution])
  dnl fi

  dnl # --with-opencv -> add include path
  dnl PHP_ADD_INCLUDE($OPENCV_DIR/include)

  dnl # --with-opencv -> check for lib and symbol presence
  dnl LIBNAME=opencv # you may want to change this
  dnl LIBSYMBOL=opencv # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $OPENCV_DIR/$PHP_LIBDIR, OPENCV_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_OPENCVLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong opencv lib version or lib not found])
  dnl ],[
  dnl   -L$OPENCV_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(OPENCV_SHARED_LIBADD)

  PHP_NEW_EXTENSION(opencv, opencv.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
