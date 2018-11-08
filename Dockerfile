FROM hihozhou/opencv:latest

MAINTAINER hihzhou <hihzohou@gmail.com>

RUN git clone https://github.com/hihozhou/php-opencv.git \
&& cd php-opencv \
&& phpize \
&& ./configure --with-php-config=/usr/bin/php-config \
&& make \
&& make test