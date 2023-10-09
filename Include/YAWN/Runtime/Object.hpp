#pragma once 

#include "../Reflection/TypeId.hpp"

#define YAWN_OBJECT(TSelf, TBase) \
    public: \
        using Base = TBase; \
        static constexpr wchar_t TypeName[] = L#TSelf; \
        virtual const wchar_t* GetTypeName() const { \
            return L#TSelf; \
        } \
        virtual TypeId GetTypeId() const override { \
            constexpr TypeId typeId = YAWN::TypeId::From<TSelf>(); \
            return typeId; \
        } \
    protected: \
        virtual bool _IsInstanceOf(TypeId id) const override { \
            constexpr TypeId typeId = YAWN::TypeId::From<TSelf>(); \
            return id == typeId || TBase::_IsInstanceOf(id); \
        } 

namespace YAWN {
    class Object {
    public:
        static constexpr wchar_t TypeName[] = L"Object"; \

        virtual ~Object() = default;

        virtual const wchar_t* GetTypeName() const;

        virtual TypeId GetTypeId() const;

        template<typename T>
        bool IsInstanceOf() const {
            constexpr TypeId id = TypeId::From<T>();
            return _IsInstanceOf(id);
        }

    protected:
        virtual bool _IsInstanceOf(TypeId id) const;
    };

    template<typename TTo>
    TTo* CastTo(Object* object) {
        if (object && object->IsInstanceOf<TTo>()) {
            return (TTo*)object;
        }

        return nullptr;
    }
}
