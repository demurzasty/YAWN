#include <YAWN/Math/Rectangle.hpp>
#include <YAWN/Math/Math.hpp>

using namespace YAWN;

Rectangle Rectangle::Intersect(const Rectangle& rect) const {
    const float x = Math::Max(Position.X, rect.Position.X);
    const float y = Math::Max(Position.Y, rect.Position.Y);

    const Vector2 myEnd = GetEnd();
    const Vector2 otherEnd = rect.GetEnd();

    const float right = Math::Min(myEnd.X, otherEnd.X);
    const float bottom = Math::Min(myEnd.Y, otherEnd.Y);

    if (right > x && bottom > y) {
        return Rectangle(x, y, right - x, bottom - y);
    }

    return Rectangle(0.0f, 0.0f, 0.0f, 0.0f);
}
