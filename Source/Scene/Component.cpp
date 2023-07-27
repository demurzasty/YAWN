#include <YAWN/Scene/Component.hpp>
#include <YAWN/Scene/Actor.hpp>

using namespace YAWN;

void Component::Register(Meta<Component>& meta) {
    meta.SetBase<Reference>();
    meta.SetName(L"Component");
}

void Component::Enter() {
}

void Component::Exit() {
}

void Component::Update(float timeStep) {
}

void Component::LateUpdate(float timeStep) {
}

void Component::FixedUpdate(float timeStep) {
}

Actor* Component::GetOwner() const {
    return mOwner;
}
