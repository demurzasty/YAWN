#pragma once 

#include "../Runtime/Reference.hpp"

namespace YAWN {
    struct ReadWriteMutexImpl;

    class ReadWriteMutex : public Reference {
        YAWN_OBJECT(ReadWriteMutex, Reference);

        friend class ConditionVariable;

    public:
        ReadWriteMutex();

        ~ReadWriteMutex();

        void ReadLock();

        bool TryReadLock();

        void ReadUnlock();

        void WriteLock();

        bool TryWriteLock();

        void WriteUnlock();

    private:
        ReadWriteMutexImpl* mImpl = nullptr;
    };

    class ReadLock {
    public:
        ReadLock(ReadWriteMutex& mutex);

        ~ReadLock();

    private:
        ReadWriteMutex& mMutex;
    };

    class WriteLock {
    public:
        WriteLock(ReadWriteMutex& mutex);

        ~WriteLock();

    private:
        ReadWriteMutex& mMutex;
    };
}
