#include <YAWN/Scene/UI/Label.hpp>

using namespace YAWN;

void Label::Update(float timeStep) {
    Base::Update(timeStep);

    if (const Ref<Theme>& theme = GetTheme(); theme) {
        SetMinimumSize(theme->GetDefaultFont()->GetTextSize(GetText(), GetFontSize()));
    }
}

void Label::Draw() {
    Base::Draw();

    if (const Ref<Theme>& theme = GetTheme(); theme) {
        Rectangle rectangle = GetGlobalClientRectangle();
        Vector2 textSize = theme->GetDefaultFont()->GetTextSize(GetText(), GetFontSize());

        Vector2 position = rectangle.Position;
        position.Y += rectangle.Size.Y / 2.0f - textSize.Y / 2.0f;

        DrawText(theme->GetDefaultFont(), GetFontSize(), position, GetText(), Color::White);
    }
}

void Label::SetText(const String& text) {
    mText = text;

    RequestRedraw();
}

const String& Label::GetText() const {
    return mText;
}

void Label::SetFontSize(int fontSize) {
    mFontSize = fontSize;

    RequestRedraw();
}

int Label::GetFontSize() const {
    return mFontSize;
}
