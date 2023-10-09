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
            constexpr TypeId hash = TypeId::From<T>();

            Ref<Type> type = GetOrAddType(hash);
            type->SetName(T::TypeName);
            type->SetBase(TypeId::From<typename T::Base>());
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
            constexpr TypeId hash = TypeId::From<T>();

            return GetType(hash);
        }

        static Ref<Type> GetType(TypeId id);

        static Ref<Type> GetTypeByName(const String& name);

        template<typename T>
        static void EnumerateTypesOfBase(const Delegate<void(const Ref<Type>&)>& delegate) {
            constexpr TypeId typeId = TypeId::From<T>();

            EnumerateTypesOfBase(typeId, delegate);
        }

        static void EnumerateTypesOfBase(TypeId base, const Delegate<void(const Ref<Type>&)>& delegate);

    private:
        static Ref<Type> GetOrAddType(TypeId id);

        static Map<TypeId, Ref<Type>> sTypes;
    };
}
