#pragma once 

#include "../Core/Map.hpp"
#include "../Core/Array.hpp"
#include "../Core/String.hpp"
#include "../Math/Vector2.hpp"
#include "../Math/Vector3.hpp"
#include "../Math/Vector4.hpp"
#include "Reference.hpp"

namespace YAWN {
    template<typename TReference>
    class Ref;

    class Reference;

    enum class VariantType {
        /**
         * @brief Hold nothing.
         */
        Null,

        /**
         * @brief Hold bool.
         */
        Boolean,

        /**
         * @brief Holds long long (int64).
         */
        Integer,

        /**
         * @brief Holds double.
         */
        FloatingPoint,

        /**
         * @brief Hold String.
         */
        String,

        /**
         * @brief Holds Array<Variant>.
         */
        Array,

        /**
         * @brief Holds Map<String, Variant>.
         */
        Map,

        /**
         * @brief Holds Ref<Reference>.
         */
        Object,

        /**
         * @brief Holds Vector2.
         */
        Vector2,

        /**
         * @brief Holds Vector3.
         */
        Vector3,

        /**
         * @brief Holds Vector4.
         */
        Vector4
    };

    class Variant {
        static constexpr int MaxSize = MaxTypesSize<
            bool,
            long long,
            double,
            String,
            Array<Variant>,
            Map<String, Variant>,
            Ref<Reference>,
            Vector2,
            Vector3,
            Vector4
        >::Value;

    public:
        static Variant MakeArray();

        static Variant MakeMap();

        Variant();

        Variant(bool value);

        Variant(int value);

        Variant(long long value);

        Variant(float value);

        Variant(double value);

        Variant(const String& value);

        Variant(String&& value);

        Variant(const wchar_t* value);

        Variant(const Array<Variant>& value);

        Variant(Array<Variant>&& value) noexcept;

        template<typename T>
        Variant(const Array<T>& value) : mType(VariantType::Array) {
            Array<Variant> data;
            for (const T& element : value) {
                data.Add(element);
            }

            Memory::Construct((Array<Variant>*)mData, data);
        }

        template<typename T>
        Variant(const ArrayView<T>& value) : mType(VariantType::Array) {
            Array<Variant> data;
            for (const T& element : value) {
                data.Add(element);
            }

            Memory::Construct((Array<Variant>*)mData, data);
        }

        Variant(const Map<String, Variant>& value);

        Variant(Map<String, Variant>&& value) noexcept;

        Variant(const Ref<Reference>& value);

        template<typename TReference>
        Variant(const Ref<TReference>& value) : Variant(Ref<Reference>(value.Get())) { }

        Variant(const Vector2& value);

        Variant(const Vector3& value);

        Variant(const Vector4& value);

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

        template<typename T>
        operator const Array<T>() const {
            Array<T> data;
            for (const Variant& value : AsArray()) {
                data.Add(value);
            }
            return data;
        }

        operator const Map<String, Variant>& () const;

        operator const Vector2& () const;

        operator const Vector3& () const;

        operator const Vector4& () const;

        operator const Ref<Reference>& () const;

        template<typename T>
        operator const Ref<T> () const {
            // TODO: Fix up casting.
            return (T*)(AsObject().Get());
        }

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

        Ref<Reference>& AsObject();

        const Ref<Reference>& AsObject() const;

        const Vector2& AsVector2() const;

        const Vector3& AsVector3() const;

        const Vector4& AsVector4() const;

        VariantType GetType() const;

    private:
        void Construct(const Variant& variant);

        void Destroy();

    private:
        VariantType mType = VariantType::Null;
        char mData[MaxSize];
    };
}
