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
    TextureFormat format = (TextureFormat)file.Read32();

    Array<char> data;

    switch (format) {
    case TextureFormat::R8:
        data.Resize(width * height);
        break;
    case TextureFormat::RG8:
        data.Resize(width * height * 2);
        break;
    case TextureFormat::RGBA8:
        data.Resize(width * height * 4);
        break;
    case TextureFormat::BC1:
        data.Resize(width * height / 2);
        break;
    case TextureFormat::BC3:
        data.Resize(width * height);
        break;
    }

    file.Read(data.GetData(), data.GetSize());

    Ref<Texture> texture = new Texture(width, height, format, TextureFilter::Anisotropic, TextureWrapping::Repeat, 1);
    texture->SetData(0, data.GetData());
    return texture;
}

TypeId TextureLoader::GetSupportedResourceTypeId() const {
    return TypeId::From<Texture>();
}
