#pragma once 

#include "Control.hpp"

namespace YAWN {
    class BoxContainer : public Control {
        YAWN_OBJECT(BoxContainer, Control);

    public:
        virtual ~BoxContainer() = default;

        virtual void Update(float timeStep) override;

        virtual void Draw() override;

        void SetVertical(bool vertical);

        bool IsVertical() const;

        void SetMargin(float margin);

        float GetMargin() const;

        void SetSplitter(bool splitter);

        bool IsSplitter() const;

    private:
        bool mVertical = false;
        bool mSplitter = false;
        float mMargin = 0.0f;

        int mSelectedSplitter = -1;
        Vector2 mLastMousePosition = Vector2::Zero;
    };
}