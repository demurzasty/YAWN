#include <YAWN/Runtime/Reference.hpp>
#include <YAWN/Core/Assert.hpp>

using namespace YAWN;

Reference::~Reference() {
    YAWN_ASSERT(mCounter == 0);
}

void Reference::IncRef() {
    ++mCounter;
}

void Reference::DecRef() {
    if (--mCounter == 0) {
        delete this;
    }
}

int Reference::GetUseCount() const {
    return mCounter;
}
