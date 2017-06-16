dnl $Id$
dnl config.m4 for extension opencv

PHP_ARG_WITH(opencv, for opencv support,
dnl Make sure that the comment is aligned:
[  --with-opencv             Include opencv support])


AC_MSG_CHECKING(for php debug)


if test -z "$PHP_DEBUG"; then
    AC_ARG_ENABLE(debug,
    [   --enable-debug          compile with debugging symbols],[
        PHP_DEBUG=$enableval
    ],[ PHP_DEBUG=no
    ])
else
    AC_MSG_RESULT(no)
fi

dnl 检测是否启用调试
if test "$PHP_OPENCV_DEBUG" != "no"; then
    dnl 是，则设置 C 语言宏指令
    AC_DEFINE(USE_OPENCV_DEBUG,1,[Include debugging support in example])
fi

dnl AC_MSG_ERROR(Ooops ! no pkg-config found .... )
if test "$PHP_OPENCV" != "no"; then
    dnl Compile using c++
    PHP_REQUIRE_CXX()
    PHP_ADD_LIBRARY(stdc++, 1, OPENCV_SHARED_LIBADD)
    PHP_SUBST(OPENCV_SHARED_LIBADD)

    opencv_source_file="opencv.cc \
    source/opencv2/core/mat.cc \
    cv.cc \
    source/opencv2/core/hal/interface.cc \
    source/opencv2/highgui.cc \
    source/opencv2/imgcodecs/imgcodecs_c.cc"


    PHP_NEW_EXTENSION(opencv, $opencv_source_file, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)

    dnl Checking for pkg-config
    AC_MSG_CHECKING(for pkg-config)
    if test ! -f "$PKG_CONFIG"; then
          PKG_CONFIG=`which pkg-config`
    fi

    if test -f "$PKG_CONFIG"; then
          AC_MSG_RESULT(found)
          AC_MSG_CHECKING(for opencv)
          if $PKG_CONFIG --exists opencv; then
              if $PKG_CONFIG --atleast-version=3.2.0 opencv; then
                  opencv_version=`$PKG_CONFIG --modversion opencv`
                  AC_MSG_RESULT([found $opencv_version])
                  dnl Add c++ opencv libs and includes by pkg-config
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
          AC_MSG_RESULT(not found)
          AC_MSG_ERROR(Ooops ! no pkg-config found .... )
    fi


fi