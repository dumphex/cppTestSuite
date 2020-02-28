cmake_minimum_required(VERSION 2.8.0)
project(cppTestSuite)

set(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -v -g")
#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -fno-inline-functions")

add_subdirectory(src)
