#include <YAWN/Scene/Scene.hpp>

using namespace YAWN;

Ref<Node> Scene::sRoot;

void Scene::Initialize() {
    sRoot = new Node();
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

void Scene::Update(const Ref<Node>& node, float timeStep) {
    node->Update(timeStep);

    for (const Ref<Node>& child : node->GetChildren()) {
        Update(child, timeStep);
    }
}

void Scene::LateUpdate(const Ref<Node>& node, float timeStep) {
    node->LateUpdate(timeStep);

    for (const Ref<Node>& child : node->GetChildren()) {
        LateUpdate(child, timeStep);
    }
}

void Scene::FixedUpdate(const Ref<Node>& node, float timeStep) {
    node->FixedUpdate(timeStep);

    for (const Ref<Node>& child : node->GetChildren()) {
        FixedUpdate(child, timeStep);
    }
}

const Ref<Node>& Scene::GetRoot() {
    return sRoot;
}
