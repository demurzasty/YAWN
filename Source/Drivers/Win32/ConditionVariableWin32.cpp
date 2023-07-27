#include <YAWN/Threading/ConditionVariable.hpp>
#include <YAWN/Core/Assert.hpp>

#include "ThreadingWin32.hpp"

using namespace YAWN;

ConditionVariable::ConditionVariable() {
    mImpl = new ConditionVariableImpl();

    InitializeConditionVariable(&mImpl->ConditionVariable);
}

ConditionVariable::~ConditionVariable() {
    delete mImpl;
}

void ConditionVariable::NotifyOne() {
    WakeConditionVariable(&mImpl->ConditionVariable);
}

void ConditionVariable::NotifyAll() {
    WakeAllConditionVariable(&mImpl->ConditionVariable);
}

void ConditionVariable::Wait(const ExclusiveMutex& exclusiveMutex) {
    SleepConditionVariableCS(&mImpl->ConditionVariable, &exclusiveMutex.mImpl->CriticalSection, INFINITE);
}

void ConditionVariable::WaitRead(const ReadWriteMutex& readWriteMutex) {
    SleepConditionVariableSRW(&mImpl->ConditionVariable, &readWriteMutex.mImpl->SRWLock, INFINITE, CONDITION_VARIABLE_LOCKMODE_SHARED);
}

void ConditionVariable::WaitWrite(const ReadWriteMutex& readWriteMutex) {
    SleepConditionVariableSRW(&mImpl->ConditionVariable, &readWriteMutex.mImpl->SRWLock, INFINITE, 0);
}
