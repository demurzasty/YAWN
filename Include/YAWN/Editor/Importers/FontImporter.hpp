#pragma once 

#include "../Importer.hpp"

namespace YAWN {
    class FontImporter : public Importer {
        YAWN_OBJECT(FontImporter, Importer);

    public:
        static void Register(Meta<FontImporter>& meta);

    public:
        virtual ~FontImporter() = default;

        virtual void Import(const Path& inputPath, const Path& outputPath, const Map<String, Variant>& metadata) override;

        virtual ArrayView<const String> GetSupportedExtensions() const override;
    };
}
