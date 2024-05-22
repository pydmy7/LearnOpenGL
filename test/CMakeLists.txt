set(target test)

addExecutable(${target})
target_link_libraries(${target} PRIVATE glad::glad glfw::glfw)
