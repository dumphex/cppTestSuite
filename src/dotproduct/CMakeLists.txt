cmake_minimum_required(VERSION 2.8.0)
project(cppTestSuite)

set(bin dotProduct)
include_directories("${PROJECT_SOURCE_DIR}/../../libutils")
add_executable(${bin} main.cc dotProduct.cc dotProductImpl.S)
target_link_libraries(${bin} utils)
install(TARGETS ${bin} DESTINATION bin)
