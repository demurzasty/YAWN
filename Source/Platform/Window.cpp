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

    sDriver.Reset();
}

void Window::PollEvents() {
    ExclusiveLock lock(sMutex);

    sDriver->PollEvents();
}

bool Window::IsOpen() {
    ExclusiveLock lock(sMutex);

    return sDriver->IsOpen();
}

void Window::SwapBuffers() {
    ExclusiveLock lock(sMutex);

    sDriver->SwapBuffers();
}
