#pragma once 

#include "TypeTraits.hpp"

namespace YAWN {
    class Utility {
    public:
        template<typename T>
        static constexpr T&& Forward(typename RemoveReference<T>::Type& arg) noexcept {
            return static_cast<T&&>(arg);
        }

        template<typename T>
        static constexpr T&& Forward(typename RemoveReference<T>::Type&& arg) noexcept {
            return static_cast<T&&>(arg);
        }

        template<typename T>
        static constexpr typename RemoveReference<T>::Type&& Move(T&& arg) noexcept {
            return static_cast<typename RemoveReference<T>::Type&&>(arg);
        }
    };
}
