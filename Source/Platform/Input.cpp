#include <YAWN/Platform/Input.hpp>
#include <YAWN/Core/Memory.hpp>

using namespace YAWN;

bool Input::sKeyStates[int(Key::Last)];
bool Input::sLastKeyStates[int(Key::Last)];
bool Input::sMouseButtonStates[int(MouseButton::Last)];
bool Input::sLastMouseButtonStates[int(MouseButton::Last)];
Vector2 Input::sMousePosition = Vector2::Zero;
float Input::sMouseWheel = 0.0f;

void Input::Initialize() {
    for (bool& value : sKeyStates) {
        value = false;
    }

    for (bool& value : sLastKeyStates) {
        value = false;
    }

    for (bool& value : sMouseButtonStates) {
        value = false;
    }

    for (bool& value : sLastMouseButtonStates) {
        value = false;
    }
}

void Input::Release() {
}

void Input::Refresh() {
    Memory::Copy(sLastKeyStates, sKeyStates, sizeof(sKeyStates));
    Memory::Copy(sLastMouseButtonStates, sMouseButtonStates, sizeof(sMouseButtonStates));
}

bool Input::IsKeyDown(Key key) {
    return sKeyStates[int(key)];
}

bool Input::IsKeyUp(Key key) {
    return !sKeyStates[int(key)];
}

bool Input::IsKeyPressed(Key key) {
    return sKeyStates[int(key)] && !sLastKeyStates[int(key)];
}

bool Input::IsKeyReleased(Key key) {
    return !sKeyStates[int(key)] && sLastKeyStates[int(key)];
}

bool Input::IsMouseButtonDown(MouseButton button) {
    return sMouseButtonStates[int(button)];
}

bool Input::IsMouseButtonUp(MouseButton button) {
    return !sMouseButtonStates[int(button)];
}

bool Input::IsMouseButtonPressed(MouseButton button) {
    return sMouseButtonStates[int(button)] && !sLastMouseButtonStates[int(button)];
}

bool Input::IsMouseButtonReleased(MouseButton button) {
    return !sMouseButtonStates[int(button)] && sLastMouseButtonStates[int(button)];
}

const Vector2& Input::GetMousePosition() {
    return sMousePosition;
}

void Input::SetKeyState(Key key, bool state) {
    sKeyStates[int(key)] = state;
}

void Input::SetMouseButtonState(MouseButton button, bool state) {
    sMouseButtonStates[int(button)] = state;
}

void Input::SetMouseWheel(float wheel) {
    sMouseWheel = wheel;
}

float Input::GetMouseWheel() {
    return sMouseWheel;
}

void Input::UpdateMousePosition(const Vector2& position) {
    sMousePosition = position;
}
