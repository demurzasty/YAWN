#include <YAWN/Runtime/Object.hpp>

using namespace YAWN;

const wchar_t* Object::GetTypeName() const {
    return L"Object";
}

int Object::GetTypeId() const {
    return TypeID::Hash<Object>();
}

bool Object::_IsInstanceOf(int id) const {
    constexpr int objectId = TypeID::Hash<Object>();

    return id == objectId;
}
