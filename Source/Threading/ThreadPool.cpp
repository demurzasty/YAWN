#include <YAWN/Threading/ThreadPool.hpp>

using namespace YAWN;

volatile bool ThreadPool::sRunning = false;
ConditionVariable ThreadPool::sAvailable;
ExclusiveMutex ThreadPool::sMutex;
Array<Delegate<void()>> ThreadPool::sTasks;
Array<Ref<Thread>> ThreadPool::sThreads;

void ThreadPool::Initialize() {
    sThreads.Resize(Thread::GetHardwareConcurrency() - 1);

    Delegate<void()> worker = Delegate<void()>::Bind<&ThreadPool::Worker>();

    sRunning = true;
    for (int i = 0; i < sThreads.GetSize(); ++i) {
        sThreads[i] = new Thread(worker);
    }
}

void ThreadPool::Release() {
    sRunning = false;

    sAvailable.NotifyAll();

    sThreads.Clear();
}

void ThreadPool::Submit(const Delegate<void()>& delegate) {
    sMutex.Lock();

    sTasks.Insert(0, delegate);

    sMutex.Unlock();

    sAvailable.NotifyOne();
}

void ThreadPool::Worker() {
    Delegate<bool()> available;
    available.Connect<&ThreadPool::IsAvailable>();

    while (sRunning) {
        sMutex.Lock();

        sAvailable.Wait(sMutex, available);

        if (sRunning) {
            Delegate<void()> task = sTasks.GetBack();
            sTasks.Pop();

            sMutex.Unlock();

            task();
        } else {
            sMutex.Unlock();
        }
    }
}

bool ThreadPool::IsAvailable() {
    return !sTasks.IsEmpty() || !sRunning;
}
