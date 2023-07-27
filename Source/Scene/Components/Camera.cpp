#include <YAWN/Scene/Components/Camera.hpp>
#include <YAWN/Scene/Actor.hpp>
#include <YAWN/Graphics/Renderer.hpp>

using namespace YAWN;

void Camera::Register(Meta<Camera>& meta) {
    meta.SetBase<Component>();
    meta.SetName(L"Camera");
}

void Camera::Enter() {
    GetOwner()->GetTransformUpdateSignal().Connect<&Camera::OnTransformUpdate>(this);
}

void Camera::Exit() {
    GetOwner()->GetTransformUpdateSignal().Disconnect(this);
}

void Camera::OnTransformUpdate(const Ref<Actor>& actor) {
    Renderer::SetCameraTransform(actor->GetGlobalTransform());
    Renderer::SetCameraProjection(Matrix4::CreatePerspective(Math::DegreesToRadians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f));
}
