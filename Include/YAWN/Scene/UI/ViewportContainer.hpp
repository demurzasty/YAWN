#pragma once 

#include "Container.hpp"

namespace YAWN {
    class ViewportContainer : public Container {
        YAWN_OBJECT(ViewportContainer, Container);

    public:
        virtual ~ViewportContainer() = default;

        virtual void Enter() override;

        virtual void Update(float timeStep) override;

        virtual void Draw() override;

        virtual void HandleEvent(const Event& event) override;
    };
}