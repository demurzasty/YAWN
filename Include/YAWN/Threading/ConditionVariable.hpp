#pragma once 

#include "ExclusiveMutex.hpp"
#include "ReadWriteMutex.hpp"
#include "../Runtime/Delegate.hpp"

namespace YAWN {
    struct ConditionVariableImpl;

    class ConditionVariable : public Reference {
        YAWN_OBJECT(ConditionVariable, Reference);

    public:
        ConditionVariable();

        ~ConditionVariable();

        void NotifyOne();

        void NotifyAll();

        void Wait(const ExclusiveMutex& exclusiveMutex);

        void Wait(const ExclusiveMutex& exclusiveMutex, const Delegate<bool()>& predicate);

        void WaitRead(const ReadWriteMutex& readWriteMutex);

        void WaitWrite(const ReadWriteMutex& readWriteMutex);

    private:
        ConditionVariableImpl* mImpl = nullptr;
    };
}
