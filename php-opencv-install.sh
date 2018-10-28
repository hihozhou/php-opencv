#!/bin/sh
set -e

SUPPORT_MAP="
x86_64-centos-7
x86_64-fedora-26
x86_64-fedora-27
x86_64-fedora-28
x86_64-debian-wheezy
x86_64-debian-jessie
x86_64-debian-stretch
x86_64-debian-buster
x86_64-ubuntu-trusty
x86_64-ubuntu-xenial
x86_64-ubuntu-bionic
x86_64-ubuntu-artful
s390x-ubuntu-xenial
s390x-ubuntu-bionic
s390x-ubuntu-artful
ppc64le-ubuntu-xenial
ppc64le-ubuntu-bionic
ppc64le-ubuntu-artful
aarch64-ubuntu-xenial
aarch64-ubuntu-bionic
aarch64-debian-jessie
aarch64-debian-stretch
aarch64-debian-buster
aarch64-fedora-26
aarch64-fedora-27
aarch64-fedora-28
aarch64-centos-7
armv6l-raspbian-jessie
armv7l-raspbian-jessie
armv6l-raspbian-stretch
armv7l-raspbian-stretch
armv7l-debian-jessie
armv7l-debian-stretch
armv7l-debian-buster
armv7l-ubuntu-trusty
armv7l-ubuntu-xenial
armv7l-ubuntu-bionic
armv7l-ubuntu-artful
"

get_system_distribution() {
	lsb_dist=""
	# Every system that we officially support has /etc/os-release
	# 从/etc/os-release文件中读取系统信息
	# 如NAME="Ubuntu"
	#VERSION="16.04.5 LTS (Xenial Xerus)"
	#ID=ubuntu
	#ID_LIKE=debian
	#PRETTY_NAME="Ubuntu 16.04.5 LTS"
	#VERSION_ID="16.04"
	#HOME_URL="http://www.ubuntu.com/"
	#SUPPORT_URL="http://help.ubuntu.com/"
	#BUG_REPORT_URL="http://bugs.launchpad.net/ubuntu/"
	#VERSION_CODENAME=xenial
	#UBUNTU_CODENAME=xenial
	if [ -r /etc/os-release ]; then
		lsb_dist="$(. /etc/os-release && echo "$ID")"
	fi
	# Returning an empty string here should be alright since the
	# case statements don't act unless you provide an actual value
	echo "$lsb_dist"
}

do_install(){
    # ubuntu 下直接用build-essential包安装c\c++编译环境
    echo "The C\C++ compiler environment (build-essential package) is being installed..."
    echo "$(sudo apt-get install -y build-essential)"
    echo "Build-essential software package installed successfully"
    echo "$(sudo apt-get install -y git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev -qq)"


}
do_install
