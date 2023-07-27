#pragma once 

#include "../Core/Array.hpp"

namespace YAWN {
    class Pool {
    public:
        static constexpr int None = -1;

    public:
        int Acquire();

        void Dispose(int id);

        bool IsValid(int id) const;

        int GetSize() const;

        const int* GetData() const;

    private:
        Array<int> mPool;
        int mDisposed = None;
    };
}
