#pragma once 

#define YAWN_WIDE_INTERNAL(x) L##x
#define YAWN_WIDE(x) YAWN_WIDE_INTERNAL(x)

#ifndef YAWN_CURRENT_DIRECTORY
#   ifndef YAWN_CURRENT_DIRECTORY_INTERNAL
#      define YAWN_CURRENT_DIRECTORY_INTERNAL "."
#   endif

#   define YAWN_CURRENT_DIRECTORY YAWN_WIDE(YAWN_CURRENT_DIRECTORY_INTERNAL)
#endif

#ifdef _MSC_VER
#	define YAWN_DEBUG_BREAK() __debugbreak()
#   define YAWN_NOVTABLE __declspec(novtable)
#   define YAWN_ASSUME(x) __assume(x)
#   define YAWN_PRETTY_FUNCTION __FUNCSIG__
#elif defined(__clang__)
#	define YAWN_DEBUG_BREAK() __builtin_debugtrap()
#   define YAWN_NOVTABLE 
#   define YAWN_ASSUME(x)
#   define YAWN_PRETTY_FUNCTION __PRETTY_FUNCTION__
#else
#	define YAWN_DEBUG_BREAK() __builtin_trap()
#   define YAWN_NOVTABLE 
#   define YAWN_ASSUME(x)
#   define YAWN_PRETTY_FUNCTION __PRETTY_FUNCTION__
#endif
