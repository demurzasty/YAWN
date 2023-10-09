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

            Ref<Type> type = GetOrAddType(hash);
            type->SetName(T::TypeName);
            type->SetBase(TypeID::Hash<typename T::Base>());
            type->SetId(hash);
            return Meta<T>(type);
        }

        template<typename T>
        static void Register() {
            Meta<T> meta = Reflect<T>();
            T::Register(meta);
        }

        template<typename T>
        static Ref<Type> GetType() {
            constexpr int hash = TypeID::Hash<T>();

            return GetType(hash);
        }

        static Ref<Type> GetType(int id);

        static Ref<Type> GetTypeByName(const String& name);

        template<typename T>
        static void EnumerateTypesOfBase(const Delegate<void(const Ref<Type>&)>& delegate) {
            constexpr int hash = TypeID::Hash<T>();

            EnumerateTypesOfBase(hash, delegate);
        }

        static void EnumerateTypesOfBase(int base, const Delegate<void(const Ref<Type>&)>& delegate);

    private:
        static Ref<Type> GetOrAddType(int id);

        static Map<int, Ref<Type>> sTypes;
    };
}
