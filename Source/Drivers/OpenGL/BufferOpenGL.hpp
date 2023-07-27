#pragma once 

#include <YAWN/RHI/Buffer.hpp>

#include <GL/glew.h>

namespace YAWN {
    class BufferOpenGL : public Buffer {
        YAWN_OBJECT(BufferOpenGL, Buffer);

    public:
        BufferOpenGL(int elementSize, int elementCount, const void* data, int flags);

        ~BufferOpenGL() override;

        GLuint GetId() const;

    protected:
        void* OnMap(BufferAccess access) override;

        void OnUnmap() override;

    private:
        GLuint mId = 0;
    };
}
