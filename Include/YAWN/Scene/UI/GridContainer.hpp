#pragma once 

#include "Container.hpp"

namespace YAWN {
    class GridContainer : public Container {
        YAWN_OBJECT(GridContainer, Container);

    public:
        virtual ~GridContainer() = default;

    private:
    };
}
