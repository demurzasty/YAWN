cmake_minimum_required (VERSION 3.8.2)

set (BUILD_SHARED_LIBS OFF)

add_subdirectory ("cgltf-1.13")

add_subdirectory ("duktape-2.7.0")

add_subdirectory ("glew-2.1.0")

set (GLFW_BUILD_EXAMPLES OFF)
set (GLFW_BUILD_TESTS OFF)
set (GLFW_BUILD_DOCS OFF)
set (GLFW_INSTALL OFF)

add_subdirectory ("glfw-3.3.8")

add_subdirectory ("imgui-1.89.9")

add_subdirectory ("inih-r56")

add_subdirectory ("jsmn-1.1.0")

add_subdirectory ("json-c-0.17")

add_subdirectory ("meshoptimizer-0.18")

add_subdirectory ("miniz-3.0.2")

add_subdirectory ("rgbcx-1.12")

add_subdirectory ("stb")
