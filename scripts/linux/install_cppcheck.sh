#!/bin/sh

git clone git://github.com/danmar/cppcheck.git cppcheck-repository
cd cppcheck-repository
echo "Building cppcheck..."
make SRCDIR=build CFGDIR=cfg HAVE_RULES=yes
make install
cp -R -v ./cfg/ /usr/bin/
cd ..
