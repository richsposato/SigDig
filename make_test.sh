#!/bin/bash

g++ -Weffc++ -Wall -std=c++17 -I include -I src -I .. -c test/boost_test.cpp -o bin/boost_test.o

g++ -Weffc++ -Wall -std=c++17 \
	bin/boost_test.o \
	../boost_1_74_0/stage/lib/libboost_unit_test_framework-vc142-mt-x64-1_74.a \
	/usr/lib/gcc/x86_64-pc-cygwin/9.3.0/libstdc++.a \
	-o bin/boost_test.exe
