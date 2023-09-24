#include <YAWN/Scene/UI/Control.hpp>
#include <YAWN/Graphics/Renderer.hpp>

using namespace YAWN;

void Control::Draw() {
    Base::Draw();

    Vector2 globalPosition = GetGlobalPosition();
    Vector2 size = GetLocalSize();

    Vertex2D vertices[4] = {
        Vertex2D(globalPosition, Vector2(0.0f, 0.0f), mBackgroundColor),
        Vertex2D(globalPosition + Vector2(0.0f, size.Y), Vector2(0.0f, 1.0f), mBackgroundColor),
        Vertex2D(globalPosition + Vector2(size.X, size.Y), Vector2(1.0f, 1.0f), mBackgroundColor),
        Vertex2D(globalPosition + Vector2(size.X, 0.0f), Vector2(1.0f, 0.0f), mBackgroundColor),
    };

    unsigned short indices[6] = {
        0, 1, 2,
        2, 3, 0
    };

    Renderer::LLSetTexture2D(Renderer::GetWhiteTexture());

    Renderer::LLSetVertexBufferData2D(vertices);
    Renderer::LLSetIndexBufferData2D(indices);

    Renderer::LLDraw2D(0, 0, 6);
}

void Control::SetLocalSize(const Vector2& size) {
    mLocalSize = size;
}

const Vector2& Control::GetLocalSize() const {
    return mLocalSize;
}

void Control::SetLocalRectangle(const Rectangle& rectangle) {
    SetLocalPosition(rectangle.GetPosition());
    SetLocalSize(rectangle.GetSize());
}

Rectangle Control::GetLocalRectangle() const {
    return Rectangle(GetLocalPosition(), GetLocalSize());
}

Rectangle Control::GetGlobalRectangle() const {
    return Rectangle(GetGlobalPosition(), GetLocalSize());
}

void Control::SetBackgroundColor(const Color4& color) {
    mBackgroundColor = color;
}

const Color4& Control::GetBackgroundColor() const {
    return mBackgroundColor;
}
