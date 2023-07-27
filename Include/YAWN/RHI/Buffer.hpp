#pragma once 

#include "../Runtime/Reference.hpp"

namespace YAWN {
    struct BufferFlags {
        static constexpr int TransferSource = 1;
        static constexpr int TransferDestination = 2;
        static constexpr int Uniform = 4;
        static constexpr int Storage = 8;
        static constexpr int Index = 16;
        static constexpr int Vertex = 32;
        static constexpr int Indirect = 64;

        static constexpr int Dynamic = 128;
        static constexpr int MapRead = 256;
        static constexpr int MapWrite = 512;
        static constexpr int MapPersistent = 1024;
        static constexpr int MapCoherent = 2048;
        static constexpr int ClientStorage = 4096;
    };

    enum class BufferAccess {
        ReadOnly,
        WriteOnly,
        ReadWrite
    };

    class Buffer : public Reference {
        YAWN_OBJECT(Buffer, Reference);

    public:
        virtual ~Buffer() = default;

        void* Map(BufferAccess access);

        void Unmap();

        int GetElementSize() const;

        int GetElementCount() const;

        int GetSize() const;

        int GetFlags() const;

    protected:
        Buffer(int elementSize, int elementCount, const void* data, int flags);

        virtual void* OnMap(BufferAccess access) = 0;

        virtual void OnUnmap() = 0;

    private:
        const int mElementSize;
        const int mElementCount;
        const int mFlags;

#ifdef _DEBUG
        bool mIsMapped = false;
#endif
    };
}
