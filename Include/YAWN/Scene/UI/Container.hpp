#pragma once 

#include "Control.hpp"

namespace YAWN {
    class Container : public Control {
        YAWN_OBJECT(Container, Control);

    public:
        virtual ~Container() = default;

        void SetMargin(float margin);

        float GetMargin() const;

    private:
        float mMargin = 0.0f;
    };
}