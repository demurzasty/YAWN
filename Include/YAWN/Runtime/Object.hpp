#pragma once 

#include "../Reflection/TypeID.hpp"

#define YAWN_OBJECT(TSelf, TBase) \
    public: \
        using Base = TBase; \
        static constexpr wchar_t TypeName[] = L#TSelf; \
        virtual const wchar_t* GetTypeName() const { \
            return L#TSelf; \
        } \
        virtual int GetTypeId() const override { \
            constexpr int typeId = YAWN::TypeID::Hash<TSelf>(); \
            return typeId; \
        } \
    protected: \
        virtual bool _IsInstanceOf(int id) const override { \
            constexpr int typeId = YAWN::TypeID::Hash<TSelf>(); \
            return id == typeId || TBase::_IsInstanceOf(id); \
        } 

namespace YAWN {
    class Object {
    public:
        virtual ~Object() = default;

        virtual const wchar_t* GetTypeName() const;

        virtual int GetTypeId() const;

        template<typename T>
        bool IsInstanceOf() const {
            constexpr int id = TypeID::Hash<T>();
            return _IsInstanceOf(id);
        }

    protected:
        virtual bool _IsInstanceOf(int id) const;
    };

    template<typename TTo>
    TTo* CastTo(Object* object) {
        if (object && object->IsInstanceOf<TTo>()) {
            return (TTo*)object;
        }

        return nullptr;
    }
}
