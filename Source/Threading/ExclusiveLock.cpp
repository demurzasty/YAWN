#include <YAWN/Threading/ExclusiveMutex.hpp>

using namespace YAWN;

ExclusiveLock::ExclusiveLock(ExclusiveMutex& mutex)
    : mMutex(mutex) {
    mMutex.Lock();
}

ExclusiveLock::~ExclusiveLock() {
    mMutex.Unlock();
}
