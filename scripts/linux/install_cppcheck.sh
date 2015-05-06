#!/bin/sh

git clone git://github.com/danmar/cppcheck.git cppcheck-repository
cd cppcheck-repository
git pull origin master
g++ -o cppcheck -std=c++0x -include lib/cxx11emu.h -DHAVE_RULES -Ilib -Iexternals/tinyxml cli/*.cpp lib/*.cpp externals/tinyxml/*.cpp -lpcre 
mv cppcheck /usr/bin/
cd ..
