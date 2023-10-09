#pragma once 

#include "Array.hpp"

namespace YAWN {
    template<typename TKey, typename TValue>
    struct KeyValue {
        KeyValue() = default;

        KeyValue(const TKey& key, const TValue& value) : Key(key), Value(value) {}

        TKey Key = TKey();
        TValue Value = TValue();
    };

    template<typename TKey, typename TValue>
    class Map {
    public:
        using KeyType = TKey;
        using ValueType = TValue;

        const TValue& operator[](const TKey& key) const {
            int index = BinarySearch(key);
            YAWN_ASSERT(index < mArray.GetSize() && mArray[index].Key == key);
            return mArray[index].Value;
        }

        TValue& operator[](const TKey& key) {
            int index = BinarySearch(key);
            YAWN_ASSERT(index < mArray.GetSize() && mArray[index].Key == key);
            return mArray[index].Value;
        }

        bool Contains(const TKey& key) const {
            int index = BinarySearch(key);
            return index < mArray.GetSize() && mArray[index].Key == key;
        }

        TValue& Add(const TKey& key, const TValue& value) {
            int index = BinarySearch(key);
            YAWN_ASSERT(index >= mArray.GetSize() || mArray[index].Key != key);
            return mArray.Insert(index, KeyValue<TKey, TValue>(key, value)).Value;
        }

        TValue& GetOrAdd(const TKey& key) {
            int index = BinarySearch(key);
            if (index >= mArray.GetSize() || mArray[index].Key != key) {
                return mArray.Insert(index, KeyValue<TKey, TValue>(key, TValue())).Value;
            }
            return mArray[index].Value;
        }

        TValue* TryGet(const TKey& key) {
            int index = BinarySearch(key);
            if (index >= mArray.GetSize() || mArray[index].Key != key) {
                return nullptr;
            }
            return &mArray[index].Value;
        }

        bool TryGet(const TKey& key, TValue& value) {
            int index = BinarySearch(key);
            if (index >= mArray.GetSize() || mArray[index].Key != key) {
                return false;
            }

            value = mArray[index].Value;
            return true;
        }

        template<typename TFunc>
        TValue* TryGet(TFunc func) {
            for (int i = 0; i < mArray.GetSize(); ++i) {
                if (func(mArray[i].Value)) {
                    return &mArray[i].Value;
                }
            }
            return nullptr;
        }

        void Remove(const TKey& key) {
            int index = BinarySearch(key);
            if (index < mArray.GetSize() && mArray[index].Key == key) {
                mArray.RemoveAt(index);
            }
        }

        void Clear() {
            mArray.Clear();
        }

        bool IsEmpty() const {
            return mArray.IsEmpty();
        }

        const KeyValue<TKey, TValue>* GetData() const {
            return mArray.GetData();
        }

        int GetSize() const {
            return mArray.GetSize();
        }

        int GetCapacity() const {
            return mArray.GetCapacity();
        }

    public:
        KeyValue<TKey, TValue>* begin() { return mArray.begin(); }
        const KeyValue<TKey, TValue>* begin() const { return mArray.begin(); }

        KeyValue<TKey, TValue>* end() { return mArray.end(); }
        const KeyValue<TKey, TValue>* end() const { return mArray.end(); }

    private:
        int BinarySearch(const TKey& key) const {
            int low = 0, high = mArray.GetSize() - 1;
            while (low <= high) {
                int mid = (low + high) / 2;
                if (key == mArray[mid].Key) {
                    return mid;
                } else if (key > mArray[mid].Key) {
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }
            return low;
        }

    private:
        Array<KeyValue<TKey, TValue>> mArray;
    };
}
