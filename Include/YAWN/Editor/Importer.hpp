#pragma once 

#include "../Runtime/Reference.hpp"
#include "../Runtime/Variant.hpp"
#include "../Reflection/Meta.hpp"
#include "../IO/Path.hpp"

namespace YAWN {
    class Importer : public Reference {
        YAWN_OBJECT(Importer, Reference);

    public:
        virtual ~Importer() = default;

        virtual void Import(const Path& inputPath, const Path& outputPath, const Map<String, Variant>& metadata) = 0;

        virtual ArrayView<const String> GetSupportedExtensions() const = 0;
    };
}
