#pragma once 

#include "../Importer.hpp"
#include "../../Graphics/Vertex.hpp"
#include "../../Core/Map.hpp"
#include "../../Core/Guid.hpp"
#include "../../Runtime/Variant.hpp"

typedef struct cgltf_data cgltf_data;
typedef struct cgltf_node cgltf_node;

namespace YAWN {
    class ModelImporter : public Importer {
        YAWN_OBJECT(ModelImporter, Importer);

    public:
        static void Register(Meta<ModelImporter>& meta);

    public:
        virtual ~ModelImporter() = default;

        virtual void Import(const Path& inputPath, const Path& outputPath, const Map<String, Variant>& metadata) override;

        virtual ArrayView<const String> GetSupportedExtensions() const override;

    private:
        void Import(Map<String, Variant>& prefab, const Path& basePath, const Path& outputPath, cgltf_data* data, cgltf_node* node);
    };
}
