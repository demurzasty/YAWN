#pragma once 

#include "../Importer.hpp"

namespace YAWN {
    class PrefabImporter : public Importer {
        YAWN_OBJECT(PrefabImporter, Importer);

    public:
        static void Register(Meta<PrefabImporter>& meta);

    public:
        virtual ~PrefabImporter() = default;

        virtual void Import(const Path& inputPath, const Path& outputPath, const Map<String, Variant>& metadata) override;

        virtual ArrayView<const String> GetSupportedExtensions() const override;
    };
}
