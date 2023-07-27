#pragma once

#include "../Runtime/Resource.hpp"
#include "../Core/String.hpp"

namespace YAWN {
    class Compute : public Resource {
        YAWN_OBJECT(Compute, Resource);

    public:
        Compute() = default;

        virtual ~Compute() = default;
    };
}
