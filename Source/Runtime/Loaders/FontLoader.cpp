#include <YAWN/Runtime/Loaders/FontLoader.hpp>
#include <YAWN/Graphics/Font.hpp>
#include <YAWN/IO/File.hpp>

using namespace YAWN;

void FontLoader::Register(Meta<FontLoader>& meta) {
    meta.SetBase<Loader>();
    meta.SetName(L"FontLoader");
    meta.SetConstructable();
}

Ref<Resource> FontLoader::Load(const Path& path) {
    return new Font(File::ReadAll(path));
}

TypeId FontLoader::GetSupportedResourceTypeId() const {
    return TypeId::From<Font>();
}
