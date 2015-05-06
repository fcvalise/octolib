#!/bin/sh

git clone git://github.com/danmar/cppcheck.git cppcheck-repository
cd cppcheck-repository
echo "Building cppcheck..."
g++ -o cppcheck -std=c++0x -include lib/cxx11emu.h -DCFGDIR="cfg" -DHAVE_RULES -Ilib -Iexternals/tinyxml cli/*.cpp lib/*.cpp externals/tinyxml/*.cpp -lpcre 
mv cppcheck /usr/bin/
cd ..
