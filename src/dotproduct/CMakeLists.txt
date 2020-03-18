message(STATUS "architecture: " ${ARCHITECTURE})


SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
set(bin dotProduct)
set(src main.cc dotProduct.cc)
if ("${ARCHITECTURE}" STREQUAL "aarch64")
  set(src ${src} dotProductImpl.S)
endif()

include_directories("${PROJECT_SOURCE_DIR}/libutils")
add_executable(${bin} ${src})
target_link_libraries(${bin} utils)
install(TARGETS ${bin} DESTINATION bin)
