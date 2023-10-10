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

static void WriteImage(const Path& outputPath, Ref<Image> image) {
    if (image->GetInfo().GetWidth() < 4 || image->GetInfo().GetHeight() < 4) {
        // Need at least one 4x4 pixel block.
        image = Image::Resize(image, Math::Max(image->GetInfo().GetWidth(), 4), Math::Max(image->GetInfo().GetHeight(), 4));
    } else if (!image->IsPowerOfTwo()) {
        // Be sure that texture size is power of two.
        image = Image::ResizeToNextPowerOfTwo(image);
    }

    TextureFormat format = TextureFormat::RGBA8;
    switch (image->GetInfo().GetChannels()) {
        case 1: format = TextureFormat::R8; break;
        case 2: format = TextureFormat::RG8; break;
        case 4: format = TextureFormat::BC1; break;
    }

    int mipmapCount = image->CalculateMipmapCount();

    File file;
    file.Open(outputPath, FileModeFlags::Write);
    YAWN_ASSERT(file.IsOpen());

    file.Write32(image->GetInfo().GetWidth());
    file.Write32(image->GetInfo().GetHeight());
    file.Write32(int(format));
    file.Write32(mipmapCount);

    for (int i = 0; i < mipmapCount; ++i) {
        if (format == TextureFormat::BC1) {
            Array<unsigned char> data = S3TC::BC1(image);
            file.Write(data.GetData(), data.GetSizeInBytes());
        } else if (format == TextureFormat::BC3) {
            Array<unsigned char> data = S3TC::BC3(image);
            file.Write(data.GetData(), data.GetSizeInBytes());
        } else if (format == TextureFormat::BC4) {
            Array<unsigned char> data = S3TC::BC4(image);
            file.Write(data.GetData(), data.GetSizeInBytes());
        } else {
            file.Write(image->GetData().GetData(), image->GetData().GetSizeInBytes());
        }

        if (i < mipmapCount - 1) {
            image = Image::Resize(image, image->GetInfo().GetWidth() / 2, image->GetInfo().GetHeight() / 2);
        }
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
