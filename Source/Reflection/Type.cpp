#include <YAWN/Reflection/Type.hpp>
#include <YAWN/Reflection/Types.hpp>

using namespace YAWN;

void Type::SetId(int id) {
    mId = id;
}

int Type::GetId() const {
    return mId;
}

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

void Type::AddField(const Ref<Field>& field) {
    YAWN_ASSERT(field);
    YAWN_ASSERT(!HasField(field->GetName()));

    mFields.Add(field);
}

bool Type::HasField(const String& name) {
    for (const Ref<Field>& field : mFields) {
        if (field->GetName() == name) {
            return true;
        }
    }

    return false;
}

Ref<Field> Type::GetField(const String& name) {
    for (const Ref<Field>& field : mFields) {
        if (field->GetName() == name) {
            return field;
        }
    }

    if (mBase) {
        if (Ref<Type> base = Types::GetType(mBase); base) {
            return base->GetField(name);
        }
    }

    return nullptr;
}

void Type::EnumerateFields(const Delegate<void(const Ref<Field>&)>& delegate) {
    YAWN_ASSERT(delegate);

    for (const Ref<Field>& field : mFields) {
        delegate(field);
    }

    if (mBase) {
        if (Ref<Type> base = Types::GetType(mBase); base) {
            Types::GetType(mBase)->EnumerateFields(delegate);
        }
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
        if (Ref<Type> base = Types::GetType(mBase); base) {
            return base->IsDerivedFrom(id);
        }
    }

    return false;
}
