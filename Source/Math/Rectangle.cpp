#include <YAWN/Math/Rectangle.hpp>
#include <YAWN/Math/Math.hpp>

using namespace YAWN;

Rectangle::Rectangle(float x, float y, float width, float height)
    : Position(x, y), Size(width, height) {
}

Rectangle::Rectangle(const Vector2& position, const Vector2& size)
    : Position(position), Size(size) {
}

bool Rectangle::Contains(const Rectangle& rect, const Vector2& point) {
    return point.X >= rect.Position.X && point.X < rect.Position.X + rect.Size.X &&
        point.Y >= rect.Position.Y && point.Y < rect.Position.Y + rect.Size.Y;
}

Rectangle Rectangle::Intersect(const Rectangle& rect1, const Rectangle& rect2) {
    const float x = Math::Max(rect1.Position.X, rect2.Position.X);
    const float y = Math::Max(rect1.Position.Y, rect2.Position.Y);

    const Vector2 myEnd = rect1.GetEnd();
    const Vector2 otherEnd = rect2.GetEnd();

    const float right = Math::Min(myEnd.X, otherEnd.X);
    const float bottom = Math::Min(myEnd.Y, otherEnd.Y);

    if (right > x && bottom > y) {
        return Rectangle(x, y, right - x, bottom - y);
    }

    return Rectangle(0.0f, 0.0f, 0.0f, 0.0f);
}

Vector2 Rectangle::GetEnd() const {
    return Position + Size;
}
