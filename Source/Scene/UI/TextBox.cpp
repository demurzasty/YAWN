#include <YAWN/Scene/UI/TextBox.hpp>
#include <YAWN/Platform/Input.hpp>
#include <YAWN/Platform/Window.hpp>

using namespace YAWN;

TextBox::TextBox() {
    SetPadding(8.0f);
    SetMinimumSize(32.0f);
}

void TextBox::Update(float timeStep) {
    Base::Update(timeStep);

    if (HasFocus()) {
        mCaretTime += timeStep;

        // TODO: Use fmod.
        while (mCaretTime > 1.0f) {
            mCaretTime -= 1.0f;
        }

        Window::Invalidate();
    }
}

void TextBox::HandleEvent(const Event& event) {
    Base::HandleEvent(event);

    if (event.Type == EventType::MouseButtonDown) {
        if (Rectangle::Contains(GetGlobalRectangle(), Input::GetMousePosition())) {
            GrabFocus();

            Window::Invalidate();

            mCaretTime = 0.0f;

            event.Consume();
        } else if (HasFocus()) {
            LoseFocus();
        }
    } else if (event.Type == EventType::TextInput) {
        if (HasFocus()) {
            const TextInputEvent& textInput = (const TextInputEvent&)event;

            mText = mText + textInput.TextInput;
            mCaretTime = 0.0f;

            mValueChangedSignal.Emit(mText);
        }
    } else if (event.Type == EventType::KeyDown) {
        if (HasFocus()) {
            const KeyDownEvent& keyDown = (const KeyDownEvent&)event;
            if (keyDown.Key == Key::Backspace) {
                if (mText.GetSize() > 0) {
                    mText = mText.Substring(0, mText.GetSize() - 1);

                    mValueChangedSignal.Emit(mText);
                }
                mCaretTime = 0.0f;
            }
        }
    }
}

void TextBox::Draw() {
    Base::Draw();

    if (const Ref<Theme>& theme = GetTheme(); theme) {
        DrawFillRect(GetGlobalRectangle(), theme->GetButtonActiveColor());

        Rectangle clientRectangle = GetGlobalClientRectangle();

        Vector2 textSize = theme->GetDefaultFont()->GetTextSize(mText, GetFontSize());

        Vector2 textPosition = clientRectangle.Position;
        textPosition.Y += clientRectangle.Size.Y / 2.0f - textSize.Y / 2.0f;

        DrawText(theme->GetDefaultFont(), GetFontSize(), textPosition, GetText(), Color::White);

        if (HasFocus() && mCaretTime < 0.5f) {
            Vector2 caretPosition = textPosition;
            caretPosition.X += textSize.X + 1.0f;

            DrawLine(caretPosition, caretPosition + Vector2(0.0f, textSize.Y), Color::White);
        }

        if (HasFocus()) {
            DrawRect(GetGlobalRectangle(), theme->GetTextBoxBorderColor());
        } else {
            DrawRect(GetGlobalRectangle(), theme->GetButtonHoverColor());
        
        }
    }
}

void TextBox::SetText(const String& text) {
    mText = text;

    RequestRedraw();
}

const String& TextBox::GetText() const {
    return mText;
}

void TextBox::SetFontSize(int fontSize) {
    mFontSize = fontSize;

    RequestRedraw();
}

int TextBox::GetFontSize() const {
    return mFontSize;
}

Signal<const String&>& TextBox::GetValueChangedSignal() {
    return mValueChangedSignal;
}
