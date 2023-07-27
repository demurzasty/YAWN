#include <YAWN/Threading/Thread.hpp>

#include "ThreadingWin32.hpp"

using namespace YAWN;

static int GetNativeHardwareConcurrency() {
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    return int(sysinfo.dwNumberOfProcessors);
}

int Thread::GetHardwareConcurrency() {
    static const int hardwareConcurrency = GetNativeHardwareConcurrency();

    return hardwareConcurrency;
}

static unsigned __stdcall ThreadFunc(void* argument) {
    if (argument) {
        Delegate<void()>& delegate = *(Delegate<void()>*)argument;

        if (delegate) {
            delegate();
        }
    }

    _endthreadex(0);
    return 0;
}

Thread::Thread(const Delegate<void()>& delegate)
    : mDelegate(delegate) {
    mImpl = new ThreadImpl();

    mImpl->Handle = (HANDLE)_beginthreadex(nullptr, 0, &ThreadFunc, &mDelegate, 0, &mImpl->ThreadId);
}

Thread::~Thread() {
    WaitForSingleObject(mImpl->Handle, INFINITE);

    CloseHandle(mImpl->Handle);
}

void Thread::Wait() {
    WaitForSingleObject(mImpl->Handle, INFINITE);
}
