#pragma once 

#include "String.hpp"

namespace YAWN {
    class FNV1a {
    public:
        template<typename T>
        static constexpr int Hash(const T* data, int size) {
            unsigned int hash = 0x811c9dc5;
            for (int i = 0; i < size; ++i) {
                hash ^= data[i];
                hash *= 16777619;
            }
            return int(hash);
        }

        static inline int Hash(const String& string) {
            return Hash(string.GetData(), string.GetSize());
        }

        template<typename T, int Length>
        static constexpr int Hash(const T(&data)[Length]) {
            return Hash(data, Length - 1);
        }
    };
}
