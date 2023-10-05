#pragma once 

#include "Container.hpp"

namespace YAWN {
    class GridContainer : public Container {
        YAWN_OBJECT(GridContainer, Container);

    public:
        GridContainer();

        virtual ~GridContainer() = default;

        virtual void Update(float timeStep) override;

        void SetCellSize(const Vector2& cellSize);

        const Vector2& GetCellSize() const;

    private:
        Vector2 mCellSize = Vector2(64.0f, 64.0f);
    };
}
