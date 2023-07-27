#include <YAWN/Reflection/Types.hpp>

using namespace YAWN;

Map<int, Type> Types::sTypes;

Type& Types::GetType(int id) {
    return sTypes[id];
}

void Types::EnumerateTypesOfBase(int base, const Delegate<void(const Type&)>& delegate) {
    YAWN_ASSERT(delegate);

    for (KeyValue<int, Type>& type : sTypes) {
        if (type.Value.GetBase() == base) {
            delegate(type.Value);
        }
    }
}
