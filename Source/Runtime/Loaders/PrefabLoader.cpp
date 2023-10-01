#include <YAWN/Runtime/Loaders/PrefabLoader.hpp>
#include <YAWN/Runtime/Prefab.hpp>
#include <YAWN/IO/File.hpp>

using namespace YAWN;

void PrefabLoader::Register(Meta<PrefabLoader>& meta) {
    meta.SetConstructable();
}

Ref<Resource> PrefabLoader::Load(const Path& path) {
    return new Prefab(File::ReadAllText(path));
}

int PrefabLoader::GetSupportedResourceTypeId() const {
    return TypeID::Hash<Prefab>();
}
