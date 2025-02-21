cmake_minimum_required(VERSION 3.30)
project(lab7)

set(CMAKE_CXX_STANDARD 17)

include_directories($ENV{HOME}/Programming/include)
link_directories($ENV{HOME}/Programming/lib)
link_libraries(libdataStructures.a)

add_executable(lab7 main.cpp)
