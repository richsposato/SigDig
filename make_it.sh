#!/bin/bash

# g++ -Weffc++ -Wall -std=c++17 -I ../CppUnitTest/include -c ../CppUnitTest/src/UnitTest.cpp -o obj/UnitTest.o

# -DDEBUG

rm ./obj/lookup.o
g++ -Weffc++ -Wall -std=c++17 -I include -I src -c src/lookup.cpp -o obj/lookup.o

rm ./obj/helper.o
g++ -Weffc++ -Wall -std=c++17 -I include -I src -c src/helper.cpp -o obj/helper.o

rm ./obj/utility.o
g++ -Weffc++ -Wall -std=c++17 -I include -I src -c src/utility.cpp -o obj/utility.o

rm ./obj/defined_value.o
g++ -Weffc++ -Wall -std=c++17 -I include -I src -c src/defined_value.cpp -o obj/defined_value.o

rm ./obj/measured_value.o
g++ -Weffc++ -Wall -std=c++17 -I include -I src -c src/measured_value.cpp -o obj/measured_value.o

rm ./obj/calculated_value.o
g++ -Weffc++ -Wall -std=c++17 -I include -I src -c src/calculated_value.cpp -o obj/calculated_value.o

rm ./obj/significant_value.o
g++ -Weffc++ -Wall -std=c++17 -I include -I src -c src/significant_value.cpp -o obj/significant_value.o

rm ./bin/main.o
g++ -Weffc++ -Wall -std=c++17 -I include -I src -I .. -c test/main.cpp -o bin/main.o
g++ -Weffc++ -Wall -std=c++17 -I include -I src -I .. -I ../CppUnitTest/include -c test/main.cpp -o bin/main.o

g++ -Weffc++ -Wall -std=c++17 -I include -I src -I .. -I ../CppUnitTest/include -c test/test_helper.cpp -o bin/test_helper.o

g++ -Weffc++ -Wall -std=c++17 -I include -I src -I .. -I ../CppUnitTest/include -c test/test_defined_value.cpp -o bin/test_defined_value.o

rm ./bin/main.exe
#g++ -Weffc++ -Wall -std=c++17 \
#	bin/main.o \
#	bin/test_helper.o \
#	bin/test_defined_value.o \
#	obj/defined_value.o \
#	obj/measured_value.o \
#	obj/calculated_value.o \
#	obj/significant_value.o \
#	obj/utility.o \
#	obj/helper.o \
#	obj/lookup.o \
#	../boost_1_74_0/stage/lib/libboost_unit_test_framework-vc142-mt-x64-1_74.lib \
#	-o bin/main.exe


#g++ -Weffc++ -Wall -std=c++17 \
#	bin/main.o \
#	bin/test_helper.o \
#	bin/test_defined_value.o \
#	obj/defined_value.o \
#	obj/measured_value.o \
#	obj/calculated_value.o \
#	obj/significant_value.o \
#	obj/utility.o \
#	obj/helper.o \
#	obj/lookup.o \
#	-o bin/main.exe

g++ -Weffc++ -Wall -std=c++17 \
	bin/main.o \
	bin/test_helper.o \
	bin/test_defined_value.o \
	obj/defined_value.o \
	obj/measured_value.o \
	obj/calculated_value.o \
	obj/significant_value.o \
	obj/utility.o \
	obj/helper.o \
	obj/lookup.o \
	obj/UnitTest.o \
	-o bin/main.exe

# g++ -Weffc++ -Wall -std=c++17 bin/main.o obj/defined_value.o obj/measured_value.o obj/calculated_value.o obj/Helper.o obj/UnitTest.o -o bin/main.exe
