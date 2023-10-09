#pragma once 

#include "../Loader.hpp"
#include "../../Graphics/Mesh.hpp"

namespace YAWN {
    class MeshLoader : public Loader {
        YAWN_OBJECT(MeshLoader, Loader);

    public:
        static void Register(Meta<MeshLoader>& meta);

    public:
        virtual ~MeshLoader() = default;

        virtual Ref<Resource> Load(const Path& path) override;

        virtual TypeId GetSupportedResourceTypeId() const override;
    };
}
