#!/bin/sh

INCLUDES="./includes/* ./includes/details/*"
SRCS="./src/"

cppcheck --inline-suppr --quiet --enable=all --error-exitcode=1												\
		 --force --std=c++11 -q --platform=unix64 --suppressions ./scripts/unix/cpp_check_suppressions.txt 	\
		 -I/usr/local/include/ $INCLUDES $SRCS 2>&1 | grep -e "warning" -e "error" > cppcheck_results.txt

if [ -s cppcheck_results.txt ]; then
	cat cppcheck_results.txt
	rm cppcheck_results.txt
	exit 1
else
	rm cppcheck_results.txt
	exit 0
fi
