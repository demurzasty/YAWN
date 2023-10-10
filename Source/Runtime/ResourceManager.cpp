#include <YAWN/Runtime/ResourceManager.hpp>
#include <YAWN/Reflection/Types.hpp>

using namespace YAWN;

static Guid DefaultThemeGuid = Guid(L"d90daf62-efb7-40c0-8f15-56a6333d3775");

Map<TypeId, Ref<Loader>> ResourceManager::sLoaders;
Map<Guid, Ref<Resource>> ResourceManager::sResources;

void ResourceManager::Initialize() {
    Types::EnumerateTypesOfBase<Loader>(Delegate<void(const Ref<Type>&)>::Bind<&ResourceManager::InitializeLoader>());
}

void ResourceManager::Release() {
    sResources.Clear();
    sLoaders.Clear();
}

void ResourceManager::InitializeLoader(const Ref<Type>& type) {
    Ref<Loader> loader = CastTo<Loader>(type->Construct());

    YAWN_ASSERT(loader);
    YAWN_ASSERT(loader->IsInstanceOf<Loader>());

    sLoaders.Add(loader->GetSupportedResourceTypeId(), loader);
}

Ref<Resource> ResourceManager::Get(const Guid& guid) {
    if (Ref<Resource>* resource = sResources.TryGet(guid); resource) {
        return *resource;
    }

    return nullptr;
}

void ResourceManager::Set(const Guid& guid, const Ref<Resource>& resource) {
    sResources.Add(guid, resource);
}

Ref<Resource> ResourceManager::Load(const String& resourceTypeName, const Guid& guid) {
    if (Ref<Type> type = Types::GetTypeByName(resourceTypeName)) {
        return Load(type->GetId(), guid);
    }

    return nullptr;
}

Ref<Resource> ResourceManager::Load(TypeId resourceTypeId, const Guid& guid) {
    YAWN_ASSERT(sLoaders.Contains(resourceTypeId));

    Ref<Resource> resource;
    if (sResources.TryGet(guid, resource)) {
        return resource;
    }

    Ref<Loader> loader = sLoaders[resourceTypeId];
    YAWN_ASSERT(loader);

    resource = loader->Load(Path(L"Package") / guid.ToString());
    Set(guid, resource);
    return resource;
}

Ref<Theme> ResourceManager::GetDefaultTheme() {
    if (Ref<Resource> theme = Get(DefaultThemeGuid)) {
        return CastTo<Theme>(theme);
    }

    Ref<Theme> theme = Theme::CreateDefault();
    sResources.Add(DefaultThemeGuid, theme);
    return theme;
}
