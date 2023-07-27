#include <YAWN/RHI/BufferView.hpp>
#include <YAWN/Core/Assert.hpp>

using namespace YAWN;

BufferView::BufferView(Ref<Buffer> buffer, int elementOffset, int elementCount)
    : mBuffer(buffer), mElementOffset(elementOffset), mElementCount(elementCount) {
    YAWN_ASSERT(buffer);
    YAWN_ASSERT(elementOffset >= 0);
    YAWN_ASSERT(elementOffset + elementCount <= buffer->GetElementCount());
}

void* BufferView::Map(BufferAccess access) {
    return mBuffer->Map(access);
}

void BufferView::Unmap() {
    mBuffer->Unmap();
}

int BufferView::GetElementOffset() const {
    return mElementOffset;
}

int BufferView::GetElementSize() const {
    return mBuffer->GetElementSize();
}

int BufferView::GetElementCount() const {
    return mElementCount;
}

int BufferView::GetSize() const {
    return mBuffer->GetElementSize() * mElementCount;
}

int BufferView::GetFlags() const {
    return mBuffer->GetFlags();;
}
