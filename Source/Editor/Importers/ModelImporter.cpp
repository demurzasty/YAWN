#include <YAWN/Editor/Importers/ModelImporter.hpp>

#include <Windows.h>

#include <cgltf.h>

using namespace YAWN;

void ModelImporter::Register(Meta<ModelImporter>& meta) {
    meta.SetBase<Importer>();
    meta.SetName(L"ModelImporter");
    meta.SetConstructable();
}

void ModelImporter::Import(const Path& inputPath, const Path& outputPath, const Map<String, Variant>& metadata) {
    cgltf_options options = { cgltf_file_type_invalid };
    cgltf_data* data = nullptr;
    if (cgltf_parse_file(&options, inputPath.ToString().ToUTF8().GetData(), &data) == cgltf_result_success) {

        cgltf_free(data);
    }
}

ArrayView<const String> ModelImporter::GetSupportedExtensions() const {
    static String extensions[] = {
        L".gltf",
    };

    return extensions;
}
