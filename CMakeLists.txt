cmake_minimum_required(VERSION 3.15)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(
    LearnOpenGL
    LANGUAGES CXX C
    DESCRIPTION "Learn OpenGL"
    VERSION 0.1.0
)

include(cmake/addtarget.cmake)

add_subdirectory(3rdparty)
add_subdirectory(test)
