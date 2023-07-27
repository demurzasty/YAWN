#include <YAWN/Threading/ConditionVariable.hpp>

using namespace YAWN;

void ConditionVariable::Wait(const ExclusiveMutex& exclusiveMutex, const Delegate<bool()>& predicate) {
    while (!predicate()) {
        Wait(exclusiveMutex);
    }
}
