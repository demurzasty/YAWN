#pragma once 

#include "Control.hpp"

namespace YAWN {
    class Section : public Control {
        YAWN_OBJECT(Section, Control);

    public:
        virtual ~Section() = default;

        virtual void Enter() override;

        virtual void Update(float timeStep) override;

        virtual void Draw() override;

        void SetText(const String& text);

        const String& GetText() const;

    private:
        String mText;
    };
}