#pragma once 

#include "Config.hpp"

#ifdef _DEBUG
#   define YAWN_ASSERT(cond) if (!(cond)) { YAWN_DEBUG_BREAK(); } else (0)
#else
#   define YAWN_ASSERT(cond) ((void)0)
#endif
