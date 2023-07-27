#pragma once 

#include "../Runtime/Resource.hpp"

namespace YAWN {
    class Mesh : public Resource {
        YAWN_OBJECT(Mesh, Resource);

    public:
        Mesh();
    };
}