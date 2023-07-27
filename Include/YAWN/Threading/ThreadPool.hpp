#pragma once 

#include "Thread.hpp"
#include "ConditionVariable.hpp"
#include "ExclusiveMutex.hpp"
#include "../Core/Array.hpp"

namespace YAWN {
    class ThreadPool {
    public:
        static void Initialize();

        static void Release();

        static void Submit(const Delegate<void()>& delegate);

    private:
        static void Worker();

        static bool IsAvailable();

    private:
        static volatile bool sRunning; // TODO: Should be atomic.
        static ConditionVariable sAvailable;
        static ExclusiveMutex sMutex;
        static Array<Delegate<void()>> sTasks;
        static Array<Ref<Thread>> sThreads;
    };
}