#pragma once 

#include "BoxContainer.hpp"

namespace YAWN {
    class Popup : public BoxContainer {
        YAWN_OBJECT(Popup, BoxContainer);

    public:
        virtual ~Popup() = default;

        virtual void HandleEvent(const Event& event) override;

        virtual void Draw() override;
    };
}
