#pragma once 

#include "WindowDriver.hpp"
#include "../Threading/ExclusiveMutex.hpp"

namespace YAWN {
    class Window {
    public:
        static void Initialize();

        static void Release();

        static void PollEvents();

        static bool IsOpen();

        static void SwapBuffers();

    private:
        static Ref<WindowDriver> sDriver;
        static ExclusiveMutex sMutex;
    };
}
