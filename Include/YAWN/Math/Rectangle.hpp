#pragma once 

#include "Vector2.hpp"

namespace YAWN {
    struct Rectangle {
        Rectangle() = default;

        constexpr Rectangle(float x, float y, float width, float height) : Position(x, y), Size(width, height) {}

        constexpr Rectangle(const Vector2& position, const Vector2& size) : Position(position), Size(size) {}

        constexpr bool Contains(const Vector2& point) const {
            return point.X >= Position.X && point.X < Position.X + Size.X &&
                point.Y >= Position.Y && point.Y < Position.Y + Size.Y;
        }

        inline Vector2 GetEnd() const {
            return Position + Size;
        }

        Vector2 Position;
        Vector2 Size;
    };
}
