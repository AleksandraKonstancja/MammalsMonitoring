cmake_minimum_required(VERSION 3.7)
project(Part1)

set(CMAKE_C_STANDARD 99)
set(SOURCE_FILES main.c)

add_executable(Part1 ${SOURCE_FILES})
target_link_libraries(Part1 m)