# 制定系统版本为ubuntu18.04
FROM ubuntu:18.04
MAINTAINER hihzhou <hihzohou@gmail.com>
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive && apt-get install -y  pkg-config cmake git php-cli php-dev