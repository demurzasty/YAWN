#include <YAWN/Editor/Importers/TextureImporter.hpp>
#include <YAWN/Graphics/Image.hpp>
#include <YAWN/IO/File.hpp>

#include <stdio.h>

using namespace YAWN;

void TextureImporter::Register(Meta<TextureImporter>& meta) {
    meta.SetBase<Importer>();
    meta.SetName(L"TextureImporter");
    meta.SetConstructable();
}

void TextureImporter::Import(const Path& inputPath, const Path& outputPath, const Map<String, Variant>& metadata) {
    Ref<Image> image = Image::FromFile(inputPath, 4);
    YAWN_ASSERT(image);

    File file;
    file.Open(outputPath, FileModeFlags::Write);
    printf("%s\n", outputPath.ToString().ToUTF8().GetData());
    YAWN_ASSERT(file.IsOpen());

    file.Write32(image->GetInfo().GetWidth());
    file.Write32(image->GetInfo().GetHeight());
    file.Write32(image->GetInfo().GetChannels());
    file.Write(image->GetData().GetData(), image->GetData().GetSizeInBytes());
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
