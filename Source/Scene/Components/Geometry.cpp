#include <YAWN/Scene/Components/Geometry.hpp>
#include <YAWN/Scene/Actor.hpp>
#include <YAWN/Graphics/Renderer.hpp>

using namespace YAWN;

void Geometry::Register(Meta<Geometry>& meta) {
    meta.SetBase<Component>();
    meta.SetName(L"Geometry");
}

void Geometry::Enter() {
    if (mId == Pool::None) {
        mId = Renderer::CreateInstance();
    }

    GetOwner()->GetTransformUpdateSignal().Connect<&Geometry::OnTransformUpdate>(this);

    OnTransformUpdate(GetOwner());
}

void Geometry::Exit() {
    if (mId != Pool::None) {
        Renderer::DestroyInstance(mId);
        mId = Pool::None;
    }

    GetOwner()->GetTransformUpdateSignal().Disconnect(this);
}

void Geometry::SetMesh(const Ref<Mesh>& mesh) {
    mMesh = mesh;

    if (mMesh) {
        
    }
}

const Ref<Mesh>& Geometry::GetMesh() const {
    return mMesh;
}

void Geometry::OnTransformUpdate(const Ref<Actor>& actor) {
    Renderer::SetInstanceTransform(mId, actor->GetGlobalTransform());
}

