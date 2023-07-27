#pragma once 

#include "../Runtime/Resource.hpp"

namespace YAWN {
    enum class TextureFormat {
        R8,
        RG8,
        RGBA8,
        BC1,
        BC3,
        BC4,
    };

    enum class TextureFilter {
        Nearest,
        Linear,
        Anisotropic
    };

    enum class TextureWrapping {
        ClampToEdge,
        Repeat
    };

    class Texture : public Resource {
        YAWN_OBJECT(Texture, Resource);

    public:
        Texture(int width, int height, TextureFormat format, TextureFilter filter, TextureWrapping wrapping, int mipmapCount);

        virtual ~Texture() override;

    private:
        const int mId;
    };
}
