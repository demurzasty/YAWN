cmake_minimum_required (VERSION 3.16)

add_executable (Example "Source/Main.cpp")
target_link_libraries (Example PUBLIC YAWN)
target_compile_definitions (Example PUBLIC YAWN_CURRENT_DIRECTORY_INTERNAL="${CMAKE_CURRENT_SOURCE_DIR}")

set_target_properties(
    Example PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
