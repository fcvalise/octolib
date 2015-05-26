#!/bin/sh

cppcheck --inline-suppr --quiet --enable=all --error-exitcode=1 --force --std=c++11 -q --platform=unix64 -I/usr/local/include/ -I./includes/ -I./octolib/includes ./includes/ ./src/ 2>&1 | grep -e "warning" -e "error" > cppcheck_results.txt
if [ -s cppcheck_results.txt ]; then
	cat cppcheck_results.txt
	exit 1
fi
