#include <YAWN/Scene/UI/Section.hpp>

using namespace YAWN;

Section::Section() {
    SetPadding(Vector4(1.0f, 32.0f, 1.0f, 1.0f));
}

void Section::Enter() {
    Base::Enter();
}

void Section::Update(float timeStep) {
    Base::Update(timeStep);

    if (GetChildCount() > 0) {
        if (const Ref<Control> control = CastTo<Control>(GetChild(0)); control) {
            const Vector4& padding = GetPadding();
            const Vector2& size = GetLocalSize();

            control->SetLocalRectangle(
                Rectangle(
                    Vector2(padding.X, padding.Y),
                    Vector2(size.X - padding.X - padding.Z, size.Y - padding.Y - padding.W)
                )
            );
        }
    }
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
