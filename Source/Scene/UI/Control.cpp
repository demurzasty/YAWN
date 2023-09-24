#include <YAWN/Scene/UI/Control.hpp>
#include <YAWN/Graphics/Renderer.hpp>
#include <YAWN/Runtime/ResourceManager.hpp>

using namespace YAWN;

void Control::Enter() {
    Base::Enter();

    mFont = ResourceManager::Load<Font>(Guid(L"f77df380-4ce3-ab24-9ba6-ef80efd64a73"));
}

void Control::Draw() {
    Base::Draw();

    Vector2 globalPosition = GetGlobalPosition();
    Vector2 size = GetLocalSize();

    mFont->GetGlyph(L'A', 16);
    mFont->GetGlyph(L'b', 16);
    mFont->GetGlyph(L'C', 16);
    mFont->GetGlyph(L'D', 16);
    mFont->GetGlyph(L'E', 16);
    mFont->GetGlyph(L'F', 16);
    mFont->GetGlyph(L'G', 16);

    //DrawTexture(Renderer::GetWhiteTexture(), GetGlobalRectangle(), Rectangle(0.0f, 0.0f, 4.0f, 4.0f), GetBackgroundColor());

    // DrawTexture(mFont->GetTextureId(), GetGlobalRectangle(), Rectangle(0.0f, 0.0f, 512.0f, 512.0f), Color::White);

    DrawText(mFont, GetGlobalPosition(), L"Lorem ipsum dolor sit amet.", Color::White);
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
