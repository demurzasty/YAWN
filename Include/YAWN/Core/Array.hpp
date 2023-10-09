#pragma once 

#include "Memory.hpp"
#include "Assert.hpp"

namespace YAWN {
    template<typename T>
    class Array {
    public:
        using ValueType = T;

        Array() = default;

        explicit Array(int size) : mSize(size), mCapacity(size) {
            YAWN_ASSERT(size >= 0);

            if (mSize > 0) {
                mData = (T*)Memory::Allocate(sizeof(T) * mSize);

                for (int i = 0; i < mSize; ++i) {
                    Memory::Construct(&mData[i]);
                }
            }
        }

        Array(const T* data, int size) : mSize(size), mCapacity(size) {
            if (mSize > 0) {
                mData = (T*)Memory::Allocate(sizeof(T) * mSize);

                for (int i = 0; i < mSize; ++i) {
                    Memory::Construct(&mData[i], data[i]);
                }
            }
        }

        Array(const Array<T>& array) : mSize(array.mSize), mCapacity(array.mSize) {
            if (mSize > 0) {
                mData = (T*)Memory::Allocate(sizeof(T) * mSize);

                for (int i = 0; i < mSize; ++i) {
                    Memory::Construct(&mData[i], array.mData[i]);
                }
            }
        }

        Array(Array<T>&& array) noexcept : mData(array.mData), mSize(array.mSize), mCapacity(array.mSize) {
            array.mData = nullptr;
            array.mCapacity = 0;
            array.mSize = 0;
        }

        ~Array() {
            for (int i = 0; i < mSize; ++i) {
                Memory::Destroy(&mData[i]);
            }

            Memory::Deallocate(mData);
        }

        Array<T>& operator=(const Array<T>& array) {
            for (int i = 0; i < mSize; ++i) {
                Memory::Destroy(&mData[i]);
            }

            mSize = array.mSize;

            EnsureCapacity(mSize);

            for (int i = 0; i < mSize; ++i) {
                Memory::Construct(&mData[i], array.mData[i]);
            }

            return *this;
        }

        Array<T>& operator=(Array<T>&& array) noexcept {
            for (int i = 0; i < mSize; ++i) {
                Memory::Destroy(&mData[i]);
            }
            Memory::Deallocate(mData);

            mData = array.mData;
            mSize = array.mSize;
            mCapacity = array.mCapacity;

            array.mData = nullptr;
            array.mCapacity = 0;
            array.mSize = 0;

            return *this;
        }

        const T& operator[](int index) const {
            YAWN_ASSERT(index >= 0 && index < mSize);
            return mData[index];
        }

        T& operator[](int index) {
            YAWN_ASSERT(index >= 0 && index < mSize);
            return mData[index];
        }

        T& Add(const T& value) {
            EnsureCapacity(mSize + 1);

            Memory::Construct(&mData[mSize], value);

            return mData[mSize++];
        }

        T& Add(T&& value) {
            EnsureCapacity(mSize + 1);

            Memory::Construct(&mData[mSize], Utility::Forward<T>(value));

            return mData[mSize++];
        }

        void AddRange(const T* data, int size) {
            for (int i = 0; i < size; ++i) {
                Add(data[i]);
            }
        }

        T& Insert(int index, const T& value) {
            YAWN_ASSERT(index >= 0 && index <= mSize);

            EnsureCapacity(mSize + 1);

            for (int i = mSize; i > index; --i) {
                mData[i] = Utility::Move(mData[i - 1]);
            }

            Memory::Construct(&mData[index], value);

            mSize++;
            return mData[index];
        }

        T& Insert(int index, T&& value) {
            YAWN_ASSERT(index >= 0 && index <= mSize);

            EnsureCapacity(mSize + 1);

            for (int i = mSize; i > index; --i) {
                Memory::Construct(&mData[i], Utility::Move(mData[i - 1]));
            }

            Memory::Construct(&mData[index], Utility::Forward<T>(value));

            ++mSize;

            return mData[index];
        }

        int Find(const T& value) const {
            for (int i = 0; i < mSize; ++i) {
                if (mData[i] == value) {
                    return i;
                }
            }

            return -1;
        }

        void RemoveAt(int index) {
            YAWN_ASSERT(index >= 0 && index < mSize);

            Memory::Destroy(&mData[index]);

            --mSize;

            for (int i = index; i < mSize; ++i) {
                mData[i] = Utility::Move(mData[i + 1]);
            }
        }

        void Remove(const T& value) {
            int index = Find(value);
            if (index > -1) {
                RemoveAt(index);
            }
        }

        void Pop() {
            YAWN_ASSERT(mSize > 0);

            RemoveAt(mSize - 1);
        }

        void Clear() {
            for (int i = 0; i < mSize; ++i) {
                Memory::Destroy(&mData[i]);
            }
            mSize = 0;
        }

        void Resize(int newSize, const T& fillValue = T()) {
            YAWN_ASSERT(newSize >= 0);

            for (int i = newSize; i < mSize; ++i) {
                Memory::Destroy(&mData[i]);
            }

            EnsureCapacity(newSize);

            for (int i = mSize; i < newSize; ++i) {
                Memory::Construct(&mData[i], fillValue);
            }

            mSize = newSize;
        }

        void Expand(int newSize, const T& fillValue = T()) {
            YAWN_ASSERT(newSize >= 0);

            if (newSize > mSize) {
                Resize(newSize, fillValue);
            }
        }

        void Reserve(int newCapacity) {
            YAWN_ASSERT(newCapacity >= 0);

            EnsureCapacity(newCapacity);
        }

        T& GetFront() {
            YAWN_ASSERT(mSize > 0);
            return mData[0];
        }

        const T& GetFront() const {
            YAWN_ASSERT(mSize > 0);
            return mData[0];
        }

        T& GetBack() {
            YAWN_ASSERT(mSize > 0);
            return mData[mSize - 1];
        }

        const T& GetBack() const {
            YAWN_ASSERT(mSize > 0);
            return mData[mSize - 1];
        }

        const T* GetData() const {
            return mData;
        }

        T* GetData() {
            return mData;
        }

        int GetCapacity() const {
            return mCapacity;
        }

        int GetSize() const {
            return mSize;
        }

        int GetSizeInBytes() const {
            return mSize * sizeof(T);
        }

        bool IsEmpty() const {
            return mSize == 0;
        }

    public:
        T* begin() { return mData; }
        const T* begin() const { return mData; }

        T* end() { return mData + mSize; }
        const T* end() const { return mData + mSize; }

    private:
        void EnsureCapacity(int newSize) {
            if (newSize > mCapacity) {
                do {
                    mCapacity = (mCapacity ? (mCapacity << 1) : 4);
                } while (newSize > mCapacity);

                mData = (T*)Memory::Reallocate(mData, sizeof(T) * mCapacity);
            }
        }

    private:
        T* mData = nullptr;
        int mCapacity = 0;
        int mSize = 0;
    };
}
