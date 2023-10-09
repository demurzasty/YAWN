#pragma once 

#include "Pool.hpp"
#include "../Core/TypeTraits.hpp"

namespace YAWN {
    /*
    template<typename T>
    class Arena : protected Pool {
    public:
        ~Arena() {
            const int* pool = Pool::GetData();
            for (int i = 0; i < Pool::GetSize(); ++i) {
                if (pool[i] == i) {
                    Memory::Destroy((T*)&mData[i]);
                }
            }
        }

        template<typename Func>
        void ForEach(Func func) {
            const int* pool = Pool::GetData();
            for (int i = 0; i < Pool::GetSize(); ++i) {
                func(i, *(T*)&mData[i]);
            }
        }

        template<typename Func>
        void ForEach(Func func) const {
            const int* pool = Pool::GetData();
            for (int i = 0; i < Pool::GetSize(); ++i) {
                func(i, *(const T*)&mData[i]);
            }
        }

        template<typename... Args>
        int Create(Args&&... args) {
            int id = Acquire();

            if (id == mData.GetSize()) {
                mData.Add(Storage<T>());
            }

            Memory::Construct((T*)&mData[id], Utility::Forward<Args>(args)...);

            return id;
        }

        void Destroy(int id) {
            YAWN_ASSERT(Pool::IsValid(id));

            Memory::Destroy((T*)&mData[id]);

            Pool::Dispose(id);
        }

        bool IsValid(int id) const {
            return Pool::IsValid(id);
        }

        int GetSize() const {
            return Pool::GetSize();
        }

        T* GetData() {
            return (T*)mData.GetData();
        }

        const T* GetData() const {
            return (T*)mData.GetData();
        }

    private:
        Array<Storage<T>> mData;
    };
    */
}
