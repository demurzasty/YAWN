#pragma once 

#include "../Runtime/Reference.hpp"

namespace YAWN {
    struct ExclusiveMutexImpl;

    class ExclusiveMutex : public Reference {
        YAWN_OBJECT(ExclusiveMutex, Reference);

        friend class ConditionVariable;

    public:
        ExclusiveMutex();

        ~ExclusiveMutex();

        void Lock();

        bool TryLock();

        void Unlock();

    private:
        ExclusiveMutexImpl* mImpl = nullptr;
    };

    class ExclusiveLock {
    public:
        ExclusiveLock(ExclusiveMutex& mutex);

        ~ExclusiveLock();

    private:
        ExclusiveMutex& mMutex;
    };
}
