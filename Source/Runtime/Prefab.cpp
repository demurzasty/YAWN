#include <YAWN/Runtime/Prefab.hpp>
#include <YAWN/Runtime/JSON.hpp>

using namespace YAWN;

void Prefab::Register(Meta<Prefab>& meta) {
}

Prefab::Prefab(const String& data)
    : mData(data) {
}

Ref<Node> Prefab::Instantiate() {
    Variant data = JSON::Parse(mData);

    YAWN_ASSERT(data.GetType() == VariantType::Object);

    return CastTo<Node>(data.AsObject());
}
