#pragma once 

#include "BoxContainer.hpp"

namespace YAWN {
    class MenuBar : public BoxContainer {
        YAWN_OBJECT(MenuBar, BoxContainer);

    public:
        virtual ~MenuBar() = default;

        virtual void Enter() override;

        virtual void Update(float timeStep) override;
    };
}