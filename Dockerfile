# 制定系统版本为ubuntu18.04
FROM ubuntu:18.04

MAINTAINER hihzhou <hihzohou@gmail.com>

RUN apt-get update \
&& export DEBIAN_FRONTEND=noninteractive \
&& apt-get install -y  pkg-config cmake git php-cli php-dev qt5-default \
&& git clone --depth 1 https://github.com/opencv/opencv.git \
&& cd opencv \
&& mkdir build \
&& cd build \
&& cmake -D CMAKE_BUILD_TYPE=RELEASE \
-D CMAKE_INSTALL_PREFIX=/usr/local \
-D WITH_TBB=ON \
-D WITH_V4L=ON \
-D INSTALL_C_EXAMPLES=OFF \
-D INSTALL_PYTHON_EXAMPLES=OFF \
-D BUILD_EXAMPLES=OFF \
-D BUILD_JAVA=OFF \
-D BUILD_TESTS=OFF \
-D WITH_QT=ON \
-D WITH_OPENGL=ON  .. \
&& make \
&& make install
