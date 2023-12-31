#include "WindowDriverGLFW.hpp"

#include <YAWN/Runtime/Settings.hpp>
#include <YAWN/Platform/Input.hpp>
#include <YAWN/Graphics/Renderer.hpp>
#include <YAWN/Graphics/Image.hpp>
#include <YAWN/Scene/Scene.hpp>

#include "../../Graphics/BuiltIn/Icon.png.h"

using namespace YAWN;

static Key MapKey(int key) {
    YAWN_ASSUME(key >= GLFW_KEY_SPACE && key <= GLFW_KEY_LAST);
    switch (key) {
        case GLFW_KEY_SPACE: return Key::Space;
        case GLFW_KEY_APOSTROPHE: return Key::Apostrophe;
        case GLFW_KEY_COMMA: return Key::Comma;
        case GLFW_KEY_MINUS: return Key::Minus;
        case GLFW_KEY_PERIOD: return Key::Period;
        case GLFW_KEY_SLASH: return Key::Slash;
        case GLFW_KEY_0: return Key::Num0;
        case GLFW_KEY_1: return Key::Num1;
        case GLFW_KEY_2: return Key::Num2;
        case GLFW_KEY_3: return Key::Num3;
        case GLFW_KEY_4: return Key::Num4;
        case GLFW_KEY_5: return Key::Num5;
        case GLFW_KEY_6: return Key::Num6;
        case GLFW_KEY_7: return Key::Num7;
        case GLFW_KEY_8: return Key::Num8;
        case GLFW_KEY_9: return Key::Num9;
        case GLFW_KEY_SEMICOLON: return Key::Semicolon;
        case GLFW_KEY_EQUAL: return Key::Equal;
        case GLFW_KEY_A: return Key::A;
        case GLFW_KEY_B: return Key::B;
        case GLFW_KEY_C: return Key::C;
        case GLFW_KEY_D: return Key::D;
        case GLFW_KEY_E: return Key::E;
        case GLFW_KEY_F: return Key::F;
        case GLFW_KEY_G: return Key::G;
        case GLFW_KEY_H: return Key::H;
        case GLFW_KEY_I: return Key::I;
        case GLFW_KEY_J: return Key::J;
        case GLFW_KEY_K: return Key::K;
        case GLFW_KEY_L: return Key::L;
        case GLFW_KEY_M: return Key::M;
        case GLFW_KEY_N: return Key::N;
        case GLFW_KEY_O: return Key::O;
        case GLFW_KEY_P: return Key::P;
        case GLFW_KEY_Q: return Key::Q;
        case GLFW_KEY_R: return Key::R;
        case GLFW_KEY_S: return Key::S;
        case GLFW_KEY_T: return Key::T;
        case GLFW_KEY_U: return Key::U;
        case GLFW_KEY_V: return Key::V;
        case GLFW_KEY_W: return Key::W;
        case GLFW_KEY_X: return Key::X;
        case GLFW_KEY_Y: return Key::Y;
        case GLFW_KEY_Z: return Key::Z;
        case GLFW_KEY_LEFT_BRACKET: return Key::LeftBracket;
        case GLFW_KEY_BACKSLASH: return Key::Backslash;
        case GLFW_KEY_RIGHT_BRACKET: return Key::RightBracket;
        case GLFW_KEY_GRAVE_ACCENT: return Key::GraveAccent;
        case GLFW_KEY_WORLD_1: return Key::World1;
        case GLFW_KEY_WORLD_2: return Key::World2;
        case GLFW_KEY_ESCAPE: return Key::Escape;
        case GLFW_KEY_ENTER: return Key::Enter;
        case GLFW_KEY_TAB: return Key::Tab;
        case GLFW_KEY_BACKSPACE: return Key::Backspace;
        case GLFW_KEY_INSERT: return Key::Insert;
        case GLFW_KEY_DELETE: return Key::Delete;
        case GLFW_KEY_RIGHT: return Key::Right;
        case GLFW_KEY_LEFT: return Key::Left;
        case GLFW_KEY_DOWN: return Key::Down;
        case GLFW_KEY_UP: return Key::Up;
        case GLFW_KEY_PAGE_UP: return Key::PageUp;
        case GLFW_KEY_PAGE_DOWN: return Key::PageDown;
        case GLFW_KEY_HOME: return Key::Home;
        case GLFW_KEY_END: return Key::End;
        case GLFW_KEY_CAPS_LOCK: return Key::CapsLock;
        case GLFW_KEY_SCROLL_LOCK: return Key::ScrollLock;
        case GLFW_KEY_NUM_LOCK: return Key::NumLock;
        case GLFW_KEY_PRINT_SCREEN: return Key::PrintScreen;
        case GLFW_KEY_PAUSE: return Key::Pause;
        case GLFW_KEY_F1: return Key::F1;
        case GLFW_KEY_F2: return Key::F2;
        case GLFW_KEY_F3: return Key::F3;
        case GLFW_KEY_F4: return Key::F4;
        case GLFW_KEY_F5: return Key::F5;
        case GLFW_KEY_F6: return Key::F6;
        case GLFW_KEY_F7: return Key::F7;
        case GLFW_KEY_F8: return Key::F8;
        case GLFW_KEY_F9: return Key::F9;
        case GLFW_KEY_F10: return Key::F10;
        case GLFW_KEY_F11: return Key::F11;
        case GLFW_KEY_F12: return Key::F12;
        case GLFW_KEY_F13: return Key::F13;
        case GLFW_KEY_F14: return Key::F14;
        case GLFW_KEY_F15: return Key::F15;
        case GLFW_KEY_F16: return Key::F16;
        case GLFW_KEY_F17: return Key::F17;
        case GLFW_KEY_F18: return Key::F18;
        case GLFW_KEY_F19: return Key::F19;
        case GLFW_KEY_F20: return Key::F20;
        case GLFW_KEY_F21: return Key::F21;
        case GLFW_KEY_F22: return Key::F22;
        case GLFW_KEY_F23: return Key::F23;
        case GLFW_KEY_F24: return Key::F24;
        case GLFW_KEY_F25: return Key::F25;
        case GLFW_KEY_KP_0: return Key::NumPad0;
        case GLFW_KEY_KP_1: return Key::NumPad1;
        case GLFW_KEY_KP_2: return Key::NumPad2;
        case GLFW_KEY_KP_3: return Key::NumPad3;
        case GLFW_KEY_KP_4: return Key::NumPad4;
        case GLFW_KEY_KP_5: return Key::NumPad5;
        case GLFW_KEY_KP_6: return Key::NumPad6;
        case GLFW_KEY_KP_7: return Key::NumPad7;
        case GLFW_KEY_KP_8: return Key::NumPad8;
        case GLFW_KEY_KP_9: return Key::NumPad9;
        case GLFW_KEY_KP_DECIMAL: return Key::NumPadDecimal;
        case GLFW_KEY_KP_DIVIDE: return Key::NumPadDivide;
        case GLFW_KEY_KP_MULTIPLY: return Key::NumPadMultiply;
        case GLFW_KEY_KP_SUBTRACT: return Key::NumPadSubtract;
        case GLFW_KEY_KP_ADD: return Key::NumPadAdd;
        case GLFW_KEY_KP_ENTER: return Key::NumPadEnter;
        case GLFW_KEY_KP_EQUAL: return Key::NumPadEqual;
        case GLFW_KEY_LEFT_SHIFT: return Key::LeftShift;
        case GLFW_KEY_LEFT_CONTROL: return Key::LeftControl;
        case GLFW_KEY_LEFT_ALT: return Key::LeftAlt;
        case GLFW_KEY_LEFT_SUPER: return Key::LeftSuper;
        case GLFW_KEY_RIGHT_SHIFT: return Key::RightShift;
        case GLFW_KEY_RIGHT_CONTROL: return Key::RightControl;
        case GLFW_KEY_RIGHT_ALT: return Key::RightAlt;
        case GLFW_KEY_RIGHT_SUPER: return Key::RightSuper;
        case GLFW_KEY_MENU: return Key::Menu;
    }

    return Key::Last;
}

