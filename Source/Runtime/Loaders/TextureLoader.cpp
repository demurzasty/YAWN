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
    int mipmapCount = file.Read32();

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

    Ref<Texture> texture = new Texture(width, height, format, TextureFilter::Anisotropic, TextureWrapping::Repeat, mipmapCount);
    for (int i = 0; i < mipmapCount; ++i) {
        switch (format) {
        case TextureFormat::R8:
            file.Read(data.GetData(), width * height);
            break;
        case TextureFormat::RG8:
            file.Read(data.GetData(), width * height * 2);
            break;
        case TextureFormat::RGBA8:
            file.Read(data.GetData(), width * height * 4);
            break;
        case TextureFormat::BC1:
            file.Read(data.GetData(), width * height / 2);
            break;
        case TextureFormat::BC3:
            file.Read(data.GetData(), width * height);
            break;
        }

        texture->SetData(i, data.GetData());

        width /= 2;
        height /= 2;
    }

    return texture;
}

TypeId TextureLoader::GetSupportedResourceTypeId() const {
    return TypeId::From<Texture>();
}
