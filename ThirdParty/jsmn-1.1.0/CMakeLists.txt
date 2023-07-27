cmake_minimum_required (VERSION 3.8.2)

add_library (jsmn STATIC "src/jsmn.c")
target_include_directories (jsmn PUBLIC "include")
