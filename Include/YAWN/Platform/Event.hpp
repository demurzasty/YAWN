#pragma once 

#include "Key.hpp"
#include "MouseButton.hpp"
#include "../Math/Vector2.hpp"

namespace YAWN {
    enum class EventType : unsigned char {
        None,
        KeyDown,
        KeyUp,
        MouseMove,
        MouseButtonDown,
        MouseButtonUp,
        MouseWheel,
        WindowResize,
        TextInput
    };

    struct Event {
        constexpr Event() = default;

        constexpr Event(EventType type) : Type(type) { }

        constexpr void Consume() const { mConsumed = true; }

        constexpr bool IsConsumed() const { return mConsumed; }

        EventType Type = EventType::None;

    private:
        mutable bool mConsumed = false;
    };

    struct KeyDownEvent : public Event {
        constexpr KeyDownEvent(Key key) : Event(EventType::KeyDown), Key(key) {}

        Key Key;
    };

    struct KeyUpEvent : public Event {
        constexpr KeyUpEvent(Key key) : Event(EventType::KeyUp), Key(key) {}

        Key Key;
    };

    struct MouseMoveEvent : public Event {
        constexpr MouseMoveEvent(Vector2 position) : Event(EventType::MouseMove), Position(position) {}

        Vector2 Position;
    };

    struct MouseButtonDownEvent : public Event {
        constexpr MouseButtonDownEvent(Vector2 position, MouseButton button) : Event(EventType::MouseButtonDown), Position(position), Button(button) {}

        MouseButton Button;
        Vector2 Position;
    };

    struct MouseButtonUpEvent : public Event {
        constexpr MouseButtonUpEvent(Vector2 position, MouseButton button) : Event(EventType::MouseButtonUp), Position(position), Button(button) {}

        MouseButton Button;
        Vector2 Position;
    };

    struct MouseWheelEvent : public Event {
        constexpr MouseWheelEvent(float wheel) : Event(EventType::MouseWheel), Wheel(wheel) {}

        float Wheel;
    };

    struct WindowResizeEvent : public Event {
        constexpr WindowResizeEvent(Vector2 size) : Event(EventType::WindowResize), Size(size) {}

        Vector2 Size;
    };

    struct TextInputEvent : public Event {
        TextInputEvent(const String& textInput) : Event(EventType::TextInput), TextInput(textInput) {}

        String TextInput;
    };
}
