# 制定系统版本为ubuntu18.04
FROM ubuntu:18.04
MAINTAINER hihzhou <hihzohou@gmail.com>



RUN apt-get update && export DEBIAN_FRONTEND=noninteractive && apt-get install -y  pkg-config cmake git php-cli php-dev qt5-qmake

RUN apt-get install gcc-4.8 -y
RUN apt-get install gcc-4.8 -y
RUN apt-get install -y git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev
RUN apt-get install -y python-dev python-numpy libtbb2 libtbb-dev libjpeg-dev libpng-dev libtiff-dev libdc1394-22-dev

RUN git clone --depth 1 https://github.com/opencv/opencv.git

RUN cd opencv && mkdir build && cd build && cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local -D WITH_TBB=ON -D BUILD_NEW_PYTHON_SUPPORT=ON -D WITH_V4L=ON -D INSTALL_C_EXAMPLES=ON -D INSTALL_PYTHON_EXAMPLES=ON -D BUILD_EXAMPLES=ON -D WITH_QT=ON -D WITH_OPENGL=ON ..
