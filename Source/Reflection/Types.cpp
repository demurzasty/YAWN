#include <YAWN/Reflection/Types.hpp>

using namespace YAWN;

Map<int, Type> Types::sTypes;

Type& Types::GetType(int id) {
    return sTypes.GetOrAdd(id);
}

Type* Types::GetTypeByName(const String& name) {
    return sTypes.TryGet([&name](const Type& type) {
        return type.GetName() == name;
    });
}

void Types::EnumerateTypesOfBase(int base, const Delegate<void(const Type&)>& delegate) {
    YAWN_ASSERT(delegate);

    for (KeyValue<int, Type>& type : sTypes) {
        if (type.Value.GetBase() == base) {
            delegate(type.Value);
        }
    }
}
