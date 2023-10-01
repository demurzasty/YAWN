#include <YAWN/Scene/Geometry3D.hpp>
#include <YAWN/Graphics/Renderer.hpp>

using namespace YAWN;

void Geometry3D::Register(Meta<Geometry3D>& meta) {
    meta.SetBase<Node3D>();
    meta.SetName(L"Geometry3D");
    meta.SetConstructable();
    meta.AddField<&Geometry3D::SetMesh, &Geometry3D::GetMesh>(L"Mesh");
}

void Geometry3D::SetMesh(const Ref<Mesh>& mesh) {
    mMesh = mesh;

    if (mMesh && Renderer::IsMeshValid(mMesh->GetId())) {
        if (mId == Pool::None) {
            mId = Renderer::CreateInstance();
        }
    }

    Renderer::SetInstanceMesh(mId, mMesh ? mMesh->GetId() : Pool::None);
}

const Ref<Mesh>& Geometry3D::GetMesh() const {
    return mMesh;
}

void Geometry3D::Enter() {
    if (mId == Pool::None) {
        mId = Renderer::CreateInstance();
    }
}

void Geometry3D::Exit() {
    if (mId != Pool::None) {
        Renderer::DestroyInstance(mId);
        mId = Pool::None;
    }
}

void Geometry3D::OnTransformUpdate() {
    Renderer::SetInstanceTransform(mId, GetGlobalTransform());
}

