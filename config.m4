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
    source/opencv2/core/opencv_mat.cc \
    source/opencv2/core/opencv_utility.cc \
    source/opencv2/opencv_imgcodecs.cc \
    opencv_exception.cc \
    source/opencv2/core/hal/opencv_interface.cc \
    source/opencv2/opencv_highgui.cc \
    source/opencv2/core/opencv_type.cc \
    source/opencv2/opencv_core.cc \
    source/opencv2/opencv_imgproc.cc \
    source/opencv2/core/opencv_base.cc \
    source/opencv2/core/opencv_persistence.cc \
    source/opencv2/opencv_objdetect.cc \
    source/opencv2/opencv_videoio.cc \
    source/opencv2/opencv_face.cc \
    source/opencv2/face/opencv_facerec.cc \
    source/opencv2/core/opencv_cvdef.cc \
    source/opencv2/opencv_ml.cc"


    PHP_NEW_EXTENSION(opencv, $opencv_source_file, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)

    dnl Checking for pkg-config
    AC_MSG_CHECKING(for pkg-config)
    if test ! -f "$PKG_CONFIG"; then
          PKG_CONFIG=`which pkg-config`
    fi

    if test -f "$PKG_CONFIG"; then
          AC_MSG_RESULT(found)
          AC_MSG_CHECKING(for opencv)
          if $PKG_CONFIG --exists opencv4; then
              if $PKG_CONFIG --atleast-version=4.0.0 opencv4; then
                  opencv_version=`$PKG_CONFIG --modversion opencv4`
                  AC_MSG_RESULT([found $opencv_version])
                  dnl Add c++ opencv libs and includes by pkg-config
                  OPENCV_LIBS=`$PKG_CONFIG --libs opencv4`
                  OPENCV_INCS=`$PKG_CONFIG --cflags opencv4`
                  PHP_EVAL_INCLINE($OPENCV_INCS)
                  PHP_EVAL_LIBLINE($OPENCV_LIBS, OPENCV_SHARED_LIBADD)
                  AC_DEFINE(HAVE_OPENCV, 1, [whether opencv exists in the system])
              else
                  AC_MSG_RESULT(too old)
                  AC_MSG_ERROR(Ooops ! You need at least opencv 4.0.0)
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
