#pragma once 

#include "../Runtime/Variant.hpp"

namespace YAWN {
    class Field : public Reference {
    public:
        Field() = default;

        Field(const String& name, void (*setter)(void*, const Variant&), void (*getter)(const void*, Variant&), VariantType type);

        void Set(void* instance, const Variant& value) const;

        void Get(const void* instance, Variant& value) const;

        Variant Get(const void* instance) const;

        bool IsAssignable() const;

        const String& GetName() const;

        VariantType GetType() const;

    private:
        String mName;
        void (*mSetter)(void*, const Variant&) = nullptr;
        void (*mGetter)(const void*, Variant&) = nullptr;
        VariantType mType = VariantType::Null;
    };
}
