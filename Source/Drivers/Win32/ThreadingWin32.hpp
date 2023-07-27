#pragma once 

#include <Windows.h>
#include <process.h>

namespace YAWN {
    struct ExclusiveMutexImpl {
        CRITICAL_SECTION CriticalSection;
    };

    struct ReadWriteMutexImpl {
        SRWLOCK SRWLock;
    };

    struct ConditionVariableImpl {
        CONDITION_VARIABLE ConditionVariable;
    };

    struct ThreadImpl {
        HANDLE Handle;
        unsigned int ThreadId;
    };
}
