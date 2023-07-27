cmake_minimum_required (VERSION 3.16)

add_library (cgltf STATIC "src/cgltf.c")
target_include_directories (cgltf PUBLIC "include")
