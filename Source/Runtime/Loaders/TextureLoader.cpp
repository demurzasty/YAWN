#include <YAWN/Runtime/Loaders/TextureLoader.hpp>
#include <YAWN/Graphics/Texture.hpp>
#include <YAWN/IO/File.hpp>

using namespace YAWN;

void TextureLoader::Register(Meta<TextureLoader>& meta) {
    meta.SetBase<Loader>();
    meta.SetName(L"TextureLoader");
    meta.SetConstructable();
}

Ref<Resource> TextureLoader::Load(const Path& path) {
    File file;
    file.Open(path, FileModeFlags::Read);
    YAWN_ASSERT(file.IsOpen());

    int width = file.Read32();
    int height = file.Read32();
    int channels = file.Read32();

    Array<char> data(width * height * channels);
    file.Read(data.GetData(), data.GetSize());

    Ref<Texture> texture = new Texture(width, height, TextureFormat::RGBA8, TextureFilter::Anisotropic, TextureWrapping::Repeat, 1);
    
    return texture;
}

int TextureLoader::GetSupportedResourceTypeId() const {
    return TypeID::Hash<Texture>();
}
