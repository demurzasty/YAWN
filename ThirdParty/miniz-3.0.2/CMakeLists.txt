cmake_minimum_required (VERSION 3.16)

add_library (miniz STATIC "src/miniz.c")
target_include_directories (miniz PUBLIC "include")
