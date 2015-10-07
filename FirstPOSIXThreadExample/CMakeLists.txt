cmake_minimum_required(VERSION 3.3)
project(RealTimeSystems)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp tres.c.c tres.c.h)
add_executable(RealTimeSystems ${SOURCE_FILES})