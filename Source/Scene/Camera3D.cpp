#include <YAWN/Scene/Camera3D.hpp>
#include <YAWN/Graphics/Renderer.hpp>

using namespace YAWN;

void Camera3D::Register(Meta<Camera3D>& meta) {
    meta.SetBase<Node3D>();
    meta.SetName(L"Camera3D");
}

void Camera3D::Enter() {
}

void Camera3D::Exit() {
}

void Camera3D::OnTransformUpdate() {
    Renderer::SetCameraTransform(GetGlobalTransform());
    Renderer::SetCameraProjection(Matrix4::CreatePerspective(Math::DegreesToRadians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f));
}
