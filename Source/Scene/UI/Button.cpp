#include <YAWN/Scene/UI/Button.hpp>
#include <YAWN/Platform/Input.hpp>

using namespace YAWN;

void Button::Update(float timeStep) {
    Base::Update(timeStep);

    // TODO: Should be on event.
    CheckSize();

    const Vector2& mousePosition = Input::GetMousePosition();
    Rectangle globalRect = GetGlobalRectangle();

    if (globalRect.Contains(mousePosition)) {
        if (Input::IsMouseButtonPressed(MouseButton::Left)) {
                mState = ButtonState::Active;
        } 

        if (mState == ButtonState::Default) {
            mState = ButtonState::Hover;
        }
    } else {
        if (mState == ButtonState::Hover) {
            mState = ButtonState::Default;
        }
    }

    if (Input::IsMouseButtonReleased(MouseButton::Left)) {
        if (mState == ButtonState::Active) {
            mState = ButtonState::Default;
        }

        if (globalRect.Contains(mousePosition)) {

        }
    }
}

void Button::Draw() {
    Base::Draw();

    if (const Ref<Theme>& theme = GetTheme(); theme) {
        switch (mState) {
        case ButtonState::Default:
            DrawFillRect(GetGlobalRectangle(), theme->GetButtonDefaultColor());
            break;
        case ButtonState::Hover:
            DrawFillRect(GetGlobalRectangle(), theme->GetButtonHoverColor());
            break;
        case ButtonState::Active:
            DrawFillRect(GetGlobalRectangle(), theme->GetButtonActiveColor());
            break;
        }

        Vector2 textSize = theme->GetDefaultFont()->GetTextSize(GetText(), GetFontSize());

        DrawText(theme->GetDefaultFont(), GetFontSize(), GetGlobalPosition() + GetLocalSize() / 2.0f - textSize / 2.0f, GetText(), theme->GetButtonTextColor());
    }
}

void Button::SetText(const String& text) {
    mText = text;

    CheckSize();

    RequestRedraw();
}

const String& Button::GetText() const {
    return mText;
}

void Button::SetFontSize(int fontSize) {
    mFontSize = fontSize;

    CheckSize();

    RequestRedraw();
}

int Button::GetFontSize() const {
    return mFontSize;
}

void Button::CheckSize() {
    if (const Ref<Theme>& theme = GetTheme(); theme) {
        Vector2 size = GetLocalSize();
        Vector2 textSize = theme->GetDefaultFont()->GetTextSize(GetText(), GetFontSize());

        float padding = 8.0f;

        size.X = Math::Max(size.X, textSize.X + padding * 2.0f);
        size.Y = Math::Max(size.Y, textSize.Y);

        SetLocalSize(size);
    }
}
