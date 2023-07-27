#include <YAWN/Runtime/Buffer.hpp>
#include <YAWN/Core/Memory.hpp>

using namespace YAWN;

Buffer::Buffer(int size)
    : mSize(size) {
    mData = Memory::Allocate(mSize);
}

Buffer::Buffer(const void* initialData, int size)
    : mSize(size) {
    mData = Memory::Allocate(mSize);
    Memory::Copy(mData, initialData, mSize);
}

Buffer::~Buffer() {
    Memory::Deallocate(mData);
}

const void* Buffer::GetData() const {
    return mData;
}

void* Buffer::GetData() {
    return mData;
}

int Buffer::GetSize() const {
    return mSize;
}