static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    Key mappedKey = MapKey(key);
    if (mappedKey != Key::Last) {
        Input::SetKeyState(mappedKey, action != GLFW_RELEASE);
    }

    if (action != GLFW_RELEASE) {
        Scene::HandleEvent(KeyDownEvent(mappedKey));
    } else {
        Scene::HandleEvent(KeyUpEvent(mappedKey));
    }
}

static MouseButton MapMouseButton(int mouseButton) {
    switch (mouseButton) {
        case GLFW_MOUSE_BUTTON_LEFT: return MouseButton::Left;
        case GLFW_MOUSE_BUTTON_MIDDLE: return MouseButton::Middle;
        case GLFW_MOUSE_BUTTON_RIGHT: return MouseButton::Right;
    }

    return MouseButton::Last;
}

static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    MouseButton mappedButton = MapMouseButton(button);
    if (mappedButton != MouseButton::Last) {
        Input::SetMouseButtonState(mappedButton, action == GLFW_PRESS);
    }

    double x, y;
    glfwGetCursorPos(window, &x, &y);

    Vector2 position = Vector2(float(x), float(y));
    if (action == GLFW_PRESS) {
        Scene::HandleEvent(MouseButtonDownEvent(position, mappedButton));
    } else {
        Scene::HandleEvent(MouseButtonUpEvent(position, mappedButton));
    }
}

