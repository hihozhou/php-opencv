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

dnl $PHP_OPENCV=yes
dnl 动态编译的时候总是yes（动态编译是装完php后，在单独编译扩展）
dnl 静态编译要选择--with-opencv/--enable-opencv后为yes（静态编译是安装php时候一起编译安装该扩展）
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

    dnl 使用c++编译
    PHP_REQUIRE_CXX()
    PHP_ADD_LIBRARY(stdc++, 1, OPENCV_SHARED_LIBADD)
    PHP_SUBST(OPENCV_SHARED_LIBADD)

    dnl 指定编译的文件
    PHP_NEW_EXTENSION(opencv, opencv.cc, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)

    dnl 检测pkg-config
    AC_MSG_CHECKING(for pkg-config)
    if test ! -f "$PKG_CONFIG"; then
          dnl 如何没有找到则用命令`which pkg-config`的结果赋值给PKG_CONFIG
          PKG_CONFIG=`which pkg-config`
    fi

    dnl 再次检测pkg-config命令路径
    if test -f "$PKG_CONFIG"; then
          AC_MSG_RESULT(found)
          AC_MSG_CHECKING(for opencv)
          dnl 使用命令pkg-config --exists opencv检测是否存在opencv
          if $PKG_CONFIG --exists opencv; then
              if $PKG_CONFIG --atleast-version=3.2.0 opencv; then
                  opencv_version=`$PKG_CONFIG --modversion opencv`
                  AC_MSG_RESULT([found $opencv_version])
                  OPENCV_LIBS=`$PKG_CONFIG --libs opencv`
                  OPENCV_INCS=`$PKG_CONFIG --cflags opencv`
                  PHP_EVAL_INCLINE($OPENCV_INCS)
                  PHP_EVAL_LIBLINE($OPENCV_LIBS, OPENCV_SHARED_LIBADD)
                  AC_DEFINE(HAVE_OPENCV, 1, [whether opencv exists in the system])
              else
                  AC_MSG_RESULT(too old)
                  AC_MSG_ERROR(Ooops ! You need at least opencv 2.1.0)
              fi
          else
              AC_MSG_RESULT(not found)
              AC_MSG_ERROR(Ooops ! no opencv detected in the system)
          fi
    else
          dnl 找不到则报错退出
          AC_MSG_RESULT(not found)
          AC_MSG_ERROR(Ooops ! no pkg-config found .... )
    fi



fi
