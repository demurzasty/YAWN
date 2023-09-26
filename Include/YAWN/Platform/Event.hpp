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
        WindowResize,
    };

    struct Event {
        EventType Type = EventType::None;

        constexpr Event() = default;

        constexpr Event(EventType type) : Type(type) { }
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

    struct WindowResizeEvent : public Event {
        constexpr WindowResizeEvent(Vector2 size) : Event(EventType::WindowResize), Size(size) {}

        Vector2 Size;
    };
}
