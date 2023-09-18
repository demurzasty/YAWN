#include <YAWN/Scene/Geometry3D.hpp>
#include <YAWN/Graphics/Renderer.hpp>

using namespace YAWN;

void Geometry3D::Register(Meta<Geometry3D>& meta) {
    meta.SetBase<Node3D>();
    meta.SetName(L"Geometry3D");
}

void Geometry3D::SetMesh(const Ref<Mesh>& mesh) {
    mMesh = mesh;

    if (mMesh) {

    }
}

const Ref<Mesh>& Geometry3D::GetMesh() const {
    return mMesh;
}

void Geometry3D::OnEnter() {
    if (mId == Pool::None) {
        mId = Renderer::CreateInstance();
    }
}

void Geometry3D::OnExit() {
    if (mId != Pool::None) {
        Renderer::DestroyInstance(mId);
        mId = Pool::None;
    }
}

void Geometry3D::OnTransformUpdate() {
    Renderer::SetInstanceTransform(mId, GetGlobalTransform());
}

