#include <YAWN/Editor/Importers/PrefabImporter.hpp>
#include <YAWN/IO/File.hpp>

using namespace YAWN;

void PrefabImporter::Register(Meta<PrefabImporter>& meta) {
    meta.SetBase<Importer>();
    meta.SetName(L"PrefabImporter");
    meta.SetConstructable();
}

void PrefabImporter::Import(const Path& inputPath, const Path& outputPath, const Map<String, Variant>& metadata) {
    File::WriteAllText(outputPath, File::ReadAllText(inputPath));
}

ArrayView<const String> PrefabImporter::GetSupportedExtensions() const {
    static String extensions[] = {
        L".prefab",
    };

    return extensions;
}
