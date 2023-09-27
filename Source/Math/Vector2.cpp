#include <YAWN/Math/Vector2.hpp>
#include <YAWN/Core/Assert.hpp>

using namespace YAWN;

const Vector2 Vector2::Zero = Vector2(0.0f, 0.0f);

const Vector2 Vector2::One = Vector2(1.0f, 1.0f);

float Vector2::Dot(const Vector2& lhs, const Vector2& rhs) {
    return lhs.X * rhs.X + lhs.Y * rhs.Y;
}

float Vector2::Length(const Vector2& vec) {
    return Math::Sqrt(Dot(vec, vec));
}

float Vector2::Distance(const Vector2& lhs, const Vector2& rhs) {
    return Length(rhs - lhs);
}

Vector2 Vector2::Normalize(const Vector2& vec) {
    const float length = Length(vec);
    return Vector2(vec.X / length, vec.Y / length);
}

bool Vector2::AlmostEquals(const Vector2& lhs, const Vector2& rhs) {
    return Math::AlmostEquals(lhs.X, rhs.X) &&
        Math::AlmostEquals(lhs.Y, rhs.Y);
}

Vector2 Vector2::Min(const Vector2& lhs, const Vector2& rhs) {
    return Vector2(Math::Min(lhs.X, rhs.X), Math::Min(lhs.Y, rhs.Y));
}

Vector2 Vector2::Max(const Vector2& lhs, const Vector2& rhs) {
    return Vector2(Math::Max(lhs.X, rhs.X), Math::Max(lhs.Y, rhs.Y));
}

Vector2 Vector2::Floor(const Vector2& vec) {
    return Vector2(Math::Floor(vec.X), Math::Floor(vec.Y));
}

Vector2 Vector2::Ceil(const Vector2& vec) {
    return Vector2(Math::Ceil(vec.X), Math::Floor(vec.Y));
}

Vector2 Vector2::Round(const Vector2& vec) {
    return Vector2(Math::Round(vec.X), Math::Floor(vec.Y));
}

Vector2 Vector2::operator+(const Vector2& rhs) const {
    return Vector2(X + rhs.X, Y + rhs.Y);
}

Vector2 Vector2::operator-(const Vector2& rhs) const {
    return Vector2(X - rhs.X, Y - rhs.Y);
}

Vector2 Vector2::operator*(const Vector2& rhs) const {
    return Vector2(X * rhs.X, Y * rhs.Y);
}

Vector2 Vector2::operator/(const Vector2& rhs) const {
    return Vector2(X / rhs.X, Y / rhs.Y);
}

Vector2& Vector2::operator+=(const Vector2& rhs) {
    X += rhs.X; Y += rhs.Y;
    return *this;
}

Vector2& Vector2::operator-=(const Vector2& rhs) {
    X -= rhs.X; Y -= rhs.Y;
    return *this;
}

Vector2& Vector2::operator*=(const Vector2& rhs) {
    X *= rhs.X; Y *= rhs.Y;
    return *this;
}

Vector2& Vector2::operator/=(const Vector2& rhs) {
    X /= rhs.X; Y /= rhs.Y;
    return *this;
}

float& Vector2::operator[](int index) {
    YAWN_ASSERT(index < 2);
    return (&X)[index];
}

float Vector2::operator[](int index) const {
    YAWN_ASSERT(index < 2);
    return (&X)[index];
}