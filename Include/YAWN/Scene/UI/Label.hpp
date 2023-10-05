#pragma once 

#include "Control.hpp"

namespace YAWN {
    class Label : public Control {
        YAWN_OBJECT(Label, Control);

    public:
        virtual ~Label() = default;

        virtual void Update(float timeStep) override;

        virtual void Draw() override;

        void SetText(const String& text);

        const String& GetText() const;

        void SetFontSize(int fontSize);

        int GetFontSize() const;

    private:
        String mText;
        int mFontSize = 16;
    };
}