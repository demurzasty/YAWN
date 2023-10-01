#pragma once 

#include <YAWN/Platform/WindowDriver.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace YAWN {
    class WindowDriverGLFW : public WindowDriver {
        YAWN_OBJECT(WindowDriverGLFW, WindowDriver);

    public:
        WindowDriverGLFW();

        ~WindowDriverGLFW() override;

        void PollEvents() override;

        bool IsOpen() const override;

        void SwapBuffers() override;

        Vector2 GetSize() override;

        double GetTime() override;

    private:
        GLFWwindow* mWindow = nullptr;
    };
}
