#pragma once 

#include "ThreadPool.hpp"
#include "ReadWriteMutex.hpp"
#include "../Core/Optional.hpp"

namespace YAWN {
    template<typename T>
    class Task : public Reference {
        YAWN_OBJECT(Task<T>, Reference);

    public:
        Task(const Delegate<T()>& delegate) : mDelegate(delegate) {
            YAWN_ASSERT(mDelegate);

            Delegate<void()> worker;
            worker.Connect<&Task<T>::Worker>(*this);

            mMutex.WriteLock();

            ThreadPool::Submit(worker);
        }

        Task(const Task<T>&) = delete;

        Task(Task<T>&&) = delete;

        Task<T>& operator=(const Task<T>&) = delete;

        Task<T>& operator=(Task<T>&&) = delete;

        void Wait() {
            WriteLock lock(mMutex);
        }

        const T& GetValue() const {
            WriteLock lock(mMutex);

            return mValue.GetValue();
        }

        T& GetValue() {
            WriteLock lock(mMutex);

            return mValue.GetValue();
        }

    private:
        void Worker() {
            if (mDelegate) {
                mValue = mDelegate();
            }

            mMutex.WriteUnlock();
        }

    private:
        Delegate<T()> mDelegate;
        mutable ReadWriteMutex mMutex;
        Optional<T> mValue;
    };
}
