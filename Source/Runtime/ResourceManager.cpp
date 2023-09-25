#include <YAWN/Runtime/ResourceManager.hpp>
#include <YAWN/Reflection/Types.hpp>

using namespace YAWN;

static Guid DefaultThemeGuid = Guid(L"d90daf62-efb7-40c0-8f15-56a6333d3775");

Map<int, Ref<Loader>> ResourceManager::sLoaders;
Map<Guid, Ref<Resource>> ResourceManager::sResources;

void ResourceManager::Initialize() {
    Types::EnumerateTypesOfBase<Loader>(Delegate<void(const Type&)>::Bind<&ResourceManager::InitializeLoader>());
}

void ResourceManager::Release() {
    sResources.Clear();
    sLoaders.Clear();
}

void ResourceManager::InitializeLoader(const Type& type) {
    Ref<Loader> loader = CastTo<Loader>(type.Construct());

    YAWN_ASSERT(loader);
    YAWN_ASSERT(loader->IsInstanceOf<Loader>());

    sLoaders.Add(loader->GetSupportedResourceTypeId(), loader);
}

Ref<Resource> ResourceManager::Load(int resourceTypeId, const Guid& guid) {
    YAWN_ASSERT(sLoaders.Contains(resourceTypeId));

    if (Ref<Resource>* resource = sResources.TryGet(guid); resource) {
        return *resource;
    }

    Ref<Loader> loader = sLoaders[resourceTypeId];

    Ref<Resource> resource = loader->Load(Path(L"Package") / guid.ToString());
    sResources.Add(guid, resource);
    return resource;
}

Ref<Resource> ResourceManager::Get(const Guid& guid) {
    if (Ref<Resource>* resource = sResources.TryGet(guid); resource) {
        return *resource;
    }

    return nullptr;
}

Ref<Theme> ResourceManager::GetDefaultTheme() {
    if (Ref<Resource> theme = Get(DefaultThemeGuid); theme) {
        return CastTo<Theme>(theme);
    }

    Ref<Theme> theme = Theme::CreateDefault();
    sResources.Add(DefaultThemeGuid, theme);
    return theme;
}
