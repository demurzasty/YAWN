#pragma once 

#include "Resource.hpp"

namespace YAWN {
    class Prefab : public Resource {
        YAWN_OBJECT(Prefab, Resource);

    public:
        virtual ~Prefab() = default;

    private:
        String mData;
    };
}