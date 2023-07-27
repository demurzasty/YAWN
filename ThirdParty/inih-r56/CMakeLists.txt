cmake_minimum_required (VERSION 3.8.2)

add_library (inih STATIC "ini.c")
target_include_directories (inih PUBLIC ".")
