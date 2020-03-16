file(GLOB SRC ./*.cc)

add_library(utils SHARED ${SRC})
install(TARGETS utils DESTINATION lib)
