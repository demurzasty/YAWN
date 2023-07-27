#pragma once 

#include "Config.hpp"

namespace YAWN {
    template<int Arg0, int... Args>
    struct StaticMax;

    template<int Arg>
    struct StaticMax<Arg> {
        static constexpr int Value = Arg;
    };

    template<int Arg0, int Arg1, int ... Args>
    struct StaticMax<Arg0, Arg1, Args...> {
        static constexpr int Value = Arg0 >= Arg1 ? StaticMax<Arg0, Args...>::Value : StaticMax<Arg1, Args...>::Value;
    };

    template<typename... Types>
    struct MaxTypesSize {
        static constexpr int Value = StaticMax<sizeof(Types)...>::Value;
    };

    template<typename T>
    struct AddConst {
        using Type = const T;
    };

    template<typename T>
    struct RemoveConst {
        using Type = T;
    };

    template<typename T>
    struct RemoveConst<const T> {
        using Type = T;
    };

    template<typename T>
    struct RemoveReference {
        using Type = T;
    };

    template<typename T>
    struct RemoveReference<T&> {
        using Type = T;
    };

    template<typename T>
    struct RemoveReference<T&&> {
        using Type = T;
    };

    template<typename T>
    struct RemoveConstReference {
        using Type = typename RemoveConst<typename RemoveReference<T>::Type>::Type;
    };

    template<typename T>
    class Storage {
        unsigned char mData[sizeof(T)];
    };
}
