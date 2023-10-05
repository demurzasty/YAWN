#pragma once 

#include "../Runtime/Variant.hpp"

namespace YAWN {
    class Field {
    public:
        Field() = default;

        Field(void (*setter)(void*, const Variant&), void (*getter)(const void*, Variant&), VariantType type);

        void Set(void* instance, const Variant& value) const;

        void Get(const void* instance, Variant& value) const;

        Variant Get(const void* instance) const;

        bool IsAssignable() const;

        VariantType GetType() const;

    private:
        void (*mSetter)(void*, const Variant&) = nullptr;
        void (*mGetter)(const void*, Variant&) = nullptr;
        VariantType mType = VariantType::Null;
    };
}
