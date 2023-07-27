#pragma once 

#include "Key.hpp"
#include "MouseButton.hpp"
#include "../Math/Vector2.hpp"

namespace YAWN {
    class Input {
    public:
        static void Initialize();

        static void Release();

        static void Refresh();

        static bool IsKeyDown(Key key);

        static bool IsKeyUp(Key key);

        static bool IsKeyPressed(Key key);

        static bool IsKeyReleased(Key key);

        static bool IsMouseButtonDown(MouseButton button);

        static bool IsMouseButtonUp(MouseButton button);

        static bool IsMouseButtonPressed(MouseButton button);

        static bool IsMouseButtonReleased(MouseButton button);

        static const Vector2& GetMousePosition();

        static void SetKeyState(Key key, bool state);

        static void SetMouseButtonState(MouseButton button, bool state);

        static void UpdateMousePosition(const Vector2& position);

    private:
        static bool sKeyStates[int(Key::Last)];
        static bool sLastKeyStates[int(Key::Last)];
        static bool sMouseButtonStates[int(MouseButton::Last)];
        static bool sLastMouseButtonStates[int(MouseButton::Last)];
        static Vector2 sMousePosition;
    };
}
