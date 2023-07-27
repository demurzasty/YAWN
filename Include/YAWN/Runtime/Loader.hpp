#pragma once 

#include "Resource.hpp"
#include "../IO/Path.hpp"
#include "../Reflection/Meta.hpp"

namespace YAWN {
    class Loader : public Reference {
        YAWN_OBJECT(Loader, Reference);

    public:
        virtual ~Loader() = default;

        virtual Ref<Resource> Load(const Path& path) = 0;

        virtual int GetSupportedResourceTypeId() const = 0;
    };
}
