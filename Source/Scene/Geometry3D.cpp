#include <YAWN/Scene/Geometry3D.hpp>
#include <YAWN/Graphics/Renderer.hpp>
#include <YAWN/Scene/Viewport.hpp>
#include <YAWN/Runtime/Console.hpp>

using namespace YAWN;

void Geometry3D::Register(Meta<Geometry3D>& meta) {
    meta.SetConstructable();
    meta.AddField<&Geometry3D::SetMesh, &Geometry3D::GetMesh>(L"Mesh");
    meta.AddField<&Geometry3D::SetMaterial, &Geometry3D::GetMaterial>(L"Material");
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

void Geometry3D::SetMaterial(const Ref<Material>& material) {
    mMaterial = material;

    if (mMaterial && Renderer::IsMeshValid(mMaterial->GetId())) {
        if (mId == Pool::None) {
            mId = Renderer::CreateInstance();
        }
    }

    Renderer::SetInstanceMaterial(mId, mMaterial ? mMaterial->GetId() : Pool::None);
}

const Ref<Material>& Geometry3D::GetMaterial() const {
    return mMaterial;
}

void Geometry3D::Enter() {
    if (mId == Pool::None) {
        mId = Renderer::CreateInstance();
    }

    Ref<Viewport> viewport = GetViewport();
    YAWN_ASSERT(viewport);
    Renderer::SetInstanceViewport(mId, viewport->GetId());
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

