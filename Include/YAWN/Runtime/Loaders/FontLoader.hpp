#pragma once 

#include "../Loader.hpp"
#include "../../Graphics/Font.hpp"

namespace YAWN {
    class FontLoader : public Loader {
        YAWN_OBJECT(FontLoader, Loader);

    public:
        static void Register(Meta<FontLoader>& meta);

    public:
        virtual ~FontLoader() = default;

        virtual Ref<Resource> Load(const Path& path) override;

        virtual int GetSupportedResourceTypeId() const override;
    };
}
