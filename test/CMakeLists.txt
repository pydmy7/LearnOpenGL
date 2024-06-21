set(target test)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src src)

add_executable(${target} ${src})
target_link_libraries(${target} PRIVATE glad::glad glfw::glfw)
target_compile_features(${target} PRIVATE cxx_std_20)
if(MSVC)
    target_compile_options(${target} PRIVATE /W4)
else()
    target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic)
endif()
