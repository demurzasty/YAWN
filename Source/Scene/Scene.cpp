#include <YAWN/Scene/Scene.hpp>

using namespace YAWN;

Ref<Actor> Scene::sRoot;

void Scene::Initialize() {
    sRoot = new Actor();
}

void Scene::Release() {
    sRoot.Reset();
}

void Scene::Update(float timeStep) {
    Update(sRoot, timeStep);
}

void Scene::LateUpdate(float timeStep) {
    LateUpdate(sRoot, timeStep);
}

void Scene::FixedUpdate(float timeStep) {
    FixedUpdate(sRoot, timeStep);
}

void Scene::Update(const Ref<Actor>& actor, float timeStep) {
    actor->Update(timeStep);

    for (const Ref<Actor>& child : actor->GetChildren()) {
        Update(child, timeStep);
    }
}

void Scene::LateUpdate(const Ref<Actor>& actor, float timeStep) {
    actor->LateUpdate(timeStep);

    for (const Ref<Actor>& child : actor->GetChildren()) {
        LateUpdate(child, timeStep);
    }
}

void Scene::FixedUpdate(const Ref<Actor>& actor, float timeStep) {
    actor->FixedUpdate(timeStep);

    for (const Ref<Actor>& child : actor->GetChildren()) {
        FixedUpdate(child, timeStep);
    }
}

const Ref<Actor>& Scene::GetRoot() {
    return sRoot;
}
