#pragma once 

#include "Control.hpp"
#include "../../Runtime/Signal.hpp"

namespace YAWN {
    enum class ButtonState {
        Default,
        Hover,
        Active
    };

    class Button : public Control {
        YAWN_OBJECT(Button, Control);

    public:
        virtual ~Button() = default;

        virtual void Update(float timeStep) override;

        virtual void Draw() override;

        void SetText(const String& text);

        const String& GetText() const;

        void SetFontSize(int fontSize);

        int GetFontSize() const;

        void SetIconTexture(const Ref<Texture>& texture);

        const Ref<Texture> GetIconTexture() const;

        void SetIconSourceRectangle(const Rectangle& source);

        const Rectangle& GetIconSourceRectangle() const;

        Signal<Ref<Button>>& GetClickedSignal();

    private:
        void CheckSize();

    private:
        String mText;
        int mFontSize = 16;
        ButtonState mState = ButtonState::Default;
        Ref<Texture> mIconTexture;
        Rectangle mIconSourceRectangle = Rectangle(0.0f, 0.0f, 0.0f, 0.0f);
        Signal<Ref<Button>> mClickedSignal;
    };
}