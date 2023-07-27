#pragma once 

#include "String.hpp"

namespace YAWN {
    class Number {
    public:
        static int ToInteger(const String& string);

        static long long ToLongLong(const String& string);

        static float ToFloat(const String& string);

        static String ToString(int value);

        static String ToString(long long value);

        static String ToString(float value);
    };
}