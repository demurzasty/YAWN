#include <YAWN/Runtime/Variant.hpp>
#include <YAWN/Runtime/Reference.hpp>

using namespace YAWN;

Variant Variant::MakeArray() {
    Variant variant;
    variant.mType = VariantType::Array;
    Memory::Construct((Array<Variant>*)variant.mData);
    return variant;
}

Variant Variant::MakeMap() {
    Variant variant;
    variant.mType = VariantType::Map;
    Memory::Construct((Map<String, Variant>*)variant.mData);
    return variant;
}

Variant::Variant() : mData() {
}

Variant::Variant(bool value) : mType(VariantType::Boolean) {
    Memory::Construct((bool*)mData, value);
}

Variant::Variant(int value) : mType(VariantType::Integer) {
    Memory::Construct((long long*)mData, value);
}

Variant::Variant(long long value) : mType(VariantType::Integer) {
    Memory::Construct((long long*)mData, value);
}

Variant::Variant(float value) : mType(VariantType::FloatingPoint) {
    Memory::Construct((double*)mData, value);
}

Variant::Variant(double value) : mType(VariantType::FloatingPoint) {
    Memory::Construct((double*)mData, value);
}

Variant::Variant(const String& value) : mType(VariantType::String) {
    Memory::Construct((String*)mData, value);
}

Variant::Variant(String&& value) : mType(VariantType::String) {
    Memory::Construct((String*)mData, Utility::Forward<String>(value));
}

Variant::Variant(const wchar_t* value) : mType(VariantType::String) {
    Memory::Construct((String*)mData, value);
}

Variant::Variant(const Array<Variant>& value) : mType(VariantType::Array) {
    Memory::Construct((Array<Variant>*)mData, value);
}

Variant::Variant(Array<Variant>&& value) noexcept : mType(VariantType::Array) {
    Memory::Construct((Array<Variant>*)mData, Utility::Forward<Array<Variant>>(value));
}

Variant::Variant(const Map<String, Variant>& value) : mType(VariantType::Map) {
    Memory::Construct((Map<String, Variant>*)mData, value);
}

Variant::Variant(Map<String, Variant>&& value) noexcept : mType(VariantType::Map) {
    Memory::Construct((Map<String, Variant>*)mData, Utility::Forward<Map<String, Variant>>(value));
}

Variant::Variant(const Ref<Reference>& value) : mType(VariantType::Object) {
    Memory::Construct((Ref<Reference>*)mData, value);
}

Variant::Variant(const Vector2& value) : mType(VariantType::Vector2) {
    Memory::Construct((Vector2*)mData, value);
}

Variant::Variant(const Vector3& value) : mType(VariantType::Vector3) {
    Memory::Construct((Vector3*)mData, value);
}

Variant::Variant(const Vector4& value) : mType(VariantType::Vector4) {
    Memory::Construct((Vector4*)mData, value);
}

Variant::Variant(const Color4& value) : mType(VariantType::Color) {
    Memory::Construct((Color4*)mData, value);
}

Variant::Variant(const Variant& variant) : mData() {
    Construct(variant);
}

Variant::Variant(Variant&& variant) noexcept : mType(variant.mType) {
    Memory::Copy(mData, variant.mData, MaxSize);

    variant.mType = VariantType::Null;
}

Variant::~Variant() {
    Destroy();
}

Variant& Variant::operator=(const Variant& variant) {
    Destroy();

    Construct(variant);
    return *this;
}

Variant& Variant::operator=(Variant&& variant) noexcept {
    Destroy();

    mType = variant.mType;
    Memory::Copy(mData, variant.mData, MaxSize);

    variant.mType = VariantType::Null;

    return *this;
}

const Variant& Variant::operator[](int index) const {
    return AsArray()[index];
}

const Variant& Variant::operator[](const String& key) const {
    return AsMap()[key];
}

Variant::operator bool() const {
    return AsBool();
}

Variant::operator int() const {
    return AsInt();
}

Variant::operator long long() const {
    return AsLongLong();
}

Variant::operator float() const {
    return AsFloat();
}

Variant::operator double() const {
    return AsDouble();
}

Variant::operator const String& () const {
    return AsString();
}

Variant::operator const Array<Variant>& () const {
    return AsArray();
}

Variant::operator const Map<String, Variant>& () const {
    return AsMap();
}

Variant::operator const Vector2& () const {
    return AsVector2();
}

Variant::operator const Vector3& () const {
    return AsVector3();
}

Variant::operator const Vector4& () const {
    return AsVector4();
}

Variant::operator const Color4& () const {
    return AsColor();
}

Variant::operator const Ref<Reference>& () const {
    return AsObject();
}

