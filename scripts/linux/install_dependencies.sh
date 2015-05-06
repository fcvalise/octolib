#!/bin/sh

set -e

echo "deb http://llvm.org/apt/precise/ llvm-toolchain-precise main" | tee -a /etc/apt/sources.list
echo "deb http://llvm.org/apt/precise/ llvm-toolchain-precise-3.5 main" | tee -a /etc/apt/sources.list
echo "deb http://ppa.launchpad.net/ubuntu-toolchain-r/test/ubuntu precise main" | tee -a /etc/apt/sources.list
apt-get update -qq

sfml_packages="
libpthread-stubs0-dev
libx11-dev
libgl1-mesa-dev
libxrandr-dev
libfreetype6-dev
libglew1.5-dev
libjpeg8-dev
libsndfile1-dev
libopenal-dev
libudev-dev
libx11-xcb-dev
libxcb-icccm4-dev
libxcb-image0-dev
libxcb-util0-dev
libxcb-randr0-dev
"

for package in $sfml_packages
do
	apt-get install -qq --allow-unauthenticated $package
done

apt-get install -qq libboost-all-dev
apt-get install -qq libpcre3-dev

build_tool_packages="
cmake
clang-3.5
"

for package in $build_tool_packages
do
	apt-get install -qq $package
done
