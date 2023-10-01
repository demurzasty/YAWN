#include <YAWN/Runtime/Resource.hpp>

using namespace YAWN;

void Resource::Register(Meta<Resource>& meta) {
    meta.SetName(L"Resource");
    meta.SetBase<Reference>();
}