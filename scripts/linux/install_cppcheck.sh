#!/bin/sh

git clone git://github.com/danmar/cppcheck.git cppcheck-repository
cd cppcheck-repository
echo "Building cppcheck..."
chmod 777 cfg
chmod 777 cfg/*
make SRCDIR=build CFGDIR=$PWD/cfg/ HAVERULE=yes
make install
cd ..
