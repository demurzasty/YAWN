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
            return CastTo<TResource>(Load(TypeId::From<TResource>(), guid));
        }

        static Ref<Resource> Load(const String& resourceTypeName, const Guid& guid);

        static Ref<Theme> GetDefaultTheme();

        static Ref<Resource> Get(const Guid& guid);

        static void Set(const Guid& guid, const Ref<Resource>& resource);
        
    private:
        static void InitializeLoader(const Ref<Type>& type);

        static Ref<Resource> Load(TypeId resourceTypeId, const Guid& guid);

    private:
        static Map<TypeId, Ref<Loader>> sLoaders;
        static Map<Guid, Ref<Resource>> sResources;
    };
}
