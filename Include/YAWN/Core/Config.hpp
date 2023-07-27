#pragma once 

#define YAWN_WIDE_INTERNAL(x) L##x
#define YAWN_WIDE(x) YAWN_WIDE_INTERNAL(x)

#ifdef _MSC_VER
#	define YAWN_DEBUG_BREAK() __debugbreak()
#   define YAWN_NOVTABLE __declspec(novtable)
#   define YAWN_PRETTY_FUNCTION __FUNCSIG__
#else
#	define YAWN_DEBUG_BREAK() __builtin_trap()
#   define YAWN_NOVTABLE 
#   define YAWN_PRETTY_FUNCTION __PRETTY_FUNCTION__
#endif
