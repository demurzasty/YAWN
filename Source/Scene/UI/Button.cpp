#include <YAWN/Scene/UI/Button.hpp>
#include <YAWN/Platform/Input.hpp>

using namespace YAWN;

void Button::Update(float timeStep) {
    Base::Update(timeStep);

    if (IsVisible()) {
        // TODO: Should be on event.
        CheckSize();

        const Vector2& mousePosition = Input::GetMousePosition();
        Rectangle globalRect = GetGlobalRectangle();

        if (Rectangle::Contains(globalRect, mousePosition)) {
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

                if (Rectangle::Contains(globalRect, mousePosition)) {
                    GetClickedSignal().Emit(this);

                    mState = ButtonState::Hover;
                } else {
                    mState = ButtonState::Default;
                }
            }
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

void Button::SetIconTexture(const Ref<Texture>& texture) {
    mIconTexture = texture;
}

const Ref<Texture> Button::GetIconTexture() const {
    return mIconTexture;
}

void Button::SetIconSourceRectangle(const Rectangle& source) {
    mIconSourceRectangle = source;
}

const Rectangle& Button::GetIconSourceRectangle() const {
    return mIconSourceRectangle;
}

Signal<Ref<Button>>& Button::GetClickedSignal() {
    return mClickedSignal;
}

void Button::CheckSize() {
    if (const Ref<Theme>& theme = GetTheme(); theme) {
        Vector2 size = GetLocalSize();
        Vector2 textSize = theme->GetDefaultFont()->GetTextSize(GetText(), GetFontSize());

        float padding = 8.0f;
        
        float margin = mIconTexture ? 16.0f : 0.0f;

        size.X = Math::Max(size.X, textSize.X + padding * 2.0f + margin);
        size.Y = Math::Max(size.Y, textSize.Y);

        SetMinimumSize(size);
    }
}
