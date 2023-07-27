#include <YAWN/RHI/Texture.hpp>
#include <YAWN/Core/Assert.hpp>

using namespace YAWN;

void Texture::Update(int level, int x, int y, int z, int width, int height, int depth, const void* pixels) {
    YAWN_ASSERT(level >= 0 && level < mLevels);
    YAWN_ASSERT(x >= 0 && x + width <= mWidth);
    YAWN_ASSERT(y >= 0 && y + height <= mHeight);
    YAWN_ASSERT(z >= 0 && z + depth <= mDepth);
    YAWN_ASSERT(pixels);

    OnUpdate(level, x, y, z, width, height, depth, pixels);
}

int Texture::GetWidth() const {
    return mWidth;
}

int Texture::GetHeight() const {
    return mHeight;
}

int Texture::GetDepth() const {
    return mDepth;
}

int Texture::GetLevels() const {
    return mLevels;
}

TextureFormat Texture::GetFormat() const {
    return mFormat;
}

TextureFilter Texture::GetFilter() const {
    return mFilter;
}

TextureWrapping Texture::GetWrapping() const {
    return mWrapping;
}

int Texture::GetFlags() const {
    return mFlags;
}

Texture::Texture(int width, int height, int depth, int levels, TextureFormat format, TextureFilter filter, TextureWrapping wrapping, int flags)
    : mWidth(width), mHeight(height), mDepth(depth), mLevels(levels), mFormat(format), mFilter(filter), mWrapping(wrapping), mFlags(flags) {
    YAWN_ASSERT(width > 0);
    YAWN_ASSERT(height > 0);
    YAWN_ASSERT(depth > 0);
    YAWN_ASSERT(levels > 0);
    YAWN_ASSERT(!(flags & TextureFlags::CubeMap) || depth == 6);
}
