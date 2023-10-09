#pragma once 

#include "../Loader.hpp"

namespace YAWN {
    class PrefabLoader : public Loader {
        YAWN_OBJECT(PrefabLoader, Loader);

    public:
        static void Register(Meta<PrefabLoader>& meta);

        virtual ~PrefabLoader() = default;

        virtual Ref<Resource> Load(const Path& path) override;

        virtual TypeId GetSupportedResourceTypeId() const override;
    };
}
