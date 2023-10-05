#include <YAWN/Reflection/Field.hpp>

using namespace YAWN;

Field::Field(const String& name, void (*setter)(void*, const Variant&), void (*getter)(const void*, Variant&), VariantType type)
    : mName(name), mSetter(setter), mGetter(getter), mType(type) {
}

void Field::Set(void* instance, const Variant& value) const {
    YAWN_ASSERT(mSetter);
    YAWN_ASSERT(instance);

    mSetter(instance, value);
}

void Field::Get(const void* instance, Variant& value) const {
    YAWN_ASSERT(mGetter);
    YAWN_ASSERT(instance);

    mGetter(instance, value);
}

Variant Field::Get(const void* instance) const {
    Variant value;
    Get(instance, value);
    return value;
}

bool Field::IsAssignable() const {
    return mSetter;
}

const String& Field::GetName() const {
    return mName;
}

VariantType Field::GetType() const {
    return mType;
}
