#include <YAWN/Threading/ReadWriteMutex.hpp>

using namespace YAWN;

ReadLock::ReadLock(ReadWriteMutex& mutex)
    : mMutex(mutex) {
    mMutex.ReadLock();
}

ReadLock::~ReadLock() {
    mMutex.ReadUnlock();
}

WriteLock::WriteLock(ReadWriteMutex& mutex)
    : mMutex(mutex) {
    mMutex.WriteLock();
}

WriteLock::~WriteLock() {
    mMutex.WriteUnlock();
}
