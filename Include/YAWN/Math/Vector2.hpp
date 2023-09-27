#pragma once

#include "Math.hpp"

namespace YAWN {
    struct Vector2 {
        static const Vector2 Zero;

        static const Vector2 One;

        static float Dot(const Vector2& lhs, const Vector2& rhs);

        static float Length(const Vector2& vec);

        static float Distance(const Vector2& lhs, const Vector2& rhs);

        static Vector2 Normalize(const Vector2& vec);

        static bool AlmostEquals(const Vector2& lhs, const Vector2& rhs);

        static Vector2 Min(const Vector2& lhs, const Vector2& rhs);
        
        static Vector2 Max(const Vector2& lhs, const Vector2& rhs);

        static Vector2 Floor(const Vector2& vec);

        static Vector2 Ceil(const Vector2& vec);

        static Vector2 Round(const Vector2& vec);

        Vector2() = default;

        constexpr Vector2(float value)
            : X(value), Y(value) {
        }

        constexpr Vector2(float x, float y)
            : X(x), Y(y) {
        }

        Vector2 operator+(const Vector2& rhs) const;

        Vector2 operator-(const Vector2& rhs) const;

        Vector2 operator*(const Vector2& rhs) const;

        Vector2 operator/(const Vector2& rhs) const;

        Vector2& operator+=(const Vector2& rhs);

        Vector2& operator-=(const Vector2& rhs);

        Vector2& operator*=(const Vector2& rhs);

        Vector2& operator/=(const Vector2& rhs);

        float& operator[](int index);

        float operator[](int index) const;

        float X, Y;
    };
}