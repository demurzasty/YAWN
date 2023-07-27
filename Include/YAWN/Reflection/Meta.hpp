#pragma once 

#include "Type.hpp"
#include "TypeID.hpp"

namespace YAWN {
    template<typename T>
    class Meta {
    public:
        Meta(Type& type) : mType(type) {
        }

        void SetConstructable() {
            mType.SetConstructor([]() -> Ref<Reference> {
                return new T();
            });
        }

        void SetName(const String& name) {
            mType.SetName(name);
        }

        void AddTag(const String& tag) {
            mType.AddTag(tag);
        }

        template<typename T>
        void SetBase() {
            mType.SetBase(TypeID::Hash<T>());
        }

        template<auto VField>
        void AddField(const String& name) {
            auto setter = [](void* instance, const Variant& value) {
                (((T*)instance)->*VField) = value;
            };

            auto getter = [](const void* instance, Variant& value) {
                value = (((T*)instance)->*VField);
            };

            mType.AddField(name, Field(setter, getter));
        }

        template<auto VSetter, auto VGetter>
        void AddField(const String& name) {
            auto setter = [](void* instance, const Variant& value) {
                (((T*)instance)->*VSetter)(value);
            };

            auto getter = [](const void* instance, Variant& value) {
                value = (((T*)instance)->*VGetter)();
            };

            mType.AddField(name, Field(setter, getter));
        }

    private:
        Type& mType;
    };
}