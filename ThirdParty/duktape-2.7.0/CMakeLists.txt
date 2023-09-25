cmake_minimum_required (VERSION 3.19)

add_library (duktape STATIC "duktape.c")
target_include_directories (duktape PUBLIC ".")
