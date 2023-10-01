#include <YAWN/Reflection/Types.hpp>

using namespace YAWN;

Map<int, Ref<Type>> Types::sTypes;

Ref<Type> Types::GetType(int id) {
    Ref<Type> type;
    if (sTypes.TryGet(id, type)) {
        return type;
    }

    return sTypes.Add(id, new Type());
}

Ref<Type> Types::GetTypeByName(const String& name) {
    for (const KeyValue<int, Ref<Type>>& keyValue : sTypes) {
        if (keyValue.Value->GetName() == name) {
            return keyValue.Value;
        }
    }

    return nullptr;
}

void Types::EnumerateTypesOfBase(int base, const Delegate<void(const Ref<Type>&)>& delegate) {
    YAWN_ASSERT(delegate);

    for (const KeyValue<int, Ref<Type>>& type : sTypes) {
        if (type.Value->IsDerivedFrom(base)) {
            delegate(type.Value);
        }
    }
}
