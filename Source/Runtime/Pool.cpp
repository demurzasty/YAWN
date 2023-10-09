#include <YAWN/Runtime/Pool.hpp>

using namespace YAWN;

OID Pool::Acquire() {
    if (mDisposed == None) {
        return mPool.Add(OID(mPool.GetSize(), 0));
    }

    OID recycled = mDisposed;
    mDisposed = mPool[mDisposed.GetIndex()];
    return mPool[recycled.GetIndex()] = recycled.Bump();
}

void Pool::Dispose(OID id) {
    YAWN_ASSERT(IsValid(id));

    mPool[id.GetIndex()] = mDisposed;
    mDisposed = id;
}

bool Pool::IsValid(OID id) const {
    int index = id.GetIndex();
    return index >= 0 && index < mPool.GetSize() && mPool[index] == id;
}

int Pool::GetSize() const {
    return mPool.GetSize();
}

const OID* Pool::GetData() const {
    return mPool.GetData();
}
