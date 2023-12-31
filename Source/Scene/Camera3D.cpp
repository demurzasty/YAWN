#include <YAWN/Scene/Camera3D.hpp>
#include <YAWN/Graphics/Renderer.hpp>
#include <YAWN/Scene/Viewport.hpp>

using namespace YAWN;

void Camera3D::Register(Meta<Camera3D>& meta) {
    meta.SetConstructable();
}

void Camera3D::Enter() {
    Base::Enter();
}

void Camera3D::Exit() {
    Base::Exit();
}

void Camera3D::Update(float timeStep) {
    Base::Update(timeStep);

    Ref<Viewport> viewport = GetViewport();
    if (viewport) {
        Renderer::SetCameraProjection(Matrix4::CreatePerspective(Math::DegreesToRadians(45.0f), viewport->GetSize().X / viewport->GetSize().Y, 0.1f, 100.0f));
    }
}

void Camera3D::HandleEvent(const Event& event) {
    Base::HandleEvent(event);

    if (event.Type == EventType::WindowResize) {
        const WindowResizeEvent& resizeEvent = (const WindowResizeEvent&)event;

        Renderer::SetCameraProjection(Matrix4::CreatePerspective(Math::DegreesToRadians(45.0f), resizeEvent.Size.X / resizeEvent.Size.Y, 0.1f, 100.0f));
    }
}

void Camera3D::OnTransformUpdate() {
    Base::OnTransformUpdate();

    Renderer::SetCameraTransform(GetGlobalTransform());
}
