#include <YAWN/RHI/Buffer.hpp>
#include <YAWN/Core/Assert.hpp>

using namespace YAWN;

void* Buffer::Map(BufferAccess access) {
    YAWN_ASSERT(!mIsMapped);
    YAWN_ASSERT(mFlags & (BufferFlags::MapRead | BufferFlags::MapWrite));
    YAWN_ASSERT(access != BufferAccess::ReadOnly || (mFlags & BufferFlags::MapRead));
    YAWN_ASSERT(access != BufferAccess::WriteOnly || (mFlags & BufferFlags::MapWrite));
    YAWN_ASSERT(access != BufferAccess::ReadWrite || (mFlags & (BufferFlags::MapWrite | BufferFlags::MapRead)));

    void* data = OnMap(access);

#ifdef _DEBUG
    mIsMapped = true;
#endif

    return data;
}

void Buffer::Unmap() {
    YAWN_ASSERT(mIsMapped);
    YAWN_ASSERT(mFlags & (BufferFlags::MapRead | BufferFlags::MapWrite));

    OnUnmap();

#ifdef _DEBUG
    mIsMapped = false;
#endif
}

int Buffer::GetElementSize() const {
    return mElementSize;
}

int Buffer::GetElementCount() const {
    return mElementCount;
}

int Buffer::GetSize() const {
    return mElementSize * mElementCount;
}

int Buffer::GetFlags() const {
    return mFlags;
}

Buffer::Buffer(int elementSize, int elementCount, const void* data, int flags)
    : mElementSize(elementSize), mElementCount(elementCount), mFlags(flags) {
    YAWN_ASSERT(elementSize > 0);
    YAWN_ASSERT(elementCount > 0);
    YAWN_ASSERT(flags);
}
