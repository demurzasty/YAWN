#pragma once 

#include "Utility.hpp"

namespace YAWN {
    constexpr struct InPlaceTagType {} InPlaceTag = InPlaceTagType();
}

inline void* operator new(size_t, void* ptr, YAWN::InPlaceTagType) noexcept {
    return ptr;
}

inline void operator delete(void*, void*, YAWN::InPlaceTagType) noexcept {
    return;
}

namespace YAWN {
    class Memory {
    public:
        static void* Allocate(int size);

        static void* Reallocate(void* data, int size);

        static void Deallocate(void* data);

        static void Copy(void* dst, const void* src, int size);

        static int Compare(const void* mem1, const void* mem2, int size);

        template<typename T, typename... Args>
        static T* Construct(T* data, Args&&... args) {
            return new (data, InPlaceTag) T(Utility::Forward<Args>(args)...);
        }

        template<typename T>
        static void Destroy(T* data) {
            data->~T();
        }
    };
}
