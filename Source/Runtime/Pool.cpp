#include <YAWN/Runtime/Pool.hpp>

using namespace YAWN;

int Pool::Acquire() {
    if (mDisposed == None) {
        return mPool.Add(mPool.GetSize());
    }

    int recycled = mDisposed;
    mDisposed = mPool[mDisposed];
    return mPool[recycled] = recycled;
}

void Pool::Dispose(int id) {
    YAWN_ASSERT(IsValid(id));

    mPool[id] = mDisposed;
    mDisposed = id;
}

bool Pool::IsValid(int id) const {
    return id >= 0 && id < mPool.GetSize() && mPool[id] == id;
}

int Pool::GetSize() const {
    return mPool.GetSize();
}

const int* Pool::GetData() const {
    return mPool.GetData();
}
