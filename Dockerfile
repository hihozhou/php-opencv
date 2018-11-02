# 制定系统版本为ubuntu18.04
FROM ubuntu:18.04
MAINTAINER hihzhou <hihzohou@gmail.com>



RUN apt-get update && export DEBIAN_FRONTEND=noninteractive && apt-get install -y  pkg-config cmake git php-cli php-dev

RUN apt-get install gcc-4.8 -y
RUN apt-get install gcc-4.8 -y
RUN apt-get install -y git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev
RUN apt-get install -y python-dev python-numpy libtbb2 libtbb-dev libjpeg-dev libpng-dev libtiff-dev libdc1394-22-dev

RUN git clone https://github.com/opencv/opencv.git

RUN cd opencv

RUN git checkout -b 4.0.0-beta 4.0.0-beta

RUN mkdir build

RUN cd build
