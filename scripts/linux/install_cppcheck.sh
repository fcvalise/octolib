#!/bin/sh

git clone git://github.com/danmar/cppcheck.git cppcheck-repository
cd cppcheck-repository
echo "Building cppcheck..."
make SRCDIR=build CFGDIR=~/cppcheck_config/cfg/ HAVE_RULES=yes
make install
mkdir -p ~/cppcheck_config/cfg/
cp -v ./cfg/* ~/cppcheck_config/cfg/
chmod 777 ~/cppcheck_config/cfg/*
cd ..
