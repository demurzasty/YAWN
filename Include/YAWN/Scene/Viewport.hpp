#pragma once 

#include "Node.hpp"
#include "../Runtime/Pool.hpp"

namespace YAWN {
    class Viewport : public Node {
        YAWN_OBJECT(Viewport, Node);

    public:
        virtual ~Viewport() = default;

        virtual void Enter() override;

        virtual void Exit() override;

        virtual void Update(float timeStep) override;

        void SetSize(const Vector2& size);

        const Vector2& GetSize() const;

        void SetRenderDirectToScreen(bool directToScreen);

        bool IsRenderDirectToScreen() const;

        int GetId() const;

    private:
        int mViewportId = Pool::None;
        bool mDirectToScreen = false;
        Vector2 mSize = Vector2(512.0f, 512.0f);
        bool mDirty = true;
    };
}
