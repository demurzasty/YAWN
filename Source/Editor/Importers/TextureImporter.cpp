#include <YAWN/Editor/Importers/TextureImporter.hpp>
#include <YAWN/Graphics/Image.hpp>
#include <YAWN/IO/File.hpp>
#include <YAWN/Graphics/S3TC.hpp>
#include <YAWN/Graphics/Texture.hpp>

#include <stdio.h>

using namespace YAWN;

void TextureImporter::Register(Meta<TextureImporter>& meta) {
    meta.SetBase<Importer>();
    meta.SetName(L"TextureImporter");
    meta.SetConstructable();
}

static void WriteImage(const Path& outputPath, const Ref<Image>& image) {
    TextureFormat format = TextureFormat::RGBA8;
    switch (image->GetInfo().GetChannels()) {
        case 1: format = TextureFormat::R8; break;
        case 2: format = TextureFormat::RG8; break;
        case 4: format = TextureFormat::BC1; break;
    }

    File file;
    file.Open(outputPath, FileModeFlags::Write);
    YAWN_ASSERT(file.IsOpen());

    file.Write32(image->GetInfo().GetWidth());
    file.Write32(image->GetInfo().GetHeight());
    file.Write32(int(format));

    if (format == TextureFormat::BC1) {
        Array<unsigned char> data = S3TC::BC1(image);
        file.Write(data.GetData(), data.GetSizeInBytes());
    } else {
        file.Write(image->GetData().GetData(), image->GetData().GetSizeInBytes());
    }
}

void TextureImporter::Import(const Path& inputPath, const Path& outputPath, const Map<String, Variant>& metadata) {
    Ref<Image> image = Image::FromFile(inputPath, 4);
    YAWN_ASSERT(image);

    WriteImage(outputPath, image);

    Ref<Image> thumbnail = Image::Resize(image, 128, 128);

    Path thumbnailPath = Path(L"Cache/Thumbnails") / outputPath.GetFilename();

    WriteImage(thumbnailPath, thumbnail);
}

ArrayView<const String> TextureImporter::GetSupportedExtensions() const {
    static String extensions[] = {
        L".png",
        L".bmp",
        L".jpg",
        L".jpeg",
        L".tga",
    };

    return extensions;
}
