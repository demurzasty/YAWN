#pragma once 

#include "../Runtime/Delegate.hpp"
#include "../Runtime/Reference.hpp"

namespace YAWN {
    struct ThreadImpl;

    class Thread : public Reference {
        YAWN_OBJECT(Thread, Reference);

    public:
        static int GetHardwareConcurrency();

        Thread(const Delegate<void()>& delegate);

        ~Thread();

        void Wait();

    private:
        ThreadImpl* mImpl = nullptr;
        Delegate<void()> mDelegate;
    };
};
