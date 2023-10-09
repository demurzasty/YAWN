#include <YAWN/Reflection/Types.hpp>

using namespace YAWN;

Map<TypeId, Ref<Type>> Types::sTypes;

Ref<Type> Types::GetType(TypeId id) {
    Ref<Type> type;
    if (sTypes.TryGet(id, type)) {
        return type;
    }
    return nullptr;
}

Ref<Type> Types::GetTypeByName(const String& name) {
    for (const KeyValue<TypeId, Ref<Type>>& keyValue : sTypes) {
        if (keyValue.Value->GetName() == name) {
            return keyValue.Value;
        }
    }

    return nullptr;
}

void Types::EnumerateTypesOfBase(TypeId base, const Delegate<void(const Ref<Type>&)>& delegate) {
    YAWN_ASSERT(delegate);

    for (const KeyValue<TypeId, Ref<Type>>& type : sTypes) {
        if (type.Value->IsDerivedFrom(base)) {
            delegate(type.Value);
        }
    }
}

Ref<Type> Types::GetOrAddType(TypeId id) {
    if (Ref<Type> type = GetType(id); type) {
        return type;
    }

    return sTypes.Add(id, new Type());
}
