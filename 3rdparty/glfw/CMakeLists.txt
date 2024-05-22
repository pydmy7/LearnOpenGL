add_library(glfwImported STATIC IMPORTED GLOBAL)
set_target_properties(
    glfwImported
    PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/include"
    IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw3.lib"
    IMPORTED_LINK_INTERFACE_LANGUAGES "C"
)
add_library(glfw::glfw ALIAS glfwImported)
