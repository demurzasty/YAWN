#pragma once 

#include "../Importer.hpp"

namespace YAWN {
    class TextureImporter : public Importer {
        YAWN_OBJECT(TextureImporter, Importer);

    public:
        static void Register(Meta<TextureImporter>& meta);

    public:
        virtual ~TextureImporter() = default;

        virtual void Import(const Path& inputPath, const Path& outputPath, const Map<String, Variant>& metadata) override;

        virtual ArrayView<const String> GetSupportedExtensions() const override;
    };
}
