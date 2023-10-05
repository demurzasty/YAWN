#pragma once 

#include "Control.hpp"
#include "../../Runtime/Signal.hpp"

namespace YAWN {
    class TextBox : public Control {
        YAWN_OBJECT(TextBox, Control);

    public:
        TextBox();

        virtual ~TextBox() = default;

        virtual void Update(float timeStep) override;

        virtual void HandleEvent(const Event& event) override;

        virtual void Draw() override;

        void SetText(const String& text);

        const String& GetText() const;

        void SetFontSize(int fontSize);

        int GetFontSize() const;

        Signal<const String&>& GetValueChangedSignal();

    private:
        String mText;
        int mFontSize = 16;
        float mCaretTime = 0.0f;
        Signal<const String&> mValueChangedSignal;
    };
}