#pragma once 

#include "../Runtime/Reference.hpp"

namespace YAWN {
    struct TextureFlags {
        static constexpr int CubeMap = 1;
    };

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

    class Texture : public Reference {
        YAWN_OBJECT(Texture, Reference);

    public:
        virtual ~Texture() = default;

        void Update(int level, int x, int y, int z, int width, int height, int depth, const void* pixels);

        int GetWidth() const;

        int GetHeight() const;

        int GetDepth() const;

        int GetLevels() const;

        TextureFormat GetFormat() const;

        TextureFilter GetFilter() const;

        TextureWrapping GetWrapping() const;

        int GetFlags() const;

    protected:
        Texture(int width, int height, int depth, int levels, TextureFormat format, TextureFilter filter, TextureWrapping wrapping, int flags);

        virtual void OnUpdate(int level, int x, int y, int z, int width, int height, int depth, const void* pixels) = 0;

    private:
        const int mWidth;
        const int mHeight;
        const int mDepth;
        const int mLevels;
        const TextureFormat mFormat;
        const TextureFilter mFilter;
        const TextureWrapping mWrapping;
        const int mFlags;
    };
}
