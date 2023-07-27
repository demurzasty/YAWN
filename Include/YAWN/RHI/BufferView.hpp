#pragma once 

#include "Buffer.hpp"

namespace YAWN {
    class BufferView : public Reference {
        YAWN_OBJECT(BufferView, Reference);

        friend class GraphicsDevice;

    public:
        virtual ~BufferView() = default;

        void* Map(BufferAccess access);

        void Unmap();

        int GetElementOffset() const;

        int GetElementSize() const;

        int GetElementCount() const;

        int GetSize() const;

        int GetFlags() const;

    protected:
        BufferView(Ref<Buffer> buffer, int elementOffset, int elementCount);

    private:
        const Ref<Buffer> mBuffer;
        const int mElementOffset;
        const int mElementCount;
    };
}
