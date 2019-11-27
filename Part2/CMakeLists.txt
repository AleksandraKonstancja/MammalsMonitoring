cmake_minimum_required(VERSION 3.7)
project(Part2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Location.cpp Location.h MammalData.cpp MammalData.h)
add_executable(Part2 ${SOURCE_FILES} Location.cpp Location.h MammalData.cpp MammalData.h)