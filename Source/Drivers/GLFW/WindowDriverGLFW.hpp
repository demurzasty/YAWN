#pragma once 

#include <YAWN/Platform/WindowDriver.hpp>

#ifdef _WIN32
#include <Windows.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#endif

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

namespace YAWN {
    class WindowDriverGLFW : public WindowDriver {
        YAWN_OBJECT(WindowDriverGLFW, WindowDriver);

    public:
        WindowDriverGLFW();

        ~WindowDriverGLFW() override;

        void PollEvents() override;

        bool IsOpen() const override;

        void SwapBuffers() override;

        void Invalidate() override;

        Vector2 GetSize() override;

        double GetTime() override;

    private:
        GLFWwindow* mWindow = nullptr;
    };
}
