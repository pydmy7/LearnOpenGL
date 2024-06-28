addExecutable(test)
target_link_libraries(test PRIVATE glad::glad glfw::glfw util::util stb::image)

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/include/test/config.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/config.h"
)
target_include_directories(test PRIVATE "${CMAKE_CURRENT_BINARY_DIR}")
