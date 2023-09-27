#pragma once 

#include "Container.hpp"

namespace YAWN {
    class WindowContainer : public Container {
        YAWN_OBJECT(WindowContainer, Container);

    public:
        virtual ~WindowContainer() = default;

        virtual void Enter() override;

        virtual void Update(float timeStep) override;

        virtual void Draw() override;

        virtual void HandleEvent(const Event& event) override;
    };
}