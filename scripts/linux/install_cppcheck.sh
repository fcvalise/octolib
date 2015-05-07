#!/bin/sh

git clone git://github.com/danmar/cppcheck.git cppcheck-repository
cd cppcheck-repository
echo "Building cppcheck..."
make SRCDIR=build CFGDIR=$PWD/cfg/ HAVERULE=yes
make install
cd ..
