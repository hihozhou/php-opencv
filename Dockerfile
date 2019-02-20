FROM hihozhou/opencv:latest

MAINTAINER hihzhou <hihzohou@gmail.com>

RUN git clone https://github.com/hihozhou/php-opencv.git \
&& cd php-opencv \
&& phpize \
&& ./configure --with-php-config=/usr/bin/php-config \
&& make \
&& make test \
&& make install \
&& sh -c 'echo "extension=opencv.so" > /etc/php/7.2/mods-available/opencv.ini' \
&& ln -s /etc/php/7.2/mods-available/opencv.ini /etc/php/7.2/cli/conf.d/20-opencv.ini