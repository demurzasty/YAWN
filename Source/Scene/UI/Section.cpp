#include <YAWN/Scene/UI/Section.hpp>

using namespace YAWN;

void Section::Enter() {
    Base::Enter();
}

void Section::Update(float timeStep) {
    Base::Update(timeStep);
}

void Section::Draw() {
    Base::Draw();

    if (const Ref<Theme> theme = GetTheme(); theme) {
        DrawFillRect(GetGlobalRectangle(), theme->GetContainerColor());

        Rectangle rect(GetGlobalPosition(), Vector2(GetLocalSize().X, 32.0f));
        DrawFillRect(rect, theme->GetSectionBarColor());

        Vector2 textSize = theme->GetDefaultFont()->GetTextSize(GetText(), 16);

        DrawText(theme->GetDefaultFont(), 16, GetGlobalPosition() + rect.Size / 2.0f - textSize / 2.0f, GetText(), theme->GetButtonTextColor());

        rect.Size.X = 4.0f;
        DrawFillRect(rect, theme->GetSectionIndicatorColor());

        DrawRect(GetGlobalRectangle(), theme->GetFrameBorderColor());
    }
}

void Section::SetText(const String& text) {
    mText = text;

    RequestRedraw();
}

const String& Section::GetText() const {
    return mText;
}
