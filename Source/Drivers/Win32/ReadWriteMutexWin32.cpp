#include <YAWN/Threading/ReadWriteMutex.hpp>

#include "ThreadingWin32.hpp"

using namespace YAWN;

ReadWriteMutex::ReadWriteMutex() {
    mImpl = new ReadWriteMutexImpl();

    InitializeSRWLock(&mImpl->SRWLock);
}

ReadWriteMutex::~ReadWriteMutex() {
    delete mImpl;
}

void ReadWriteMutex::ReadLock() {
    AcquireSRWLockShared(&mImpl->SRWLock);
}

bool ReadWriteMutex::TryReadLock() {
    return TryAcquireSRWLockShared(&mImpl->SRWLock) == TRUE;
}

void ReadWriteMutex::ReadUnlock() {
    ReleaseSRWLockShared(&mImpl->SRWLock);
}

void ReadWriteMutex::WriteLock() {
    AcquireSRWLockExclusive(&mImpl->SRWLock);
}

bool ReadWriteMutex::TryWriteLock() {
    return TryAcquireSRWLockExclusive(&mImpl->SRWLock) == TRUE;
}

void ReadWriteMutex::WriteUnlock() {
    ReleaseSRWLockExclusive(&mImpl->SRWLock);
}
