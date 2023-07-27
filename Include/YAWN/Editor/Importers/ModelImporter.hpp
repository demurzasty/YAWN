#pragma once 

#include "../Importer.hpp"

namespace YAWN {
    class ModelImporter : public Importer {
        YAWN_OBJECT(ModelImporter, Importer);

    public:
        static void Register(Meta<ModelImporter>& meta);

    public:
        virtual ~ModelImporter() = default;

        virtual void Import(const Path& inputPath, const Path& outputPath, const Map<String, Variant>& metadata) override;

        virtual ArrayView<const String> GetSupportedExtensions() const override;
    };
}
