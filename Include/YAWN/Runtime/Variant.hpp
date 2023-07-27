#pragma once 

#include "../Core/Map.hpp"
#include "../Core/Array.hpp"
#include "../Core/String.hpp"
#include "Reference.hpp"

namespace YAWN {
    template<typename TReference>
    class Ref;

    class Reference;

    enum class VariantType {
        Null,
        Boolean,
        Integer,
        FloatingPoint,
        String,
        Array,
        Map,
        Object
    };

    class Variant {
        static constexpr int MaxSize = MaxTypesSize<bool, long long, double, String, Array<Variant>, Map<String, Variant>, Ref<Reference>>::Value;

    public:
        static Variant MakeArray();

        static Variant MakeMap();

        Variant();

        Variant(bool value);

        Variant(int value);

        Variant(long long value);

        Variant(float value);

        Variant(double  value);

        Variant(const String& value);

        Variant(String&& value);

        Variant(const Array<Variant>& value);

        Variant(Array<Variant>&& value) noexcept;

        Variant(const Map<String, Variant>& value);

        Variant(Map<String, Variant>&& value) noexcept;

        Variant(const Ref<Reference>& value);

        Variant(const Variant& variant);

        Variant(Variant&& variant) noexcept;

        ~Variant();

        Variant& operator=(const Variant& variant);

        Variant& operator=(Variant&& variant) noexcept;

        const Variant& operator[](int index) const;

        const Variant& operator[](const String& key) const;

        operator bool() const;

        operator int() const;

        operator long long() const;

        operator float() const;

        operator double() const;

        operator const String&() const;

        operator const Array<Variant>&() const;

        operator const Map<String, Variant>& () const;

        bool AsBool() const;

        int AsInt() const;

        long long AsLongLong() const;

        float AsFloat() const;

        double AsDouble() const;

        const String& AsString() const;

        Array<Variant>& AsArray();

        const Array<Variant>& AsArray() const;

        Map<String, Variant>& AsMap();

        const Map<String, Variant>& AsMap() const;

        const Ref<Reference>& AsObject() const;

        VariantType GetType() const;

    private:
        void Construct(const Variant& variant);

        void Destroy();

    private:
        VariantType mType = VariantType::Null;
        char mData[MaxSize];
    };
}
