#pragma once 

#include "Container.hpp"

namespace YAWN {
    class BoxContainer : public Container {
        YAWN_OBJECT(BoxContainer, Container);

    public:
        BoxContainer();

        virtual ~BoxContainer() = default;

        virtual void Update(float timeStep) override;

        virtual void Draw() override;

        void SetVertical(bool vertical);

        bool IsVertical() const;

        void SetSplitter(bool splitter);

        bool IsSplitter() const;

    private:
        bool HasExpandedChild() const;

    private:
        bool mVertical = false;
        bool mSplitter = false;

        int mSelectedSplitter = -1;
        Vector2 mLastMousePosition = Vector2::Zero;
    };
}