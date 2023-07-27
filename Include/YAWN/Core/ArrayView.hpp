#pragma once 

#include "Array.hpp"

namespace YAWN {
    template<typename T>
    class ArrayView {
    public:
        constexpr ArrayView() = default;

        constexpr ArrayView(T* data, int size) : mData(data), mSize(size) {}

        constexpr ArrayView(const Array<typename RemoveConst<T>::Type>& array) : mData(array.GetData()), mSize(array.GetSize()) {}

        constexpr ArrayView(const Array<typename AddConst<T>::Type>& array) : mData(array.GetData()), mSize(array.GetSize()) {}

        constexpr ArrayView(Array<typename RemoveConst<T>::Type>& array) : mData(array.GetData()), mSize(array.GetSize()) {}

        constexpr ArrayView(Array<typename AddConst<T>::Type>& array) : mData(array.GetData()), mSize(array.GetSize()) {}

        constexpr ArrayView(ArrayView<typename RemoveConst<T>::Type>& array) : mData(array.GetData()), mSize(array.GetSize()) {}

        constexpr ArrayView(ArrayView<typename AddConst<T>::Type>& array) : mData(array.GetData()), mSize(array.GetSize()) {}

        template<int Size>
        constexpr ArrayView(T(&data)[Size]) : mData(data), mSize(Size) {}

        const T& operator[](int index) const {
            YAWN_ASSERT(index >= 0 && index < mSize);
            return mData[index];
        }

        T& operator[](int index) {
            YAWN_ASSERT(index >= 0 && index < mSize);
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

        T* GetData() { return mData; }

        const T* GetData() const { return mData; }

        int GetSize() const { return mSize; }

        int GetSizeInBytes() const { return sizeof(T) * mSize; }

    public:
        T* begin() { return mData; }
        const T* begin() const { return mData; }

        T* end() { return mData + mSize; }
        const T* end() const { return mData + mSize; }

    private:
        T* mData = nullptr;
        int mSize = 0;
    };
}
