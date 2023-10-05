#pragma once 

#include "Type.hpp"
#include "TypeID.hpp"

namespace YAWN {
    template<typename T>
    class Meta {
    public:
        Meta(const Ref<Type>& type) : mType(type) {
            type->SetName(T::TypeName);
            type->SetBase(TypeID::Hash<T::Base>());
            type->SetId(TypeID::Hash<T>());
        }

        void SetConstructable() {
            mType->SetConstructor([]() -> Ref<Reference> {
                return new T();
            });
        }

        void SetName(const String& name) {
            mType->SetName(name);
        }

        void AddTag(const String& tag) {
            mType->AddTag(tag);
        }

        template<typename TBase>
        void SetBase() {
            mType->SetBase(TypeID::Hash<TBase>());
        }

        template<auto VField>
        void AddField(const String& name) {
            auto setter = [](void* instance, const Variant& value) {
                (((T*)instance)->*VField) = value;
            };

            auto getter = [](const void* instance, Variant& value) {
                value = (((T*)instance)->*VField);
            };

            mType->AddField(new Field(name, setter, getter));
        }

        template<auto VSetter, auto VGetter>
        void AddField(const String& name) {
            constexpr VariantType type = VariantMethodReturnTypeDetector<VGetter>::Type;

            auto setter = [](void* instance, const Variant& value) {
                (((T*)instance)->*VSetter)(value);
            };

            auto getter = [](const void* instance, Variant& value) {
                value = (((T*)instance)->*VGetter)();
            };

            mType->AddField(new Field(name, setter, getter, type));
        }

    private:
        Ref<Type> mType;
    };
}