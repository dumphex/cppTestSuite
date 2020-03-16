include_directories("${PROJECT_SOURCE_DIR}/libutils/")

set(EXTRA_LIBS utils pthread)
file(GLOB SRC ./*.c*)

foreach(src ${SRC})
  get_filename_component(TEST_FILE ${src} NAME)
  get_filename_component(TEST_NAME ${src} NAME_WE)

  add_executable(${TEST_NAME} ${TEST_FILE})
  target_link_libraries(${TEST_NAME}  ${EXTRA_LIBS})
  install(TARGETS ${TEST_NAME} DESTINATION bin)
endforeach()

execute_process(
  COMMAND bash "-c" "uname -m|tr -d '\n'"
  OUTPUT_VARIABLE ARCHITECTURE
)

message(STATUS "architecture: " ${ARCHITECTURE})
if ("${ARCHITECTURE}" STREQUAL "aarch64")
  add_subdirectory(dotproduct)
endif()
