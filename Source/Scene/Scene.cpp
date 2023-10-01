#include <YAWN/Scene/Scene.hpp>
#include <YAWN/Scene/UI/Control.hpp>
#include <YAWN/Graphics/Renderer.hpp>
#include <YAWN/Platform/Window.hpp>

using namespace YAWN;

Ref<Viewport> Scene::sRoot;

void Scene::Initialize() {
    sRoot = new Viewport();
    sRoot->SetName(L"Root");
    sRoot->SetRenderDirectToScreen(true);
    sRoot->SetSize(Window::GetSize());
    sRoot->OnEnter();
}

void Scene::Release() {
    sRoot->Exit();
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

void Scene::HandleEvent(const Event& event) {
    HandleEvent(sRoot, event);
}

void Scene::Redraw() {
    Redraw(sRoot);
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

void Scene::HandleEvent(const Ref<Node>& node, const Event& event) {
    for (int i = node->GetChildCount() - 1; i >= 0; --i) {
        HandleEvent(node->GetChild(i), event);
    }

    if (!event.IsConsumed()) {
        node->HandleEvent(event);
    }
}

void Scene::Redraw(const Ref<Node>& node) {
    if (node->IsVisible()) {
        const Ref<Control> control = CastTo<Control>(node);
        if (control) {
            Renderer::LLPushClipRect(control->GetGlobalRectangle());
        }

        node->Redraw();

        for (const Ref<Node>& child : node->GetChildren()) {
            Redraw(child);
        }

        if (control) {
            Renderer::LLPopClipRect();
        }
    }
}

const Ref<Viewport>& Scene::GetRoot() {
    return sRoot;
}
