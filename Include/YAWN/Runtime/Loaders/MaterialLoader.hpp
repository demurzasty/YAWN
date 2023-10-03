#pragma once 

#include "../Loader.hpp"
#include "../../Graphics/Material.hpp"

namespace YAWN {
    class MaterialLoader : public Loader {
        YAWN_OBJECT(MaterialLoader, Loader);

    public:
        static void Register(Meta<MaterialLoader>& meta);

    public:
        virtual ~MaterialLoader() = default;

        virtual Ref<Resource> Load(const Path& path) override;

        virtual int GetSupportedResourceTypeId() const override;
    };
}
