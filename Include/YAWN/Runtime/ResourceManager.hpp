#pragma once 

#include "Loader.hpp"
#include "../Core/Map.hpp"
#include "../Core/Guid.hpp"
#include "../Graphics/Theme.hpp"

namespace YAWN {
    class ResourceManager {
    public:
        static void Initialize();

        static void Release();

        template<typename TResource>
        static Ref<TResource> Load(const Guid& guid) {
            return CastTo<TResource>(Load(TypeID::Hash<TResource>(), guid));
        }

        static Ref<Theme> GetDefaultTheme();
        
    private:
        static void InitializeLoader(const Type& type);

        static Ref<Resource> Load(int resourceTypeId, const Guid& guid);

        static Ref<Resource> Get(const Guid& guid);

    private:
        static Map<int, Ref<Loader>> sLoaders;
        static Map<Guid, Ref<Resource>> sResources;
    };
}
