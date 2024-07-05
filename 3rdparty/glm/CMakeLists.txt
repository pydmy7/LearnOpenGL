set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
set(glm_DIR "C:/Users/wangyao/scoop/apps/vcpkg/current/installed/x64-windows/share/glm")

find_package(glm CONFIG REQUIRED)

add_library(interface_glm INTERFACE)
target_link_libraries(interface_glm INTERFACE glm::glm)
