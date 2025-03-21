cmake_minimum_required(VERSION 3.30)
project(hybridSort)

set(CMAKE_CXX_STANDARD 17)

add_executable(hybridSort main.cpp
        sampler.cpp
        sampler.h)
