cmake_minimum_required(VERSION 2.8.0)
project(cppTestSuite)

file(GLOB SRC ./*.cc)

add_library(utils SHARED ${SRC})
install(TARGETS utils DESTINATION lib)
