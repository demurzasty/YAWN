#include <YAWN/Platform/Window.hpp>

#include "../Drivers/GLFW/WindowDriverGLFW.hpp"

using namespace YAWN;

Ref<WindowDriver> Window::sDriver;
ExclusiveMutex Window::sMutex;

void Window::Initialize() {
    ExclusiveLock lock(sMutex);

    sDriver = new WindowDriverGLFW();
}

void Window::Release() {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);

    sDriver.Reset();
}

void Window::PollEvents() {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);

    sDriver->PollEvents();
}

bool Window::IsOpen() {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);

    return sDriver->IsOpen();
}

void Window::SwapBuffers() {
    ExclusiveLock lock(sMutex);

    YAWN_ASSERT(sDriver);

    sDriver->SwapBuffers();
}
