#pragma once 

#include "Vector2.hpp"

namespace YAWN {
    struct Rectangle {
        Rectangle() = default;

        Rectangle(float x, float y, float width, float height);

        Rectangle(const Vector2& position, const Vector2& size);

        static bool Contains(const Rectangle& rect, const Vector2& point);

        static Rectangle Intersect(const Rectangle& rect1, const Rectangle& rect2);

        Vector2 GetEnd() const;

        Vector2 Position;
        Vector2 Size;
    };
}
