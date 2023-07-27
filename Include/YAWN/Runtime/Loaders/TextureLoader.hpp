#pragma once 

#include "../Loader.hpp"
#include "../../Graphics/Texture.hpp"

namespace YAWN {
    class TextureLoader : public Loader {
        YAWN_OBJECT(TextureLoader, Loader);

    public:
        static void Register(Meta<TextureLoader>& meta);

    public:
        virtual ~TextureLoader() = default;

        virtual Ref<Resource> Load(const Path& path) override;

        virtual int GetSupportedResourceTypeId() const override;
    };
}
