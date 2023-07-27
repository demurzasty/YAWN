#pragma once 

#include "Reference.hpp"

namespace YAWN {
    class Resource : public Reference {
        YAWN_OBJECT(Resource, Reference);

    public:
        virtual ~Resource() = default;
    };
}
