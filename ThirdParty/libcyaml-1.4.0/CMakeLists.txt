cmake_minimum_required (VERSION 3.8.2)

add_library (cyaml STATIC
	"src/free.c"
	"src/load.c"
	"src/mem.c"
	"src/save.c"
	"src/utf8.c"
	"src/util.c"
)
target_include_directories (cyaml PUBLIC "include")
