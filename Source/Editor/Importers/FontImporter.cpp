#include <YAWN/Editor/Importers/FontImporter.hpp>
#include <YAWN/IO/File.hpp>

using namespace YAWN;

void FontImporter::Register(Meta<FontImporter>& meta) {
    meta.SetBase<Importer>();
    meta.SetName(L"FontImporter");
    meta.SetConstructable();
}

void FontImporter::Import(const Path& inputPath, const Path& outputPath, const Map<String, Variant>& metadata) {
    File::Copy(inputPath, outputPath);
}

ArrayView<const String> FontImporter::GetSupportedExtensions() const {
    static String extensions[] = {
        L".ttf",
    };

    return extensions;
}
