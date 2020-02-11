cmake_minimum_required(VERSION 3.15)
project(geom_test_task)

set(CMAKE_CXX_STANDARD 14)

include_directories(include/)

add_executable(geom_test_task src/main.cpp src/vec.cpp include/vec.h)