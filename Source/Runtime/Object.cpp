#include <YAWN/Runtime/Object.hpp>

using namespace YAWN;

const wchar_t* Object::GetTypeName() const {
    return L"Object";
}

TypeId Object::GetTypeId() const {
    return TypeId::From<Object>();
}

bool Object::_IsInstanceOf(TypeId id) const {
    constexpr TypeId objectId = TypeId::From<Object>();

    return id == objectId;
}
