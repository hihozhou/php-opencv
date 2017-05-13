dnl $Id$
dnl config.m4 for extension opencv

PHP_ARG_WITH(opencv, for opencv support,
[  --with-opencv             Include opencv support])

PHP_ARG_ENABLE(opencv, whether to enable opencv support,
dnl [  --enable-opencv           Enable opencv support])

if test "$PHP_OPENCV" != "no"; then
    dnl Write more examples of tests here...

    dnl Compile with c++
    PHP_REQUIRE_CXX()
    PHP_ADD_LIBRARY(stdc++, 1, OPENCV_SHARED_LIBADD)
    PHP_SUBST(OPENCV_SHARED_LIBADD)

    PHP_NEW_EXTENSION(opencv, opencv.cc, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)

    dnl Chekcing for pkg-config command position
    AC_MSG_CHECKING(for pkg-config)
    if test ! -f "$PKG_CONFIG"; then
          PKG_CONFIG=`which pkg-config`
    fi

    if test -f "$PKG_CONFIG"; then
          AC_MSG_RESULT(found)
          AC_MSG_CHECKING(for opencv)
          dnl Add c++ OpenCV libs and includes by pkg-config
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
          AC_MSG_RESULT(not found)
          AC_MSG_ERROR(Ooops ! no pkg-config found .... )
    fi



fi
