#pragma once 

#include "Control.hpp"

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

    private:
        void CheckSize();

    private:
        String mText;
        int mFontSize = 16;
        ButtonState mState = ButtonState::Default;
    };
}