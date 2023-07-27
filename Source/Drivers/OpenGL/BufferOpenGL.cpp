#include "BufferOpenGL.hpp"

#include <YAWN/Core/Assert.hpp>

using namespace YAWN;

BufferOpenGL::BufferOpenGL(int elementSize, int elementCount, const void* data, int flags)
    : Buffer(elementSize, elementCount, data, flags) {
    glCreateBuffers(1, &mId);

    GLbitfield nativeFlags = 0;

#ifdef _DEBUG
    if (flags & BufferFlags::Uniform) {
        GLint maxUniformBlockSize;
        glGetIntegerv(GL_MAX_UNIFORM_BLOCK_SIZE, &maxUniformBlockSize);
        YAWN_ASSERT(GetSize() <= maxUniformBlockSize);
    }
#endif

    if (flags & BufferFlags::Dynamic) {
        nativeFlags |= GL_DYNAMIC_STORAGE_BIT;
    }

    if (flags & BufferFlags::MapRead) {
        nativeFlags |= GL_MAP_READ_BIT;
    }

    if (flags & BufferFlags::MapWrite) {
        nativeFlags |= GL_MAP_WRITE_BIT;
    }

    if (flags & BufferFlags::MapPersistent) {
        nativeFlags |= GL_MAP_PERSISTENT_BIT;
    }

    if (flags & BufferFlags::MapCoherent) {
        nativeFlags |= GL_MAP_COHERENT_BIT;
    }

    if (flags & BufferFlags::ClientStorage) {
        nativeFlags |= GL_CLIENT_STORAGE_BIT;
    }

    glNamedBufferStorage(mId, GetSize(), data, nativeFlags);
}

BufferOpenGL::~BufferOpenGL() {
    glDeleteBuffers(1, &mId);
}

GLuint BufferOpenGL::GetId() const {
    return mId;
}

void* BufferOpenGL::OnMap(BufferAccess access) {
    GLenum nativeAccess = GL_READ_WRITE;

    switch (access) {
        case BufferAccess::ReadOnly: nativeAccess = GL_READ_ONLY; break;
        case BufferAccess::WriteOnly: nativeAccess = GL_WRITE_ONLY; break;
    }

    return glMapNamedBuffer(mId, nativeAccess);
}

void BufferOpenGL::OnUnmap() {
    glUnmapNamedBuffer(mId);
}
