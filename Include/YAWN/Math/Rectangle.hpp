#pragma once 

#include "Vector2.hpp"

namespace YAWN {
    struct Rectangle {
        Rectangle() = default;

        constexpr Rectangle(float left, float top, float width, float height) : Left(left), Top(top), Width(width), Height(height) {}

        constexpr Rectangle(const Vector2& position, const Vector2& size) : Left(position.X), Top(position.Y), Width(size.X), Height(size.Y) {}

        constexpr bool Contains(const Vector2& point) const {
            return point.X >= Left && point.X < Left + Width &&
                point.Y >= Top && point.Y < Top + Height;
        }

        constexpr float GetRight() const {
            return Left + Width;
        }

        constexpr float GetBottom() const {
            return Top + Height;
        }

        constexpr void SetPosition(const Vector2& position) {
            Left = position.X;
            Top = position.Y;
        }

        Vector2 GetPosition() const {
            return Vector2(Left, Top);
        }

        constexpr void SetSize(const Vector2& size) {
            Width = size.X;
            Height = size.Y;
        }

        Vector2 GetSize() const {
            return Vector2(Width, Height);
        }

        float Left, Top, Width, Height;
    };
}
