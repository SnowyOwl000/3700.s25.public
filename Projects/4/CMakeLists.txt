cmake_minimum_required(VERSION 3.14)
project(Solution)

set(CMAKE_CXX_STANDARD 14)

#include_directories($ENV{HOME}/Programming/include)

#link_directories($ENV{HOME}/Programming/lib)
#link_libraries(libdataStructures.a)

add_executable(Solution main.cpp bstDictionary.h sampler.cpp sampler.h)