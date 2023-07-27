#include "TextureOpenGL.hpp"

using namespace YAWN;

static GLenum TranslateInternalFormat(TextureFormat format) {
    switch (format) {
    case TextureFormat::R8:
        return GL_R8;
    case TextureFormat::RG8:
        return GL_RG8;
    case TextureFormat::RGBA8:
        return GL_RGBA8;
    case TextureFormat::BC1:
        return GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
    case TextureFormat::BC3:
        return GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
    }

    return GL_RGBA8;
}

static GLenum TranslateTransferFormat(TextureFormat format) {
    switch (format) {
    case TextureFormat::R8:
        return GL_RED;
    case TextureFormat::RG8:
        return GL_RG;
    case TextureFormat::RGBA8:
        return GL_RGBA;
    case TextureFormat::BC1:
        return GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
    case TextureFormat::BC3:
        return GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
    }

    return GL_RGBA;
}

TextureOpenGL::TextureOpenGL(int width, int height, int depth, int levels, TextureFormat format, TextureFilter filter, TextureWrapping wrapping, int flags)
    : Texture(width, height, depth, levels, format, filter, wrapping, flags), mInternalFormat(TranslateInternalFormat(format)), mTransferFormat(TranslateTransferFormat(format)) {
    if (height == 1 && depth == 1) {
        glCreateTextures(GL_TEXTURE_1D, 1, &mId);
        glTextureStorage1D(mId, levels, mInternalFormat, width);
    } else if (depth == 1) {
        glCreateTextures(GL_TEXTURE_2D, 1, &mId);
        glTextureStorage2D(mId, levels, mInternalFormat, width, height);
    } else {
        glCreateTextures(GL_TEXTURE_3D, 1, &mId);
        glTextureStorage3D(mId, levels, mInternalFormat, width, height, depth);
    }
}

TextureOpenGL::~TextureOpenGL() {
    glDeleteTextures(1, &mId);
}

GLuint TextureOpenGL::GetId() const {
    return mId;
}

void TextureOpenGL::OnUpdate(int level, int x, int y, int z, int width, int height, int depth, const void* pixels) {
    if (GetHeight() == 1 && GetDepth() == 1) {
        glTextureSubImage1D(mId, level, x, width, mTransferFormat, GL_UNSIGNED_BYTE, pixels);
    } else if (GetDepth() == 1) {
        glTextureSubImage2D(mId, level, x, y, width, height, mTransferFormat, GL_UNSIGNED_BYTE, pixels);
    } else {
        glTextureSubImage3D(mId, level, x, y, z, width, height, height, mTransferFormat, GL_UNSIGNED_BYTE, pixels);
    }
}
