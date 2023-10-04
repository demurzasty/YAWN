#pragma once 

#include "Control.hpp"

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

    private:
        String mText;
        float mCaretTime = 0.0f;
    };
}