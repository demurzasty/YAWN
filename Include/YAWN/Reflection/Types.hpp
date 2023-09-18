#pragma once 

#include "Type.hpp"
#include "Meta.hpp"
#include "TypeID.hpp"

#include "../Runtime/Delegate.hpp"
#include "../Runtime/Variant.hpp"

namespace YAWN {
    class Types {
    public:
        template<typename T>
        static Meta<T> Reflect() {
            constexpr int hash = TypeID::Hash<T>();

            if (sTypes.Contains(hash)) {
                return Meta<T>(sTypes[hash]);
            }

            return Meta<T>(sTypes.Add(hash, Type()));
        }

        template<typename T>
        static void Register() {
            Meta<T> meta = Reflect<T>();
            T::Register(meta);
        }

        template<typename T>
        static Type& GetType() {
            constexpr int hash = TypeID::Hash<T>();

            return sTypes[hash];
        }

        static Type& GetType(int id);

        static Type* GetTypeByName(const String& name);

        template<typename T>
        static void EnumerateTypesOfBase(const Delegate<void(const Type&)>& delegate) {
            constexpr int hash = TypeID::Hash<T>();

            EnumerateTypesOfBase(hash, delegate);
        }

        static void EnumerateTypesOfBase(int base, const Delegate<void(const Type&)>& delegate);

    private:
        static Map<int, Type> sTypes;
    };
}
