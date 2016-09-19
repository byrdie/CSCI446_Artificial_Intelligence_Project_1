cmake_minimum_required(VERSION 3.6)
project(cpp_src)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    map_data_types.cpp
    map_data_types.h
    map_problem_gen.cpp
    map_problem_gen.h)

add_executable(cpp_src ${SOURCE_FILES})