bool Variant::AsBool() const {
    YAWN_ASSERT(mType == VariantType::Boolean);

    return *(const bool*)mData;
}

int Variant::AsInt() const {
    return (int)AsLongLong();
}

long long Variant::AsLongLong() const {
    YAWN_ASSERT(mType == VariantType::Integer);

    return *(const long long*)mData;
}

float Variant::AsFloat() const {
    return (float)AsDouble();
}

double Variant::AsDouble() const {
    YAWN_ASSERT(mType == VariantType::FloatingPoint);

    return *(const double*)mData;
}

const String& Variant::AsString() const {
    YAWN_ASSERT(mType == VariantType::String);

    return *(const String*)mData;
}

Array<Variant>& Variant::AsArray() {
    YAWN_ASSERT(mType == VariantType::Array);

    return *(Array<Variant>*)mData;
}

const Array<Variant>& Variant::AsArray() const {
    YAWN_ASSERT(mType == VariantType::Array);

    return *(const Array<Variant>*)mData;
}

Map<String, Variant>& Variant::AsMap() {
    YAWN_ASSERT(mType == VariantType::Map);

    return *(Map<String, Variant>*)mData;
}

const Map<String, Variant>& Variant::AsMap() const {
    YAWN_ASSERT(mType == VariantType::Map);

    return *(const Map<String, Variant>*)mData;
}

Ref<Reference>& Variant::AsObject() {
    YAWN_ASSERT(mType == VariantType::Object);

    return *(Ref<Reference>*)mData;
}

const Ref<Reference>& Variant::AsObject() const {
    YAWN_ASSERT(mType == VariantType::Object);

    return *(const Ref<Reference>*)mData;
}

const Vector2& Variant::AsVector2() const {
    YAWN_ASSERT(mType == VariantType::Vector2);

    return *(const Vector2*)mData;
}

const Vector3& Variant::AsVector3() const {
    YAWN_ASSERT(mType == VariantType::Vector3);

    return *(const Vector3*)mData;
}

const Vector4& Variant::AsVector4() const {
    YAWN_ASSERT(mType == VariantType::Vector4);

    return *(const Vector4*)mData;
}

const Color4& Variant::AsColor() const {
    YAWN_ASSERT(mType == VariantType::Color);

    return *(const Color4*)mData;
}


VariantType Variant::GetType() const {
    return mType;
}

void Variant::Construct(const Variant& variant) {
    mType = variant.mType;

    switch (mType) {
    case VariantType::Boolean:
        Memory::Construct((bool*)mData, variant.AsBool());
        break;
    case VariantType::Integer:
        Memory::Construct((long long*)mData, variant.AsLongLong());
        break;
    case VariantType::FloatingPoint:
        Memory::Construct((double*)mData, variant.AsDouble());
        break;
    case VariantType::String:
        Memory::Construct((String*)mData, variant.AsString());
        break;
    case VariantType::Array:
        Memory::Construct((Array<Variant>*)mData, variant.AsArray());
        break;
    case VariantType::Map:
        Memory::Construct((Map<String, Variant>*)mData, variant.AsMap());
        break;
    case VariantType::Object:
        Memory::Construct((Ref<Reference>*)mData, variant.AsObject());
        break;
    case VariantType::Vector2:
        Memory::Construct((Vector2*)mData, variant.AsVector2());
        break;
    case VariantType::Vector3:
        Memory::Construct((Vector3*)mData, variant.AsVector3());
        break;
    case VariantType::Vector4:
        Memory::Construct((Vector4*)mData, variant.AsVector4());
        break;
    case VariantType::Color:
        Memory::Construct((Color4*)mData, variant.AsColor());
        break;
    }
}

void Variant::Destroy() {
    switch (mType) {
    case VariantType::Boolean:
        Memory::Destroy((bool*)mData);
        break;
    case VariantType::Integer:
        Memory::Destroy((long long*)mData);
        break;
    case VariantType::FloatingPoint:
        Memory::Destroy((double*)mData);
        break;
    case VariantType::String:
        Memory::Destroy((String*)mData);
        break;
    case VariantType::Array:
        Memory::Destroy((Array<Variant>*)mData);
        break;
    case VariantType::Map:
        Memory::Destroy((Map<String, Variant>*)mData);
        break;
    case VariantType::Object:
        Memory::Destroy((Ref<Reference>*)mData);
        break;
    case VariantType::Vector2:
        Memory::Destroy((Vector2*)mData);
        break;
    case VariantType::Vector3:
        Memory::Destroy((Vector3*)mData);
        break;
    case VariantType::Vector4:
        Memory::Destroy((Vector4*)mData);
        break;
    case VariantType::Color:
        Memory::Destroy((Color4*)mData);
        break;
    }

    mType = VariantType::Null;
}
