cmake_minimum_required(VERSION 2.8.0)
project(cppTestSuite)

#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-elide-constructors")
file(GLOB SRC ./*.cc)

foreach(src ${SRC})
  get_filename_component(TEST_FILE ${src} NAME)
  get_filename_component(TEST_NAME ${src} NAME_WE)

  add_executable(${TEST_NAME} ${TEST_FILE})
  install(TARGETS ${TEST_NAME} DESTINATION bin)
endforeach()
