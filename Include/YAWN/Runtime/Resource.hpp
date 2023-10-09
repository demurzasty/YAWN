#pragma once 

#include "Reference.hpp"
#include "../Reflection/Meta.hpp"
#include "../Runtime/OID.hpp"

namespace YAWN {
    class Resource : public Reference {
        YAWN_OBJECT(Resource, Reference);

    public:
        static void Register(Meta<Resource>& meta);

        virtual ~Resource() = default;
    };
}
