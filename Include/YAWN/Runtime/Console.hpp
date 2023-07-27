#pragma once 

#include "../Core/String.hpp"
#include "../Threading/ExclusiveMutex.hpp"

namespace YAWN {
    class Console {
    public:
        static void Write(const wchar_t* format, ...);

        static void Write(const String& format, ...);

        static void WriteLine(const wchar_t* format, ...);

        static void WriteLine(const String& format, ...);

    private:
        static ExclusiveMutex sMutex;
    };
}
