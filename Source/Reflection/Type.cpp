#include <YAWN/Reflection/Type.hpp>
#include <YAWN/Reflection/Types.hpp>

using namespace YAWN;

void Type::SetName(const String& string) {
    mName = string;
}

const String& Type::GetName() const {
    return mName;
}

void Type::AddTag(const String& tag) {
    if (!HasTag(tag)) {
        mTags.Add(tag);
    }
}

bool Type::HasTag(const String& tag) const {
    return mTags.Find(tag) > -1;
}

void Type::AddField(const String& name, const Field& field) {
    YAWN_ASSERT(!mFields.Contains(name));

    mFields.Add(name, field);
}

bool Type::HasField(const String& name) {
    return mFields.Contains(name);
}

const Field& Type::GetField(const String& name) {
    if (mBase) {
        Type& base = Types::GetType(mBase);
        if (base.HasField(name)) {
            return base.GetField(name);
        }
    }

    return mFields[name];
}

void Type::EnumerateFields(const Delegate<void(const String&, const Field&)>& delegate) {
    YAWN_ASSERT(delegate);

    if (mBase) {
        Types::GetType(mBase).EnumerateFields(delegate);
    }

    for (const KeyValue<String, Field>& field : mFields) {
        delegate(field.Key, field.Value);
    }
}

void Type::SetConstructor(Ref<Reference>(*constructor)()) {
    mConstructor = constructor;
}

Ref<Reference> Type::Construct() const {
    YAWN_ASSERT(mConstructor);
    return mConstructor();
}

void Type::SetBase(int id) {
    mBase = id;
}

int Type::GetBase() const {
    return mBase;
}

bool Type::IsDerivedFrom(int id) const {
    if (mBase == id) {
        return true;
    }

    if (mBase) {
        return Types::GetType(mBase).IsDerivedFrom(id);
    }

    return false;
}