static void CursorPositionCallback(GLFWwindow* window, double x, double y) {
    Vector2 position = Vector2(Vector2(float(x), float(y)));

    Input::UpdateMousePosition(position);

    Scene::HandleEvent(MouseMoveEvent(position));
}

static void FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
    Vector2 size = Vector2(float(width), float(height));

    Renderer::SetFramebufferSize(size);

    Scene::HandleEvent(WindowResizeEvent(size));
}

static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    (void)xoffset;

    Input::SetMouseWheel(float(yoffset));

    Scene::HandleEvent(MouseWheelEvent(float(yoffset)));
}

static void TextInputCallback(GLFWwindow* window, unsigned int codepoint) {
    wchar_t text[2] = {
        (wchar_t)codepoint,
        0
    };

    Scene::HandleEvent(TextInputEvent(text));
}

WindowDriverGLFW::WindowDriverGLFW() {
    glfwInit();

    glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

    mWindow = glfwCreateWindow(Settings::GetWindowWidth(), Settings::GetWindowHeight(), Settings::GetWindowTitle().ToUTF8().GetData(), nullptr, nullptr);

    glfwSetKeyCallback(mWindow, &KeyCallback);
    glfwSetMouseButtonCallback(mWindow, &MouseButtonCallback);
    glfwSetCursorPosCallback(mWindow, &CursorPositionCallback);
    glfwSetFramebufferSizeCallback(mWindow, &FramebufferSizeCallback);
    glfwSetScrollCallback(mWindow, &ScrollCallback);
    glfwSetCharCallback(mWindow, &TextInputCallback);

    Ref<Image> icon = Image::FromMemory(IconPNG, 4);

    GLFWimage image = GLFWimage();
    image.pixels = icon->GetData().GetData();
    image.width = icon->GetInfo().GetWidth();
    image.height = icon->GetInfo().GetHeight();
    glfwSetWindowIcon(mWindow, 1, &image);

#ifdef _WIN32
    {
        HWND hwnd = glfwGetWin32Window(mWindow);
        HDC hdc = GetDC(hwnd);

        HBRUSH blackBrush = CreateSolidBrush(RGB(0, 0, 0));

        RECT rect;
        GetClientRect(hwnd, &rect);
        FillRect(hdc, &rect, blackBrush);

        DeleteObject(blackBrush);

        ArrayView<Color4> pixels((Color4*)image.pixels, image.width * image.height);
        for (Color4& pixel : pixels) {
            unsigned char r = pixel.R;
            pixel.R = pixel.B;
            pixel.B = r;

            pixel = Color::Lerp(pixel, Color::Black, 1.0f - pixel.A / 255.0f);
        }

        HBITMAP hBitmap = (HBITMAP)CreateBitmap(image.width, image.height, 1, 32, pixels.GetData());
        {
            PAINTSTRUCT     ps;
            HDC             hdc;
            BITMAP          bitmap;
            HDC             hdcMem;
            HGDIOBJ         oldBitmap;

            hdc = BeginPaint(hwnd, &ps);

            hdcMem = CreateCompatibleDC(hdc);
            oldBitmap = SelectObject(hdcMem, hBitmap);

            GetObject(hBitmap, sizeof(bitmap), &bitmap);
            BitBlt(hdc, rect.right / 2 - image.width / 2, rect.bottom / 2 - image.height / 2, bitmap.bmWidth, bitmap.bmHeight, hdcMem, 0, 0, SRCCOPY);

            SelectObject(hdcMem, oldBitmap);
            DeleteDC(hdcMem);

            EndPaint(hwnd, &ps);
        }
        DeleteObject(hBitmap);

        ReleaseDC(hwnd, hdc);
    }
#endif

    glfwMakeContextCurrent(mWindow);

    glfwSwapInterval(0);

    glewInit();
}

WindowDriverGLFW::~WindowDriverGLFW() {
    glfwDestroyWindow(mWindow);
    glfwTerminate();
}

void WindowDriverGLFW::PollEvents() {
    glfwPollEvents();
}

bool WindowDriverGLFW::IsOpen() const {
    return !glfwWindowShouldClose(mWindow);
}

void WindowDriverGLFW::SwapBuffers() {
    glfwSwapBuffers(mWindow);
}

void WindowDriverGLFW::Invalidate() {
    glfwPostEmptyEvent();
}

Vector2 WindowDriverGLFW::GetSize() {
    int width, height;
    glfwGetWindowSize(mWindow, &width, &height);
    return Vector2(float(width), float(height));
}

double WindowDriverGLFW::GetTime() {
    return glfwGetTime();
}
