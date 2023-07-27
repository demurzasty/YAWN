#include <YAWN/Threading/ExclusiveMutex.hpp>

#include "ThreadingWin32.hpp"

using namespace YAWN;

ExclusiveMutex::ExclusiveMutex() {
    mImpl = new ExclusiveMutexImpl();

    InitializeCriticalSection(&mImpl->CriticalSection);
}

ExclusiveMutex::~ExclusiveMutex() {
    DeleteCriticalSection(&mImpl->CriticalSection);

    delete mImpl;
}

void ExclusiveMutex::Lock() {
    EnterCriticalSection(&mImpl->CriticalSection);
}

bool ExclusiveMutex::TryLock() {
    return TryEnterCriticalSection(&mImpl->CriticalSection) == TRUE;
}

void ExclusiveMutex::Unlock() {
    LeaveCriticalSection(&mImpl->CriticalSection);
}
