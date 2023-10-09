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

    template<typename T>
    struct IsRef {
        typedef char Yes[1];
        typedef char No[2];

        template<typename C, typename D = typename C::ReferenceType>
        static Yes& Test(C*);

        template<typename C>
        static No& Test(...);

    public:
        static constexpr bool Value = sizeof(Test<T>(nullptr)) == sizeof(Yes);
    };

    template<typename T>
    struct HasKeyType {
        typedef char Yes[1];
        typedef char No[2];

        template<typename C, typename D = typename C::KeyType>
        static Yes& Test(C*);

        template<typename C>
        static No& Test(...);

    public:
        static constexpr bool Value = sizeof(Test<T>(nullptr)) == sizeof(Yes);
    };

    template<typename T>
    struct HasValueType {
        typedef char Yes[1];
        typedef char No[2];

        template<typename C, typename D = typename C::ValueType>
        static Yes& Test(C*);

        template<typename C>
        static No& Test(...);

    public:
        static constexpr bool Value = sizeof(Test<T>(nullptr)) == sizeof(Yes);
    };

    template<typename T>
    struct IsArray {
        static constexpr bool Value = HasValueType<T>::Value && !HasKeyType<T>::Value;
    };

    template<typename T>
    struct IsMap {
        static constexpr bool Value = HasValueType<T>::Value && HasKeyType<T>::Value;
    };
}
