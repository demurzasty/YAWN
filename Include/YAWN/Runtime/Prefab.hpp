#pragma once 

#include "Resource.hpp"
#include "../Scene/Node.hpp"

namespace YAWN {
    class Prefab : public Resource {
        YAWN_OBJECT(Prefab, Resource);

    public:
        static void Register(Meta<Prefab>& meta);

        Prefab(const String& data);

        virtual ~Prefab() = default;

        Ref<Node> Instantiate();

    private:
        String mData;
    };
}