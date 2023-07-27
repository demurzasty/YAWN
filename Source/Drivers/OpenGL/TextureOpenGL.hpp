#pragma once 

#include <YAWN/RHI/Texture.hpp>

#include <GL/glew.h>

namespace YAWN {
    class TextureOpenGL : public Texture {
        YAWN_OBJECT(TextureOpenGL, Texture);

    public:
        TextureOpenGL(int width, int height, int depth, int levels, TextureFormat format, TextureFilter filter, TextureWrapping wrapping, int flags);

        ~TextureOpenGL();

        GLuint GetId() const;

    protected:
        void OnUpdate(int level, int x, int y, int z, int width, int height, int depth, const void* pixels) override;

    private:
        GLuint mId = 0;
        GLenum mInternalFormat;
        GLenum mTransferFormat;
    };
}